/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:01:05 by vdzhanaz          #+#    #+#             */
/*   Updated: 2017/11/08 15:01:07 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char *))
{
	int i;

	if (s && f)
	{
		i = -1;
		while (s[++i] != '\0')
			f(&s[i]);
	}
}
