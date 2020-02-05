#ifndef CLIENT_H
#define CLIENT_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <fcntl.h>
# define IS_BE (!*(uint8_t *)&(uint16_t){1})
# define BUFF_SIZE 1024
# define MAX_FD 1024
# define MAXLINE 1024
# define DEF_DATA_SIZE 10

void			convert(uint64_t tmp);

int				get_next_line(const int fd, char **line);

void			bubble_sort(uint64_t **a);

int				parse_string(char *input, uint64_t **data);

char			*ft_strjoin(char const *s1, char const *s2);
//
//support functions
//
void			free_dar(uint64_t **all_data);
void			*xmalloc(size_t size);
void			err_quit(char *s);
int				ft_isdigit(char c);
size_t			darlen(uint64_t **m);
void			print_data(uint64_t **all_data);
void			print_socket(int sockfd);

#endif
