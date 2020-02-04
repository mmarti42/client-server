#ifndef SERV_H
# define SERV_H
# include <stdio.h>
#include <inttypes.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <limits.h>
#include <pthread.h>
# define LE 1
# define BE 0
# define MAX_QUEUE 10
# define MAXLINE 1024

typedef struct  s_sub
{
    uint64_t        start_pos;
    uint64_t        step;
    uint64_t        curr_pos;
    struct s_sub    *next;

}                   t_sub;

uint64_t    get_next_step(t_sub *s);
t_sub		*parse_sub(uint64_t **arr);

//
//support functions
//
void        err_exit(char *s);
void        *xmalloc(size_t size);
void        print_seq(uint64_t **seq);

#endif
