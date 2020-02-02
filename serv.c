#include "serv.h"
#include <pthread.h>

void	err_exit(char *s);

void    *xmalloc(size_t size)
{
    void *new;

    if (!(new = malloc(size)))
        err_exit(NULL);
    memset(new, 0, size);
    return (new);
}

void    err_exit(char *s)
{
    if (s)
        printf("%s\n", s);
    else
       perror ("server");
    exit (1);
}

void    push_back(t_sub **sub_list, uint64_t *arr)
{
    static t_sub *curr;

    if (!*sub_list)
    {
        *sub_list = (t_sub *)xmalloc(sizeof(t_sub));
        curr = *sub_list;
    }
    else
    {
        curr->next = (t_sub *)xmalloc(sizeof(t_sub));
        curr = curr->next;
    }
    curr->start_pos = *arr;
    curr->step = arr[1];
}

t_sub   *parse_sub(uint64_t **arr)
{
    t_sub *sub_list = NULL;

    while (*arr)
    {
        push_back(&sub_list, *arr);
        arr++;
    }
    return (sub_list);
}

uint64_t get_next_step(t_sub *s)
{
    if (ULLONG_MAX - s->step < s->curr_pos)
        s->curr_pos = 0;
    if (!s->curr_pos)
	    return (s->curr_pos = s->start_pos);
    return (s->curr_pos += s->step);
}

uint64_t	**ft_recv(int connfd, int listenfd)
{
	uint64_t **res;
	uint64_t *tmp;
	size_t len, i = 0;

	if (recv(connfd, &len, sizeof(len), 0) < 0)
		err_exit(NULL);
	if (!len)
		return (NULL);
	res = (uint64_t **)xmalloc(sizeof(uint64_t *) * (len + 1));
	memset(res, 0, sizeof(uint64_t *) * (len + 1));
	while (len--)
	{
		tmp = (uint64_t *)xmalloc(sizeof(uint64_t) * 2);
		if (recv(connfd, &(*tmp), sizeof(uint64_t) * 2, 0) < 0)
			err_exit(NULL);
		res[i++] = tmp;
	}
	return (res);
}

void	print_seq(uint64_t **seq)
{
	while (*seq)
	{
		for(int i = 0; i < 2; i++)
			printf("%llu ", (*seq)[i]);
		seq++;
		printf("\n");
	}
}

void	send_sub(int connfd, t_sub *sub_list)
{
	t_sub *tmp;
	uint64_t num;

	while (1)
	{
		tmp = sub_list;
		while (tmp)
		{
			num = get_next_step(tmp);
			if (send(connfd, (char *)&num, sizeof(uint64_t), 0) < 0)
				return ;
			tmp = tmp->next;
		}
	}
}	

void	create_thread()
{


int main(int argc, char **argv)
{
	int			listenfd, connfd;
	struct sockaddr_in	servaddr;
	uint64_t		**seq;
	t_sub			*sub_list;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5000); 
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, 10);

	while (1) 
	{
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0)
			err_exit(NULL);
		create_thread();
		if (!(seq = ft_recv(connfd, listenfd)))
			err_exit("ft_recv error");
		if (!(sub_list = parse_sub(seq)))
		{
			fprintf(stderr, "parse_sub error"); 
			close(connfd);
		}
		send_sub(connfd, sub_list);
	}
}
