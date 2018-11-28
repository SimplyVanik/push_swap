/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sup_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/27 21:57:23 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_check(char *s, int par, t_head *head, int j)
{
	int		i;
	long	res;
	long	count;
	char	**tmp;

	tmp = ft_strsplit(s, ' ');
	j = 0;
	while (tmp[j] != NULL)
		j++;
	while (--j >= 0)
	{
		i = ft_strlen(tmp[j]);
		res = 0;
		count = 1;
		while (--i >= 0 && tmp[j][i] > 47 && tmp[j][i] < 58 && res < 2147483649)
		{
			res = res + count * (tmp[j][i] - 48);
			count = count * 10;
		}
		res = (i == 0 && tmp[j][i] == '-') ? -1 * res : res;
		(((res > 2147483647 || res < -2147483648) &&
		ft_printf("Error. %d element isn't integer\n", par + j)) || (i > -1 &&
		!((ft_strlen(tmp[j]) > 1) && i == 0 && (tmp[j][i] == '-' || tmp[j][i] ==
		'+')) && ft_printf("Error. %d isn't digital \n", par))) ? exit(1) : 0;
		head->a = ft_addelement((int)(res), head->a, par + j);
	}
	ft_masdel(&tmp);
}

int		ft_get_stack_size(t_stack *head)
{
	int		res;
	t_stack	*tmp;

	if (head == NULL)
		return (0);
	res = 1;
	tmp = head->next;
	while (tmp->value != head->value)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int		ft_is_it_piv(t_stack *tmp, int num, int res, t_stack *head)
{
	int		i;
	int		less;

	i = -1;
	less = 0;
	while (i++ == -1 || (tmp->value != head->value && (i < num ||
	i < -1 * num)))
	{
		if (tmp->value <= res)
			less++;
		tmp = tmp->next;
	}
	if ((num - 2 * less <= 0 && num - 2 * less >= -1) ||
	(num + 2 * less >= 0 && num + 2 * less <= 1))
		return (1);
	else
		return (0);
}

int		ft_find_pivot(t_stack *head, int num)
{
	t_stack	*tmp;
	int		cur;
	int		res;
	int		i;

	cur = -1;
	while (++cur < num || cur < -1 * num)
	{
		i = (num > 0) ? -1 : 1;
		tmp = head;
		while (num > 0 && ++i < cur)
			tmp = tmp->next;
		while (num < 0 && --i > cur + num)
			tmp = tmp->prev;
		res = tmp->value;
		tmp = (num > 0) ? head : tmp;
		while (i-- > num)
			tmp = tmp->prev;
		if (ft_is_it_piv(tmp, num, res, head) == 1)
			return (res);
	}
	return (res);
}

t_stack	*ft_addelement(int to_add, t_stack *head, int par)
{
	t_stack	*tmp;

	tmp = head;
	if (head == NULL)
	{
		head = ft_memalloc(sizeof(t_stack));
		head->next = head;
		head->prev = head;
		head->value = to_add;
		return (head);
	}
	while (tmp->next != head && tmp->value != to_add)
		tmp = tmp->next;
	if (tmp->value == to_add &&
	ft_printf("Error. %d element is duplicated\n", par))
		exit(1);
	tmp->next = ft_memalloc(sizeof(t_stack));
	(tmp->next)->prev = tmp;
	tmp = tmp->next;
	tmp->value = to_add;
	tmp->next = head;
	head->prev = tmp;
	return (tmp);
}
