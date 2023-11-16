/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcallejo <mcallejo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:38:53 by mcallejo          #+#    #+#             */
/*   Updated: 2023/11/14 20:15:31 by mcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

char	*ft_join_raw_line(int fd, char *buf, int n_read, char *raw_line)
{
	if (!raw_line)
	{
		raw_line = (char *)malloc(1 * sizeof(char));
		if (!raw_line)
			return (NULL);
		raw_line[0] = '\0';
	}
	raw_line = ft_strjoin(raw_line, buf);
	if (!raw_line)
		return (NULL);
	while (n_read > 0 && (ft_strchr(buf, '\n') == NULL))
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read == -1)
		{
			free(raw_line);
			return (NULL);
		}
		buf[n_read] = '\0';
		if (n_read > 0)
			raw_line = ft_strjoin(raw_line, buf);
		if (!raw_line)
			return (NULL);
	}
	return (raw_line);
}

char	*get_lines(char *raw_line)
{
	int		i;
	char	*line;

	i = 0;
	while (raw_line[i] != '\0')
	{
		if (raw_line[i++] == '\n')
			break;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (raw_line[i] != '\n' && raw_line[i] != '\0')
	{
		line[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
	{
		line[i] = '\n';
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
		return (NULL);
	i = 0;
	while (raw_line[i] != '\n' && raw_line[i] != '\0')
		i++;
	if (raw_line[i] == '\0')
	{
		free(raw_line);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(raw_line) - i));
	if (!new)
	{
		ft_free(&raw_line);
		return (NULL);
	}
	i++;
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
	char			buf[BUFFER_SIZE + 1];
	int				n_read;

	n_read = read(fd, buf, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0 || (n_read == 0 && raw_line == NULL) || (n_read == -1))
	{
		return (ft_free(&raw_line));
	}
	buf[n_read] = '\0';
	raw_line = ft_join_raw_line(fd, buf, n_read, raw_line);
	if (!raw_line)
		return (NULL);
	line = get_lines(raw_line);
	raw_line = new_raw_line(raw_line);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*ret;

// 	fd = open("file.txt", O_RDONLY | O_CREAT);
// 	ret = (get_next_line(fd));
// 	printf("%s", ret);
// 	ret = (get_next_line(fd));
// 	printf("2 %s", ret);
// 	ret = (get_next_line(1000));
// 	printf("%s", ret);
// 	fd = open("file.txt", O_RDONLY);
// 	ret = (get_next_line(fd));
// 	printf("4 %s", ret);
// 	ret = (get_next_line(fd));
// 	printf("5 %s", ret);
// 	ret = (get_next_line(fd));
// 	printf("6 %s", ret);
// 	ret = (get_next_line(fd));
// 	printf("7 %s", ret); 
// 	ret = (get_next_line(100));
// 	printf(" 8%s", ret);
// 	free(ret);
// 	close(fd);
// 	return (0);
// }
