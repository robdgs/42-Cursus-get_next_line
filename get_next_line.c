/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:00:21 by rd-agost          #+#    #+#             */
/*   Updated: 2024/03/28 20:58:54 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		*leftover = NULL;
	char			*res;
	char			*check;
	int				posiz;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = ft_basic_fill(fd, leftover);
	check = ft_strchr(leftover, '\n');
	if (check == NULL && leftover)
		return (end_file(&leftover));
	if (check && leftover)
	{
		posiz = check - leftover;
		res = ft_substr(leftover, 0, posiz + 1);
		check = leftover;
		leftover = ft_substr(check, posiz + 1, ft_strlen(leftover));
		return (free(check), res);
	}
	if (leftover)
	{
		free(leftover);
		leftover = NULL;
	}
	return (leftover);
}

 int main (void)
{
	char *line;
	int i = 0;
	int fd = open("file.txt", O_RDONLY);
	if (!fd)
		 printf("no");
	line = get_next_line(fd);
	printf("[%d]%s", i, line);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
		printf("[%d]%s",i, line);
	}
	free(line);
	close(fd);
	return (0);
} 