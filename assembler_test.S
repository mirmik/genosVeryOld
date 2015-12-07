
#include "genos/debug/debug_asm_link.h"

.global assembler_test


assembler_test:
rcall func
rcall debug_asmlink_uint16_dpr
hhh: 
rjmp hhh
ret