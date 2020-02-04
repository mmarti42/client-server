#include "client.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	dst = (char *)xmalloc(strlen(s1) + strlen(s2) + 1);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	return (dst);
}

static int	ft_get_line(char **fd_lines, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *fd_lines;
	while (tmp[i] != '\n')
	{
		if (!tmp[i++])
			return (0);
	}
	tmp[i] = 0;
	*line = strdup(*fd_lines);
	*fd_lines = strdup(&tmp[i + 1]);
	free(tmp);
	tmp = 0;
	return (1);
}

static int	ft_readline(int fd, char **fd_lines, char *buf, char **line)
{
	char *tmp;

	while (read(fd, buf, BUFF_SIZE))
	{
		if (!*fd_lines)
			*fd_lines = strdup(buf);
		else if (*fd_lines)
		{
			tmp = *fd_lines;
			*fd_lines = ft_strjoin(*fd_lines, buf);
			free(tmp);
		}
		if ((ft_get_line(fd_lines, line)) == 1)
			return (1);
		memset(buf, 0, BUFF_SIZE);
	}
	if (*fd_lines && *fd_lines[0] != 0 && strchr(*fd_lines, '\n') == 0)
	{
		*line = strdup(*fd_lines);
		free(*fd_lines);
		*fd_lines = 0;
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*fd_lines[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || fd >= MAX_FD || BUFF_SIZE <= 0)
		return (-1);
	memset(buf, 0, BUFF_SIZE + 1);
	if (read(fd, buf, 0) < 0)
		return (-1);
	if (fd_lines[fd] && strchr(fd_lines[fd], '\n'))
		return (ft_get_line(&fd_lines[fd], line));
	ret = ft_readline(fd, &fd_lines[fd], buf, line);
	return (ret);
}
