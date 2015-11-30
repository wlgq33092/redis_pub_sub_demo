#include <string.h>
#include <hiredis.h>
#include <async.h>
#include <adapters/libevent.h>


void subscribe(const char* key, redisCallbackFn* cb, int limit);