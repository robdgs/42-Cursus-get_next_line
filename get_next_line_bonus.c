/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:19:02 by rd-agost          #+#    #+#             */
/*   Updated: 2024/03/28 20:34:28 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(char const *s, int c)
{
	while (s && *s && *s != (unsigned char)c)
		++s;
	if (s && *s == (unsigned char)c)
		return ((char *)(unsigned long)s);
	else
		return (0);
}

char	*ft_strdup(char	*src)
{
	int		c;
	char	*dest;

	c = 0;
	while (src[c] != '\0')
		c++;
	dest = (char *)malloc (c * sizeof (char) + 1);
	if (!dest)
		return (NULL);
	dest[c] = 0;
	while (c >= 0)
	{
		dest[c] = src [c];
		c--;
	}
	return (dest);
}

static char	*ft_basic_fill(int fd, char *stat)
{
	int				bytes;
	char			*buf;

	bytes = BUFFER_SIZE;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while ((ft_strchr(stat, '\n')) == NULL && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(stat), NULL);
		if (bytes != 0)
		{
			buf[bytes] = '\0';
			stat = ft_strjoin(stat, buf);
		}
	}
	if (ft_strlen(stat) == 0)
	{
		free(stat);
		stat = NULL;
	}
	return (free(buf), stat);
}

char	*end_file(char **leftover)
{
	char	*buffer;

	buffer = *leftover;
	*leftover = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*leftover[4096];
	char			*res;
	char			*check;
	int				posiz;

	if (fd < 0 || fd >= 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover[fd] = ft_basic_fill(fd, leftover[fd]);
	check = ft_strchr(leftover[fd], '\n');
	if (check == NULL && leftover[fd])
		return (end_file(&leftover[fd]));
	if (check && leftover[fd])
	{
		posiz = check - leftover[fd];
		res = ft_substr(leftover[fd], 0, posiz + 1);
		check = leftover[fd];
		leftover[fd] = ft_substr(check, posiz + 1, ft_strlen(leftover[fd]));
		return (free(check), res);
	}
	if (leftover[fd])
	{
		free(leftover[fd]);
		leftover[fd] = NULL;
	}
	return (leftover[fd]);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/