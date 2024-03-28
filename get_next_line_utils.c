/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:01:17 by rd-agost          #+#    #+#             */
/*   Updated: 2024/03/28 20:13:33 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*array;
	unsigned char	*ptr;
	size_t			total_size;

	array = malloc(nmemb * size);
	if (array == NULL)
		return (NULL);
	ptr = (unsigned char *)array;
	total_size = nmemb * size;
	while (total_size--)
		*ptr++ = 0;
	return (array);
}

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src [i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	finish;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	finish = 0;
	if (start <= slen)
		finish = slen - start;
	if (finish > len)
		finish = len;
	new = (char *)malloc(sizeof(char) * finish + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, finish + 1);
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*ptr;
	int				i;
	int				t;
	const int		s1len = ft_strlen(s1);
	const int		s2len = ft_strlen(s2);

	ptr = ft_calloc((s1len + s2len + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	i = -1;
	t = 0;
	while (++i < s1len)
		ptr[i] = s1[i];
	while (t < s2len)
		ptr[i++] = s2[t++];
	ptr[s1len + s2len] = '\0';
	free(s1);
	return (ptr);
}
