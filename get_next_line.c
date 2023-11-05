/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcallejo <mcallejo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:38:53 by mcallejo          #+#    #+#             */
/*   Updated: 2023/11/05 20:18:17 by mcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

char	*ft_join_raw_line(int fd, char *raw_line)
{
	char		*buf;
	int			n_read;

	buf = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(raw_line);
		return (NULL);
	}
	n_read = 1;
	while ((ft_strchr(buf, '\n') == NULL) && n_read != 0)
	{
		n_read = read(fd, buf, BUFFER_SIZE + 1);
		if (n_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n_read] = '\0';
		raw_line = ft_strjoin(raw_line, buf);
		if (!raw_line)
			return (NULL);
	}
	free(buf);
	return (raw_line);
}

char	*get_line(char *raw_line)
{
	int		i;
	char	*line;

	i = 0;
	if (!raw_line)
		return (NULL);
	while (raw_line[i] != '\n' && raw_line[i] != '\0')
		i++;
	line = (char *)malloc((sizeof(char *) * i) + 1);
	if (!line)
	{
		free(raw_line);//
		return (NULL);
	}
	i = 0;
	while (raw_line[i] != '\n' && raw_line[i] != '\0')
	{
		line[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
	{
		line[i] = raw_line[i];
		i++;
	}	
	line[i] = '\0';
	return (line);
}

char	*new_raw_line(char *raw_line)
{
	int				i;
	int				j;
	char			*new;

	if (!raw_line)
	{
		free(raw_line);
		return (NULL);
	}
	i = 0;
	while (raw_line[i] != '\n' && raw_line[i] != '\0')
		i++;
	i++;
	new = (char *)malloc((sizeof(char *)) * (ft_strlen(raw_line) - i +1));
	if (!new)
	{
		free(raw_line);
		return (NULL);
	}
	j = 0;
	while (raw_line[i] != '\0')
		new[j++] = raw_line[i++];
	new[j] = '\0';
	free(raw_line);
	return (new);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*raw_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(raw_line);
		return (NULL);
	}
	raw_line = ft_join_raw_line(fd, raw_line);
	if (!raw_line)
	{
		free(raw_line);
		return (NULL);
	}
	line = get_line(raw_line);
	raw_line = new_raw_line(raw_line);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*ret;

	fd = open ("file.txt", O_RDONLY | O_CREAT);
	ret = (get_next_line(fd));
	printf("ret:%s", ret);
	ret = (get_next_line(fd));
	printf("ret:%s", ret);
	ret = (get_next_line(fd));
	printf("ret:%s", ret);
	ret = (get_next_line(fd));
	printf("ret:%s", ret);
	ret = (get_next_line(fd));
	printf("ret:%s", ret);

	return (0);
 }
