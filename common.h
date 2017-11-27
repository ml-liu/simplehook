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
unsigned long long current_msecond();
__attribute((visibility("default")))  char* ffi_get_sock_info(int fd);
__attribute((visibility("default")))  char* ffi_get_peer_info(int fd);
#ifdef __cplusplus
}
#endif

#endif