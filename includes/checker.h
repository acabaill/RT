/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoutinh <mcoutinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:43:34 by mcoutinh          #+#    #+#             */
/*   Updated: 2017/05/03 16:20:57 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "rtv1.h"
# include <fcntl.h>

/*
** STRUCTS
*/

typedef struct		s_tag
{
	char			*closer;
	struct s_tag	*prev;
	struct s_tag	*next;
}					t_tag;

typedef struct		s_checker
{
	char			*file;
	int				i;
	t_tag			*tags;
}					t_checker;

/*
** FUNCTIONS
*/

#endif
