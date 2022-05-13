/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:30:28 by asoler            #+#    #+#             */
/*   Updated: 2022/05/13 02:05:22 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define GET_NEXT_LINE_H

typedef struct s_gnl
{
	char	*buf;
	char	*result;
	int		res;
	int		x;
}	t_gnl


char	*get_next_line(int fd);

#endif