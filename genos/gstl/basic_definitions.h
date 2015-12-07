/*	Copyright (C) 2004 Garrett A. Kajmowicz
	This file is part of the uClibc++ Library.
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __BASIC_DEFINITIONS
#define __BASIC_DEFINITIONS 1

#include <genos/gstl/system_configuration.h>

//#pragma GCC visibility push(default)

//The following is used to support GCC symbol visibility patch
/*
#ifdef GCC_HASCLASSVISIBILITY
	#define _UCXXEXPORT __attribute__ ((visibility("default")))
	#define _UCXXLOCAL __attribute__ ((visibility("hidden")))
#else
	#define _UCXXEXPORT
	#define _UCXXLOCAL

#endif

#ifdef __GCC__
#define __UCLIBCXX_NORETURN __attribute__ ((__noreturn__))
#else
#define __UCLIBCXX_NORETURN
#endif

#ifdef __UCLIBCXX_HAS_TLS__
	#define __UCLIBCXX_TLS __thread
#else
	#define __UCLIBCXX_TLS
#endif
*/


//Testing purposes
#define __STRING_MAX_UNITS 65535

namespace std{
	typedef signed long int streamsize;
}

//#pragma GCC visibility pop

#endif

