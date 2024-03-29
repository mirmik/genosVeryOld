


/* Copyright (c) 2002, 2004, 2010 Joerg Wunsch
   Copyright (c) 2010  Gerben van den Broeke
   All rights reserved.

       la_alloc, la_free, la_realloc from avr-libc 1.7.0
       with minor modifications, by Paul Stoffregen

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/
 
 
/*la_alloc is based on arduino malloc
reworked for use in multithreads system
by Mirmik. (only some comment...)*/
 
 #include "genos/types.h"
 #include "genos/debug/debug.h"
 #include "genos/memory/la_alloc.h"
 #include "genos/debug/debug.h"
 #include "gstd/mem.h"


#define __MALLOC_MARGIN__ 60

uint8_t dynamic_memory_debug = 0;

void dynamic_memory_debug_enable() {dynamic_memory_debug = 1;};

struct __la_freelist {
        size_t sz;
        struct __la_freelist *nx;
};

/*
 * Exported interface:
 *
 * When extending the data segment, the allocator will not try to go
 * beyond the current stack limit, decreased by __la_alloc_margin bytes.
 * Thus, all possible stack frames of interrupt routines that could
 * interrupt the current function, plus all further nested function
 * calls must not require more stack space, or they'll risk to collide
 * with the data segment.
 */
 

#define STACK_POINTER() ((char *)AVR_STACK_POINTER_REG)
extern char __heap_start;
char *__brkval = &__heap_start; // first location not yet allocated
struct __la_freelist *__flp;       // freelist pointer (head of freelist)
char *__brkval_maximum = (char*)100;


	void la_debug_info()
{
	debug_print("la_debug_info\n");
	debug_print("Heap_start:");debug_printhex_ptr(&__heap_start); debug_putchar('\n');
	debug_print("Heap_top:");debug_printhex_ptr(__brkval); debug_putchar('\n');
	
};

void *
la_alloc(size_t len)
{
		if (dynamic_memory_debug) {debug_print("la_alloc"); debug_printhex_uint16(len); debug_putchar('\t');};
		
        struct __la_freelist *fp1, *fp2, *sfp1, *sfp2;
        char *cp;
        size_t s, avail;

        /*
         * Our minimum chunk size is the size of a pointer (plus the
         * size of the "sz" field, but we don't need to account for
         * this), otherwise we could not possibly fit a freelist entry
         * into the chunk later.
         */
        if (len < sizeof(struct __la_freelist) - sizeof(size_t))
                len = sizeof(struct __la_freelist) - sizeof(size_t);

        /*
         * First, walk the la_free list and try finding a chunk that
         * would match exactly.  If we found one, we are done.  While
         * walking, note down the smallest chunk we found that would
         * still fit the request -- we need it for step 2.
         *
         */
        for (s = 0, fp1 = __flp, fp2 = 0;
             fp1;
             fp2 = fp1, fp1 = fp1->nx) {
                if (fp1->sz < len)
                        continue;
                if (fp1->sz == len) {
                        /*
                         * Found it.  Disconnect the chunk from the
                         * freelist, and return it.
                         */
                        if (fp2)
                                fp2->nx = fp1->nx;
                        else
                                __flp = fp1->nx;	
				if (dynamic_memory_debug){debug_printhex_ptr(&(fp1->nx));debug_putchar('\n');}
                        return &(fp1->nx);
                }
                else {
                        if (s == 0 || fp1->sz < s) {
                                /* this is the smallest chunk found so far */
                                s = fp1->sz;
                                sfp1 = fp1;
                                sfp2 = fp2;
                        }
                }
        }
        /*
         * Step 2: If we found a chunk on the freelist that would fit
         * (but was too large), look it up again and use it, since it
         * is our closest match now.  Since the freelist entry needs
         * to be split into two entries then, watch out that the
         * difference between the requested size and the size of the
         * chunk found is large enough for another freelist entry; if
         * not, just enlarge the request size to what we have found,
         * and use the entire chunk.
         */
        if (s) {
                if (s - len < sizeof(struct __la_freelist)) {
                        /* Disconnect it from freelist and return it. */
                        if (sfp2)
                                sfp2->nx = sfp1->nx;
                        else
                                __flp = sfp1->nx;
						if (dynamic_memory_debug) {debug_printhex_ptr(&(sfp1->nx));debug_putchar('\n');};
                        return &(sfp1->nx);
                }
                /*
                 * Split them up.  Note that we leave the first part
                 * as the new (smaller) freelist entry, and return the
                 * upper portion to the caller.  This saves us the
                 * work to fix up the freelist chain; we just need to
                 * fixup the size of the current entry, and note down
                 * the size of the new chunk before returning it to
                 * the caller.
                 */
                cp = (char *)sfp1;
                s -= len;
                cp += s;
                sfp2 = (struct __la_freelist *)cp;
                sfp2->sz = len;
                sfp1->sz = s - sizeof(size_t);
				if (dynamic_memory_debug) {debug_printhex_ptr(&(sfp2->nx));debug_putchar('\n');};
                return &(sfp2->nx);
        }
        /*
         * Step 3: If the request could not be satisfied from a
         * freelist entry, just prepare a new chunk.  This means we
         * need to obtain more memory first.  The largest address just
         * not allocated so far is remembered in the brkval variable.
         * Under Unix, the "break value" was the end of the data
         * segment as dynamically requested from the operating system.
         * Since we don't have an operating system, just make sure
         * that we don't collide with the stack.
         */
		 // this test don't work with manual stack. So, in la_alloc
		 // this was been disabled.
        //cp = STACK_POINTER() - __MALLOC_MARGIN__;
        //if (cp <= __brkval)
          /*
           * Memory exhausted.
           */
        //  return 0;
        avail = cp - __brkval;
        /*
         * Both tests below are needed to catch the case len >= 0xfffe.
         */
        if (avail >= len && avail >= len + sizeof(size_t)) {
                fp1 = (struct __la_freelist *)__brkval;
                __brkval += len + sizeof(size_t);
                __brkval_maximum = __brkval;
                fp1->sz = len;
				if (dynamic_memory_debug) {debug_printhex_ptr(&(fp1->nx));debug_putchar('\n');};
                return &(fp1->nx);
        }
        /*
         * Step 4: There's no help, just fail. :-/
         */
		 if (dynamic_memory_debug) {debug_printhex_ptr(0);debug_putchar('\n');};
        return 0;
}


void
la_free(void *p)
{
		if (dynamic_memory_debug) {debug_print("la_free"); debug_printhex_ptr(p); debug_putchar('\n');};
        struct __la_freelist *fp1, *fp2, *fpnew;
        char *cp1, *cp2, *cpnew;

        /* ISO C says la_free(NULL) must be a no-op */
        if (p == 0)
                return;

        cpnew = (char*)p;
        cpnew -= sizeof(size_t);
        fpnew = (struct __la_freelist *)cpnew;
        fpnew->nx = 0;

        /*
         * Trivial case first: if there's no freelist yet, our entry
         * will be the only one on it.  If this is the last entry, we
         * can reduce __brkval instead.
         */
        if (__flp == 0) {
                if ((char *)p + fpnew->sz == __brkval)
                        __brkval = cpnew;
                else
                        __flp = fpnew;
                return;
        }

        /*
         * Now, find the position where our new entry belongs onto the
         * freelist.  Try to aggregate the chunk with adjacent chunks
         * if possible.
         */
        for (fp1 = __flp, fp2 = 0;
             fp1;
             fp2 = fp1, fp1 = fp1->nx) {
                if (fp1 < fpnew)
                        continue;
                cp1 = (char *)fp1;
                fpnew->nx = fp1;
                if ((char *)&(fpnew->nx) + fpnew->sz == cp1) {
                        /* upper chunk adjacent, assimilate it */
                        fpnew->sz += fp1->sz + sizeof(size_t);
                        fpnew->nx = fp1->nx;
                }
                if (fp2 == 0) {
                        /* new head of freelist */
                        __flp = fpnew;
                        return;
                }
                break;
        }
        /*
         * Note that we get here either if we hit the "break" above,
         * or if we fell off the end of the loop.  The latter means
         * we've got a new topmost chunk.  Either way, try aggregating
         * with the lower chunk if possible.
         */
        fp2->nx = fpnew;
        cp2 = (char *)&(fp2->nx);
        if (cp2 + fp2->sz == cpnew) {
                /* lower junk adjacent, merge */
                fp2->sz += fpnew->sz + sizeof(size_t);
                fp2->nx = fpnew->nx;
        }
        /*
         * If there's a new topmost chunk, lower __brkval instead.
         */
        for (fp1 = __flp, fp2 = 0;
             fp1->nx != 0;
             fp2 = fp1, fp1 = fp1->nx)
                /* advance to entry just before end of list */;
        cp2 = (char *)&(fp1->nx);
        if (cp2 + fp1->sz == __brkval) {
                if (fp2 == NULL)
                        /* Freelist is empty now. */
                        __flp = NULL;
                else
                        fp2->nx = NULL;
                __brkval = cp2 - sizeof(size_t);
        }
}



void *
la_realloc(void *ptr, size_t len)
{
		if (dynamic_memory_debug) {debug_print("la_realloc"); debug_printhex_ptr(ptr); debug_putchar('\n');
		debug_printhex_uint16(len); debug_putchar('\n');};
        struct __la_freelist *fp1, *fp2, *fp3, *ofp3;
        char *cp, *cp1;
        void *memp;
        size_t s, incr;

        /* Trivial case, required by C standard. */
        if (ptr == 0)
                return la_alloc(len);

        cp1 = (char *)ptr;
        cp1 -= sizeof(size_t);
        fp1 = (struct __la_freelist *)cp1;

        cp = (char *)ptr + len; /* new next pointer */
        if (cp < cp1)
                /* Pointer wrapped across top of RAM, fail. */
                return 0;

        /*
         * See whether we are growing or shrinking.  When shrinking,
         * we split off a chunk for the released portion, and call
         * la_free() on it.  Therefore, we can only shrink if the new
         * size is at least sizeof(struct __la_freelist) smaller than the
         * previous size.
         */
        if (len <= fp1->sz) {
                /* The first test catches a possible unsigned int
                 * rollover condition. */
                if (fp1->sz <= sizeof(struct __la_freelist) ||
                    len > fp1->sz - sizeof(struct __la_freelist))
                        return ptr;
                fp2 = (struct __la_freelist *)cp;
                fp2->sz = fp1->sz - len - sizeof(size_t);
                fp1->sz = len;
                la_free(&(fp2->nx));
                return ptr;
        }

        /*
         * If we get here, we are growing.  First, see whether there
         * is space in the la_free list on top of our current chunk.
         */
        incr = len - fp1->sz;
        cp = (char *)ptr + fp1->sz;
        fp2 = (struct __la_freelist *)cp;
        for (s = 0, ofp3 = 0, fp3 = __flp;
             fp3;
             ofp3 = fp3, fp3 = fp3->nx) {
                if (fp3 == fp2 && fp3->sz + sizeof(size_t) >= incr) {
                        /* found something that fits */
                        if (fp3->sz + sizeof(size_t) - incr > sizeof(struct __la_freelist)) {
                                /* split off a new freelist entry */
                                cp = (char *)ptr + len;
                                fp2 = (struct __la_freelist *)cp;
                                fp2->nx = fp3->nx;
                                fp2->sz = fp3->sz - incr;
                                fp1->sz = len;
                        } else {
                                /* it just fits, so use it entirely */
                                fp1->sz += fp3->sz + sizeof(size_t);
                                fp2 = fp3->nx;
                        }
                        if (ofp3)
                                ofp3->nx = fp2;
                        else
                                __flp = fp2;
                        return ptr;
                }
                /*
                 * Find the largest chunk on the freelist while
                 * walking it.
                 */
                if (fp3->sz > s)
                        s = fp3->sz;
        }
        /*
         * If we are the topmost chunk in memory, and there was no
         * large enough chunk on the freelist that could be re-used
         * (by a call to la_alloc() below), quickly extend the
         * allocation area if possible, without need to copy the old
         * data.
         */
        if (__brkval == (char *)ptr + fp1->sz && len > s) {
                cp = (char *)ptr + len;
                cp1 = STACK_POINTER() - __MALLOC_MARGIN__;
                if (cp < cp1) {
                        __brkval = cp;
                        __brkval_maximum = cp;
                        fp1->sz = len;
                        return ptr;
                }
                /* If that failed, we are out of luck. */
                return 0;
        }

        /*
         * Call la_alloc() for a new chunk, then copy over the data, and
         * release the old region.
         */
        if ((memp = la_alloc(len)) == 0)
                return 0;
        memcpy(memp, ptr, fp1->sz);
        la_free(ptr);
        return memp;
}

