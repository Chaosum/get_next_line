/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:42:54 by mservage          #+#    #+#             */
/*   Updated: 2021/01/29 13:42:56 by mservage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line			*ft_foundfd(int fd, t_line *list)
{
	t_line	*temp;

	temp = list;
	if (fd < 0)
		return (0);
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	return (0);
}

t_line			*new_fd(int fd, t_line *list)
{
	t_line *temp[2];

	temp[1] = list;
	temp[0] = NULL;
	while (temp[1])
	{
		if (temp[1]->fd == fd)
			return (list);
		temp[1] = temp[1]->next;
	}
	if (!(temp[0] = malloc(sizeof(t_line))))
		return (0);
	if (!(temp[0]->stock = malloc(sizeof(char))))
	{
		free(temp[0]);
		return (0);
	}
	temp[0]->stock[0] = 0;
	temp[0]->fd = fd;
	temp[0]->next = list;
	list = temp[0];
	return (temp[0]);
}

int				ft_reading(int fd, char *buf, t_line *lst, char **line)
{
	int		i;
	int		ret;
	char	*join;

	i = 0;
	while ((ret = read(fd, buf, BUFFER_SIZE)) >= 0 && (BUFFER_SIZE > 0))
	{
		buf[ret] = 0;
		join = ft_join_buf(lst->stock, buf);
		while ((join[i] != '\n') && (join[i] != 0))
			i++;
		if (join[i] == '\n')
			if ((*line = ft_treatment_nl(join, *line, i, lst)))
				return (1);
		if (ret == 0)
			if ((*line = ft_treatment_zero(join, i, *line)))
				return (0);
		if ((join[i] != '\n'))
			if ((*line = ft_treatment_nol(join, *line, ret, lst)))
				return (0);
	}
	return (-1);
}

t_line			*ft_free_struck(t_line *lst, t_line *temp)
{
	t_line *temp2;

	temp2 = lst;
	if (temp == lst && lst)
		lst = lst->next;
	else if (lst && temp)
	{
		while (temp2->next != temp)
			temp2 = temp2->next;
		temp2->next = temp->next;
	}
	free(temp->stock);
	free(temp);
	return (lst);
}

int				get_next_line(int fd, char **line)
{
	static t_line		*lst = NULL;
	char				*buf;
	int					result;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		if (lst)
			lst = ft_free_struck(lst, NULL);
		return (-1);
	}
	if (fd < 0 || !line || (!(lst = new_fd(fd, lst))) || (read(fd, buf, 0) < 0))
	{
		free(buf);
		if (lst)
			lst = ft_free_struck(lst, ft_foundfd(fd, lst));
		return (-1);
	}
	result = ft_reading(fd, buf, ft_foundfd(fd, lst), line);
	if (result == 0 || result == -1)
		lst = ft_free_struck(lst, ft_foundfd(fd, lst));
	free(buf);
	return (result);
}
