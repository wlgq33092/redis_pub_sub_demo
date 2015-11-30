#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "sub.h"

void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnected...\n");
}


void subscribe(const char* key, redisCallbackFn* cb, int limit) {
	signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new();

    redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
    if (ac->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", ac->errstr);
        return ;
    }

    redisLibeventAttach(ac, base);
    redisAsyncSetConnectCallback(ac, connectCallback);
    redisAsyncSetDisconnectCallback(ac, disconnectCallback);
    redisAsyncCommand(ac, cb, (void *)&limit, "subscribe %s", key);
    event_base_dispatch(base);
}