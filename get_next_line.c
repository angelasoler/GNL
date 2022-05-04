/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:04 by asoler            #+#    #+#             */
/*   Updated: 2022/05/04 14:28:03 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int verify_lf(char *s, int size)
{
	// if (*s == '\n')
	// {
	// 	size--;
	// 	return (size);
	// }
	while (*s != '\n' && size)
	{
		s++;
		size--;
		// if (*s == '\n')
		// {
		// 	size--;
		// 	return (size);
		// }
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

char	*buf_backup(char	*dest, char	*src)
{
	int		total;
	char	*result;
	int		l_dest;
	int		i;

	i = 0;
	l_dest = gnl_len(dest);
	total = l_dest  + gnl_len(src) + 1;
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

#include <stdio.h>
char	*get_next_line(int fd)
{
	char		*buf;
	static char	*aux;
	char		*result;
	int			res;
	int			i;
	static int	x;
	// static char cobaia;

	// if (cobaia == 'x')
	// 	return (0);
	i = 0;
	res = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	buf = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	result = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	*result = 0;
	// inicializar com zeros
	while (!res)
	{
		if (aux)
		{
			res = verify_lf(aux, ft_len(aux));
			result = buf_backup(result, aux);
			if (*aux == 10 && ft_len(aux) == 1)
			{
				free(aux);
				aux = 0;
				return (result);
			}
			if (res)
			{
				break;
			}
			free(aux);
			aux = 0;
		}
		x = read(fd, buf, BUFFER_SIZE);
		if (!res && !x)
		{
			if (!x && !*result)
			{
				// printf("%s\n", result);
				// printf("%d\n", x);
				return (0);
			}
			return (result);
		}
		if (x < BUFFER_SIZE)
			buf[x] = 0;
		else
			buf[BUFFER_SIZE] = 0;
		res = verify_lf(buf, ft_len(buf));
		result = buf_backup(result, buf);
	}
	if (res)
	{
		if (!aux)
		{
			aux = malloc(sizeof(char *) * (res));
			while (buf[BUFFER_SIZE - res + 1])
			{
				aux[i] = buf[BUFFER_SIZE - res + 1];
				res--;
				i++;
			}
		}
		else
		{
			
		}
		aux[i] = 0;
	}
	return (result);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	char *result;
	int fd;

	fd = open("file.txt", O_RDONLY);
	result = get_next_line(fd);
	while (result)
	{
		printf("call: ");
		printf("%s", result);
		result = get_next_line(fd);
	}
	close(fd);
	return (0);
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
