#ifndef __COMMON_H

#define __COMMON_H
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
unsigned long long current_usecond();
__attribute((visibility("default"))) double current_tick();
 __attribute((visibility("default"))) long ffi_get_tid();
void log_init();
__attribute((visibility("default")))  void ffi_log_out(char* str);
#ifdef __cplusplus
}
#endif

#endif