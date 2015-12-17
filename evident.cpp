


#include "genos/base_struct/evident.h"
#include "genos/defs.h"

#ifdef EVIDENT_MODE
evident_table_t evident_table;
#endif EVIDENT_MODE


gstd::static_revstring<21> to_string_void(void*){return gstd::static_revstring<21>("stub_func_to_string");};
gstd::static_revstring<21> to_string_int16(void* data){return gstd::int_to_string(htreat<int>(data), 10);};
gstd::static_revstring<21> to_string_ptr(void* data){return gstd::int_to_string(htreat<int16_t>(data), 16);};

