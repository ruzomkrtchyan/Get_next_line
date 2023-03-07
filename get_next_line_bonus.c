/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:48:00 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/02/22 15:17:35 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

char	*ft_hi(char *a)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = a;
	while (a[i] && a[i] != '\n')
		i++;
	if (a[i] == '\0')
	{
		free(a);
		return (0);
	}
	a = ft_substr(a, i + 1, ft_strlen(a) - i - 1);
	free(ptr);
	return (a);
}

char	*ft_laveli(int fd, char *left)
{
	char	*buff;
	int		i;

	i = 0;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!ft_strchr(left, '\n'))
	{
		i = read (fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		if (i == 0)
			break ;
		left = ft_strjoin(left, buff);
	}
	free(buff);
	return (left);
}

char	*get_next_line(int fd)
{
	char		*new;
	static char	*left[OPEN_MAX];
	int			j;

	new = 0;
	j = 0;
	if (fd > OPEN_MAX)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	left[fd] = ft_laveli(fd, left[fd]);
	if (!left[fd])
		return (NULL);
	while (left[fd][j] && left[fd][j] != '\n')
		j++;
	new = ft_substr(left[fd], 0, j + 1);
	if (new && !new[0])
	{
		free(left[fd]);
		free(new);
		return (0);
	}
	left[fd] = ft_hi(left[fd]);
	return (new);
}
// int main ()
// {
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	char	*ptr;

// 	fd1 = open("text.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd1));
// 	fd2 = open("text1.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd2));
// 	fd3 = open("text2.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd3));
// 	printf("%s", get_next_line(fd3));
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }
