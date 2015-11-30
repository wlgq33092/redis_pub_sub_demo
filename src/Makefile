CC=gcc

objs=main.o sub.o
target=redis_practice
include_dir=-I/Users/wuge/open_source/redis-3.0.5/deps/hiredis -I/Users/wuge/open_source/libevent-2.0.22-stable -I/Users/wuge/open_source/libevent-2.0.22-stable/include
link_dir=-L/Users/wuge/open_source/redis-3.0.5/deps/hiredis -L/Users/wuge/open_source/libevent-2.0.22-stable/.libs
link_libs=-lhiredis -levent -lpthread

%.o:%.c
	$(CC) $(include_dir) -c -o $@ $^

target:$(objs)
	$(CC) $(objs) -o $(target) $(link_dir) $(link_libs)

clean:
	rm *.o $(target)