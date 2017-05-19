/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 09:42:07 by pmartin           #+#    #+#             */
/*   Updated: 2016/07/19 12:21:41 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 30
# include <unistd.h>
# include "../libft/includes/libft.h"

int				get_next_line(int const fd, char **line);
typedef struct	s_cheat
{
	char		*temp;
	char		*buff;
	int			i;
	int			j;
}				t_cheat;
#endif
