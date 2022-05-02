/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:04 by asoler            #+#    #+#             */
/*   Updated: 2022/05/02 22:49:05 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int verify_lf(char *s, int size)
{
	// if (size < BUFFER_SIZE)
	// 	return (0);
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
	// if (*s == '\n')
	// 	return (1);
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

char	*buf_backup(char	*dest, char	*src)
{
	int		total;
	char	*result;
	int		l_dest;
	int		i;

	i = 0;
	l_dest = gnl_len(dest);
	total = l_dest  + gnl_len(src) + 1;
	result = malloc(total * sizeof(char));
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

#include <stdio.h>
char	*get_next_line(int fd)
{
	char		*buf;
	static char	*aux;
	char		*result;
	int			res;
	int			i;
	static int	x;

	i = 0;
	res = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	result = malloc(sizeof(char) * BUFFER_SIZE);
	// printf("%d\n", x);
	// x = 1;
	// printf("%d\n", x);
	while (!res)
	{
		if (aux)
		{
			res = verify_lf(aux, ft_len(aux));
			result = buf_backup(result, aux);
			// printf("%s\n", result);
			free(aux);
			if (res)
				break;
			aux = 0;
		}
		x = read(fd, buf, BUFFER_SIZE);
		if (!x)
		{
			free(buf);
			free(aux);
			return (0);
		}
		// printf("%d\n", x);
		if (x < BUFFER_SIZE)
			buf[x] = 0;
		else
			buf[BUFFER_SIZE] = 0;
		// printf("%d\n", ft_len(buf));
		res = verify_lf(buf, ft_len(buf));
		result = buf_backup(result, buf);
	}
	// printf("%d\n", res);
	if (res)
	{
		// printf("%d\n", res);
		// if (aux)
		// {
		// 	res = ft_len(aux) - res + 1;
		// 	buf = buf_backup(buf, aux);
		// 	free(aux);
		// }
		// else
			res = BUFFER_SIZE - res + 1;
		aux = malloc(sizeof(char) * res);
		while (buf[res])
		{
			aux[i] = buf[res];
			res++;
			i++;
		}
		aux[i] = 0;
	}
	// printf("%s\n", result);
	return (result);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	char *result;
	int fd;

	fd = open("file.txt", O_RDONLY);
	result = "";
	while (result)
	{
		result = get_next_line(fd);
		printf("%s", result);
		free(result);
	}
	close(fd);
}

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
