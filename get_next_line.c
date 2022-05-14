/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:04 by asoler            #+#    #+#             */
/*   Updated: 2022/05/14 02:38:02 by asoler           ###   ########.fr       */
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

int	ft_error(char **result, char *buf, int x)
{
	if (x < 0 || x > BUFFER_SIZE)
	{
		free(*result);
		*result = 0;
		free(buf);
		return (1);
	}
	if (!x)
	{
		if (!*result[0])
		{
			free(*result);
			*result = 0;
		}
		free(buf);
		return (1);
	}
	return (0);
}

void	save_aux(char **aux, char *result, char *buf, int remains)
{
	if (*aux)
		ft_cpy(*aux, (*aux + ft_len(result)));
	else
	{
		*aux = malloc(sizeof(char) * (remains));
		ft_cpy(*aux, (buf));
	}
}

int	add_aux_to_result(char **aux, char **result)
{
	int	remains;

	if (*aux)
	{
		remains = verify_lf(*aux, ft_len(*aux));
		*result = buf_backup(*result, *aux);
		if (!remains)
		{
			free(*aux);
			*aux = 0;
		}
	}
	else
		remains = 0;
	return (remains);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*aux;
	char		*result;
	int			remains;
	int			x;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	result = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*result = 0;
	remains = add_aux_to_result(&aux, &result);
	while (!remains)
	{
		x = read(fd, buf, BUFFER_SIZE);
		if (ft_error(&result, buf, x))
			return (result);
		buf[x] = 0;
		remains = verify_lf(buf, x);
		result = buf_backup(result, buf);
	}
	save_aux(&aux, result, (buf + (x - remains + 1)), remains);
	free(buf);
	return (result);
}
