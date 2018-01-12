/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 00:39:56 by ltran             #+#    #+#             */
/*   Updated: 2017/09/06 17:31:04 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 100

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);
char	*ft_no(int fd, char *buf, int num, int r);
int		ft_read(int fd, char *buf, int r);

#endif
