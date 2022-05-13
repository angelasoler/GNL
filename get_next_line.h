/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:30:28 by asoler            #+#    #+#             */
/*   Updated: 2022/05/13 16:15:08 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H_
# include <unistd.h>
# include <stdlib.h>
# define GET_NEXT_LINE_H_

char	*get_next_line(int fd);

#endif