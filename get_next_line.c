/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:04 by asoler            #+#    #+#             */
/*   Updated: 2022/05/12 16:21:29 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	verify_lf(char *s, int size)
{
	while (*s != '\n' && size)
	{
		s++;
		size--;
	}
	return (size);
}

int	gnl_len(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == '\n')
			return (i);
		i++;
		s++;
	}
	return (i);
}

int	ft_len(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

void	ft_cpy(char *dest, char *src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = 0;
}

char	*buf_backup(char	*dest, char	*src)
{
	int		total;
	char	*result;
	int		l_dest;
	int		i;

	i = 0;
	l_dest = gnl_len(dest);
	total = l_dest + gnl_len(src) + 1;
	result = malloc(total * sizeof(char *));
	while (total)
	{
		while (i < l_dest)
		{
			result[i] = dest[i];
			i++;
			total--;
		}
		result[i] = *src;
		i++;
		src++;
		total--;
	}
	result[i] = 0;
	free(dest);
	return (result);
}

void	ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	ft_error(char *result, char *buf, int x)
{
	if (x < 0 || x > BUFFER_SIZE)
	{
		ft_free(result, buf);
		return (1);
	}
	return (0);
}

#include <stdio.h>
char	*get_next_line(int fd)
{
	char		*buf;
	static char	*aux;
	char		*result;
	int			res;
	int			x;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	result = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*result = 0;
	res = 0;
	while (!res)
	{
		if (aux)
		{
			res = verify_lf(aux, ft_len(aux));
			result = buf_backup(result, aux);
			if (res)
				break ;
			free(aux);
			aux = 0;
		}
		x = read(fd, buf, BUFFER_SIZE);
		if (ft_error(result, buf, x))
			return (0);
		if (!x)
		{
			if (!*result)
			{
				free(result);
				result = 0;
			}
			ft_free(aux, buf);
			return (result);
		}
		buf[x] = 0;
		res = verify_lf(buf, x);
		result = buf_backup(result, buf);
	}
	if (aux)
		ft_cpy(aux, (aux + ft_len(result)));
	else
	{
		aux = malloc(sizeof(char) * (res));
		ft_cpy(aux, (buf + (x - res + 1)));
	}
	free(buf);
	return (result);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main()
// {
// 	char *result;
// 	int fd;

// 	fd = open("file.txt", O_RDONLY);
// 	result = get_next_line(fd);
// 	while (result)
// 	{
// 		printf("call: ");
// 		printf("%s", result);
// 		result = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }

// Repeated calls (e.g., using a loop) to your get_next_line() function should let
// you read the text file pointed to by the file descriptor, one line at a time.
// • Your function should return the line that was read.
// If there is nothing else to read or if an error occurred, it should return NULL.
// • Make sure that your function works as expected both when reading a file and when
// reading from the standard input.
// • Please note that the returned line should include the terminating \n character,
// except if the end of file was reached and does not end with a \n character.
// • Your header file get_next_line.h must at least contain the prototype of the
// get_next_line() function.
// • Add all the helper functions you need in the get_next_line_utils.c file.
