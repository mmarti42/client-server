#ifndef SERV_H
# define SERV_H
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <limits.h>
# define MAXLINE 1024

typedef struct  s_sub
{
    uint64_t        start_pos;
    uint64_t        step;
    uint64_t        curr_pos;
    struct s_sub    *next;

}                   t_sub;

#endif
