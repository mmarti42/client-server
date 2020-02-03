#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFF_SIZE 1024
# define MAX_FD 1024
# define MAXLINE 1024
# define DEF_DATA_SIZE 10

int				get_next_line(const int fd, char **line);

void			bubble_sort(uint64_t **a);

int				parse_string(char *input, uint64_t **data);
//
//support functions
//
void			*xmalloc(size_t size);
void			err_quit(char *s);
int				ft_isdigit(char c);
size_t			darlen(uint64_t **m);
void			print_data(uint64_t **all_data);
void			print_socket(int sockfd);

#endif
