#include "serv.h"

uint64_t	**ft_recv(int connfd)
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

void	*start_rtn(void *arg)
{
	uint64_t **seq;
	int connfd = *(int *)arg;
	t_sub	*sub_list;

	if (!(seq = ft_recv(connfd)))
		err_exit("ft_recv error");
	if (!(sub_list = parse_sub(seq)))
	{
		fprintf(stderr, "parse_error");
		close (connfd);
		pthread_exit(NULL);
		return (NULL);
	}
	send_sub(connfd, sub_list);
	pthread_exit(NULL);
}

void	create_thread(int connfd)
{
	pthread_t tidp;

	if (pthread_create(&tidp, NULL, start_rtn, &connfd) < 0)
		err_exit(NULL);
}

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5000); 
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, MAX_QUEUE);

	while (1) 
	{
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0)
			err_exit("accept error");
		create_thread(connfd);
	}
}
