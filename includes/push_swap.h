/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:33:55 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/22 18:58:57 by vdzhanaz         ###   ########.fr       */
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

typedef struct		s_lists
{
	struct s_lists	*next;
	char			*com;
}					t_lists;

typedef struct		s_head
{
	t_stack			*a;
	t_stack			*b;
	t_lists			*lst;
}					t_head;

void	ft_check(char *s, int par, t_head *head);
int		ft_get_stack_size(t_stack *head);
int		ft_find_pivot(t_stack *head, int num);
t_stack	*ft_addelement(int to_add, t_stack *head, int par);
void	ft_swap(t_stack *head, char mark, t_lists *lst);
void	ft_push(t_head *head, char mark);
t_stack	*ft_rotating(t_stack *head, char mark, char rmark, t_lists *lst);
void	ft_sort_b_bottom(t_head *head, int num);
void	ft_sort_b_top(t_head *head, int num);
void	ft_ab_top(t_head *head, int num_a);
void	ft_b_bottom_3(t_head *head, int num);
void	ft_a_bot_3(t_head *head, int num_a);
void	ft_omg_sort(t_head *head, int num_a, int num_b, int b_size);
void	ft_make_sort(t_head *head, int num_a, int num_b);
void	ft_sort_b(t_head *head, int *blocks);
int		ft_backtrack(t_head *head, int *nums, int fl, int k);
void	ft_sort_a(t_head *head, int *block, int fl);
void	ft_sort(t_head *head, int i);
void	ft_optimize(t_lists *lst);

#endif
