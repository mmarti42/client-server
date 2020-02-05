#include "client.h"

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
    while (get_next_line(STDIN_FILENO, &input))
    {
        if (!strcmp(input, "exit"))
            exit (0);
        if (!strcmp(input, "export seq"))
        {
            if (!*all_data)
            {
                fprintf(stderr, "client: empty seq\n");
                continue ;
            }
            break ;
        }
        else if ((tmp = parse_string(input, &all_data[i]) < 0))
        {
            free(input);
            continue ;
        }
        free(input);
        i++;
        if (i >= size)
            all_data = expand_all_data(all_data, &size);
    }
    free(input);
    return (all_data);
}

uint8_t check_byte_order()
{
    uint16_t a = 1;

    return (*(uint8_t *)&a);
}

void    convert(uint64_t tmp)
{
    if (check_byte_order() == BE)
        return ;
    tmp = (((uint64_t)htonl(tmp)) << 32) + htonl(tmp >> 32);
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
        convert(tmp[0]);
        convert(tmp[1]);
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
    free_dar(all_data);
    // print_data(all_data);
    // sleep(1);
    while (1)
    {
        print_socket(sockfd);
        sleep (1);
    }
    return 0;
}
