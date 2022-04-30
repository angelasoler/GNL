/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:04 by asoler            #+#    #+#             */
/*   Updated: 2022/04/30 21:13:01 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int verify_lf(char *s, int size)
{
	while (*s != '\n' && size)
	{
		s++;
		size--;
	}
	return (size);
}

// void	buf_backup(char	*dest, char	*src, int	start)
// {
	
// }

#include <stdio.h>
char	*get_next_line(int fd)
{
	char		*buf;
	// char		*buf2;
	// static char	*aux;
	int			res;
	static int	i;

	i = 0;
	res = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!res)
	{
		read(fd, buf, BUFFER_SIZE);
		res = verify_lf(buf, BUFFER_SIZE);
		printf("%d\n", res);
		i++;
	}
	printf("%d\n", i);
		// buf2 = malloc((sizeof(char) * ((i * BUFFER_SIZE) - res + 1))
	return (buf);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	char *result;
	result = get_next_line(open("file.txt", O_RDONLY));

	printf("%s\n", result);
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
