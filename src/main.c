#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "hiredis.h"
#include "sub.h"

void cb(redisAsyncContext *ac, void *r, void *privdata) {
    redisReply *reply = r;
    if (reply == NULL) {
    	return;
    }
    
    static int count = 0;
    int unlimited = 0;
    int limit = *(int *)privdata;
    if (limit < 0) {
    	unlimited = 1;
    }

    int i = 0;
    for (i = 0; i < reply->elements; i++) {
    	printf("subscribe: %s\n", reply->element[i]->str);
    }

    /* Disconnect after receiving the reply to GET */
    if (!unlimited && (count++ >= limit)) {
    	redisAsyncDisconnect(ac);
    }
}

int main() {
	printf("hello, world!\n");

	subscribe("foo", cb, 100);

	return 0;
}
