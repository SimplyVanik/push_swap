/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:33:55 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/25 20:50:24 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <libftprintf.h>

# define RESET				"\033[0m"
# define B_CYAN				"\033[1;36m"
# define B_YELLOW			"\033[1;33m"
# define BLUE				"\033[0;34m"
# define YELLOW				"\033[0;33m"
# define GREEN				"\033[0;32m"
# define PURPLE				"\033[0;35m"
# define RED				"\033[0;31m"

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

void				ft_check(char *s, int par, t_head *head, int j);
int					ft_get_stack_size(t_stack *head);
int					ft_is_it_piv(t_stack *tmp, int num, int res, t_stack *head);
int					ft_find_pivot(t_stack *head, int num);
t_stack				*ft_addelement(int to_add, t_stack *head, int par);
void				ft_swap(t_stack *head, char mark, t_lists *lst);
t_stack				*ft_make_to(char mark, t_stack *tmp, t_stack *to,
					t_head *head);
void				ft_push(t_head *head, char mark);
t_stack				*ft_rotating(t_stack *head, char mark, char rmark,
					t_lists *lst);
void				ft_sort_b_bottom(t_head *head, int num);
void				ft_sort_b_top(t_head *head, int num);
void				ft_ab_top(t_head *head, int num_a);
void				ft_b_bottom_3(t_head *head, int num);
void				ft_a_bot_3(t_head *head, int num_a);
void				ft_omg_sort(t_head *head, int num_a, int num_b, int b_size);
void				ft_make_sort(t_head *head, int num_a, int num_b);
void				ft_make_b(t_head *head, int *blocks, int i, int j);
void				ft_sort_b(t_head *head, int *blocks, int j, int piv);
int					ft_backtrack(t_head *head, int *nums, int fl, int k);
void				ft_sort_a(t_head *head, int *block, int fl);
void				ft_sort(t_head *head, int i);
void				ft_optimize(t_lists *lst);
t_stack				*ft_make_to_check(t_stack *tmp, t_stack *to);
void				ft_push_check(t_head *head, char *com, char fl);
void				ft_swap_check(t_head *head, char *com, char fl);
void				ft_rotate_check(t_head *head, char *com, char fl);
void				ft_debug(t_head *head);
void				ft_debug_a(t_stack *head, char *com, int i);
void				ft_debug_b(t_stack *head, char *com, int i);
void				ft_sort_stack(t_head *head, char fl);

#endif
