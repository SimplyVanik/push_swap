/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 16:48:25 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/24 17:42:49 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*list_find_fd(size_t fd, t_list *tl)
{
	t_list	*tmp;

	if (!tl)
		if ((tl = ft_lstnew("", fd)))
		{
			tl->next = tl;
			return (tl);
		}
	tmp = tl->next;
	while (tmp->content_size != fd && tl->content_size != tmp->content_size)
		tmp = tmp->next;
	if (tl->content_size == tmp->content_size && tmp->content_size != fd)
	{
		tmp = tl->next;
		if ((tl->next = ft_lstnew("", fd)))
		{
			tl = tl->next;
			tl->next = tmp;
			tmp = tl;
		}
	}
	return (tmp);
}

static int		rdfile(t_list *tl, char **tmp)
{
	int		num;
	char	*buff;

	if (tl->content)
		*tmp = ft_strchr(tl->content, '\n');
	buff = ft_strnew(BUFF_SIZE);
	while (!(*tmp) && (num = read((int)(tl->content_size), buff, BUFF_SIZE))
	> 0)
	{
		*tmp = tl->content;
		tl->content = ft_strjoin((tl)->content, buff);
		ft_memdel((void**)(tmp));
		ft_strclr(buff);
		*tmp = ft_strchr(tl->content, '\n');
	}
	ft_memdel((void**)(&buff));
	return (num);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*tl;
	char			*tmp;

	tmp = NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1 ||
		rdfile((tl = list_find_fd(fd, tl)), &tmp) < 0)
		return (-1);
	if (!tl->content || *((char*)(tl->content)) == '\0')
	{
		ft_memdel(&(tl->content));
		return (0);
	}
	if (tmp)
	{
		*line = ft_strsub(tl->content, 0, ft_strlen(tl->content) -
			ft_strlen(tmp));
		tmp = ft_strsub(tl->content,
			(int)(ft_strlen(*line) + 1), ft_strlen(tmp + 1));
	}
	else
		*line = ft_strdup(tl->content);
	ft_memdel(&(tl->content));
	tl->content = tmp;
	return (1);
}
