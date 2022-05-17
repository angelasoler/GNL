/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:30:28 by asoler            #+#    #+#             */
/*   Updated: 2022/05/17 03:38:35 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# define GET_NEXT_LINE_BONUS_H

char	*get_next_line(int fd);

int		count_remains_lf(char *s, int size);

int		gnl_strlen(char *s);

int		ft_strlen(char *s);

void	ft_strcpy(char *dest, char *src);

#endif