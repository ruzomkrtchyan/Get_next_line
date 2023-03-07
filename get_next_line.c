/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:44:27 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/02/22 18:08:11 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

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
	static char	*left;
	int			j;

	new = 0;
	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left = ft_laveli(fd, left);
	if (!left)
		return (NULL);
	while (left[j] && left[j] != '\n')
		j++;
	new = ft_substr(left, 0, j + 1);
	if (new && !new[0])
	{
		free(left);
		free(new);
		return (0);
	}
	left = ft_hi(left);
	return (new);
}
// int main ()
// {
// 	int		fd;
// 	char	*ptr;

// 	fd = open("text.txt", O_RDONLY);
// 	ptr = get_next_line(fd);
// 	printf("%s", ptr);
// 	ptr = get_next_line(fd);
// 	printf("%s", ptr);
// 	free(ptr);
// 	close(fd);
// 	//system("leaks a.out");
// }
