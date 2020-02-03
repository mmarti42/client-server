#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAXLINE 1024
#define DEF_DATA_SIZE 10

uint64_t **expand_all_data(uint64_t **all_data, int *size)
{
    size_t bytes;

    *size *= 2;
    bytes = *size * sizeof(uint64_t *);
    return ((uint64_t **)memset(realloc(all_data, bytes), 0, bytes));
}

uint64_t    **get_data()
{
    int  size = DEF_DATA_SIZE, i = 0, tmp;
    char     *input;
    uint64_t **all_data;

    all_data = (u_int64_t **)xmalloc(size * sizeof(uint64_t *));
    while (1)
    {
        input = readline("$> ");
        if (!strncmp(input, "export", 5))
        {
            if (!*all_data)
                err_quit("Empty seq");
            break ;
        }
        else if ((tmp = parse_string(input, &all_data[i]) < 0))
            continue ;
        i++;
        if (i >= size)
            all_data = expand_all_data(all_data, &size);
    }
    free(input);
    return (all_data);
}


void    send_data(int sockfd, uint64_t **all_data)
{
    size_t len;
    uint64_t *tmp;

    len = darlen(all_data);
    write(sockfd, &len, sizeof(len));
    while (len--)
    {
        tmp = *all_data;
        tmp++;
        if (send(sockfd, (char *)&(*tmp), sizeof(uint64_t) * 2, 0) < 0)
            err_quit(NULL);
        all_data++;
    }
}

int main(int argc, char *argv[]) 
{
    int         sockfd = 0, n = 0, all_data_size = DEF_DATA_SIZE, i = 0;
    struct      sockaddr_in serv_addr;
    uint64_t    **all_data;
    
    
    if(argc != 2)
        err_quit("Usage: client [ip of server]");
    all_data = get_data();
    if (!*all_data)
        err_quit("empty input");
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit(NULL);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
        err_quit(NULL);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
       err_quit(NULL);
    bubble_sort(all_data);
    send_data(sockfd, all_data);
    //print_data(all_data);
    sleep(1);
    // while (1)
    // {
    //     print_socket(sockfd);
    //     sleep (1);
    // }
    return 0;
}
