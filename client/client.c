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

void err_quit(char *s)
{
    if (s)
        fprintf(stderr, "%s\n", s);
    else
        perror("server");
    exit (1);
}

void    *xmalloc(size_t size)
{
    void *new;

    if (!(new = malloc(size)))
        err_quit(NULL);
    memset(new, 0, size);
    return (new);
}

int ft_isdigit(char c)
{
    if (c < '0' || c > '9')
        return (1);
    return (0);
}

int get_command(char *str)
{
    char *tmp = str;
    if (strncmp(str, "seq", 3))
        exit (1);
    str += 3;
    while (*tmp)
    {
        if (ft_isdigit(*tmp))
            exit(1);
        tmp++;
    }
    return (atoll(str));
}

void	*ft_realloc(void *buf, size_t old, size_t new_size)
{
	unsigned char	*new_buf;

	new_buf = xmalloc(new_size);
	if (buf)
		memcpy(new_buf, buf, old);
	free(buf);
	return (new_buf);
}

uint64_t **expand_all_data(uint64_t **all_data, int *size)
{
    *size *= 2;
    return ((uint64_t **)ft_realloc(all_data, sizeof(uint64_t *) * (*size / 2),
    *size * sizeof(uint64_t *)));
}

int check_nums(char *s)
{
    while (*s)
    {
        if (ft_isdigit(*s))
            return (-1);
        s++;
    }
    return (0);
}

uint64_t    get_seq_num(char *s)
{
    char *tmp;

    if (!s || strncmp(s, "seq", 3))
        return (0);
    s += 3;
    if (check_nums(s) < 0)
        return (0);
    return (strtoull(s, NULL, 10));
}

uint64_t    get_start_pos(char *s)
{
    if (!s || check_nums(s) < 0)
        return (0);
    return (strtoull(s, NULL, 10));
}

uint64_t    get_step(char *s)
{
    return (get_start_pos(s));
}

int         parse_string(char *input, uint64_t **data)
{
    (*data) = (uint64_t *)xmalloc(sizeof(uint64_t) * 3);
    (*data)[0] = get_seq_num(strtok(input, " \t"));
    (*data)[1] = get_start_pos(strtok(NULL, " \t"));
    (*data)[2] = get_step(strtok(NULL, " \t"));
    if (!(*data)[0] || !(*data)[1] || !(*data)[2])
    {
        memset(*data, 0, sizeof(uint64_t) * 3);
        fprintf(stderr, "client: invalid input\n");
        return (-1);
    }
    return (0);
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
            break ;
        else if ((tmp = parse_string(input, &all_data[i]) < 0))
            continue ;
        i++;
        if (i >= size)
            all_data = expand_all_data(all_data, &size);
    }
    free(input);
    return (all_data);
}

void print_data(uint64_t **all_data)
{
    while (*all_data)
    {
        int i = 0;
        while (i < 3)
            printf("%llu ", (*all_data)[i++]);
        printf("\n");
        all_data++;
    }
}

size_t     darlen(uint64_t **m)
{
    size_t i = 0;

    if (!m)
        return (0);
    while (*m)
    {
        m++;
        i++;
    }
    return (i);
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

void    ft_swap(uint64_t **a, uint64_t **b)
{
    uint64_t *c;

    c = *a;
    *a = *b;
    *b = c;
}

void bubble_sort(uint64_t **a)
{
    size_t it = darlen(a) - 1;
    uint64_t **tmp;
    int f;

    while (it--)
    {
        tmp = a;
        while (*(tmp + 1))
        {
            if (**tmp > **(tmp + 1))
            {
                ft_swap(&*tmp, &*(tmp + 1));
                f = 1;
            }
            tmp++;
        }
        if (!f)
            break ;
    }
}

void    print_socket(int sockfd)
{
    uint64_t a;
    int b = 10;

    while (b--)
    {
        read(sockfd, &a, sizeof(uint64_t));
        printf("%llu ", a);
    }
    printf("\n");
}

int main(int argc, char *argv[]) 
{
    int         sockfd = 0, n = 0, all_data_size = DEF_DATA_SIZE, i = 0;
    struct      sockaddr_in serv_addr;
    uint64_t    **all_data;
    
    
    if(argc != 2)
        err_quit("Usage: %s <ip of server>");
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
    print_data(all_data);
    sleep(1);
    while (1)
    {
        print_socket(sockfd);
        sleep (1);
    }
    return 0;
}
