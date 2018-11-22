/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:33:55 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/10/27 21:28:41 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <libftprintf.h>

typedef struct		s_stack
{
	struct s_stack	*next;
	struct s_stack	*prev;
	int				value;
}					t_stack;

typedef struct 		s_lists
{
	struct s_lists	*next;
	char			*com;
}					t_lists;

#endif
