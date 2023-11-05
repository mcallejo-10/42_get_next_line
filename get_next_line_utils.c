/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcallejo <mcallejo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:41:07 by mcallejo          #+#    #+#             */
/*   Updated: 2023/11/02 19:39:19 by mcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *raw, char *buf)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!raw)
	{
		raw = (char *)malloc(1 * sizeof(char));
		raw[0] = '\0';
	}
	if (!raw || !buf)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(raw) + ft_strlen(buf)) + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	i = -1;
	j = 0;
	while (raw[++i] != '\0')
		str[i] = raw[i];
	while (buf[j] != '\0')
		str[i++] = buf[j++];
	str[ft_strlen(raw) + ft_strlen(buf)] = '\0';
	free(raw);
	return (str);
}
