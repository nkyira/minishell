/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:10:50 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/23 12:11:05 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

static char	*ft_read(int fd, char *line)
{
	char	*buf;
	int		p;

	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (!line)
		line = ft_calloc(1, 1);
	p = 1;
	while (p > 0)
	{
		p = read(fd, buf, BUFFER_SIZE);
		if (p == -1)
		{
			free (line);
			free (buf);
			return (NULL);
		}
		buf[p] = 0;
		line = ft_join_and_free(line, buf);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(buf);
	return (line);
}

static char	*clean_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free (line);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(line) - i + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (line[++i])
	{
		str[j] = line[i];
		j++;
	}
	str[j] = '\0';
	free (line);
	return (str);
}

static char	*return_line(char *sentence, char *line)
{
	int	i;

	i = 0;
	if (!sentence)
		return (NULL);
	while (line[i] && line[i] != '\n')
	{
		sentence[i] = line[i];
		i++;
	}
	if (line[i] && line[i] == '\n')
	{
		sentence[i] = '\n';
	}
	return (sentence);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*sentence;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	line = ft_read(fd, line);
	if (!line)
		return (NULL);
	if (!line[0])
	{
		line = clean_line(line);
		return (NULL);
	}
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		sentence = ft_calloc(sizeof(char), (i + 2));
	else
		sentence = ft_calloc(sizeof(char), (i + 1));
	sentence = return_line(sentence, line);
	line = clean_line(line);
	return (sentence);
}
