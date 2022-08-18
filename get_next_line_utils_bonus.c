/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:43:28 by mservage          #+#    #+#             */
/*   Updated: 2021/01/29 13:43:30 by mservage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char			*ft_join_buf(char *src, char *buf)
{
	char		*dest;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!(src) && !(buf))
		return (0);
	i = ft_strlen(src);
	j = ft_strlen(buf);
	if (!(dest = malloc(sizeof(char) * i + j + 1)))
		return (NULL);
	i = 0;
	j = 0;
	if (src[0])
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
	if (buf[0])
		while (buf[j])
			dest[i++] = buf[j++];
	dest[i] = 0;
	return (dest);
}

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char			*ft_treatment_nl(char *join, char *dest, int i, t_line *lst)
{
	int j;
	int k;

	j = -1;
	k = 0;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	while (join[++j] != '\n' && (join[j]))
		dest[j] = join[j];
	dest[j] = 0;
	j++;
	free(lst->stock);
	if (!(lst->stock = malloc(sizeof(char) * (ft_strlen(&join[j]) + 1))))
		return (0);
	while (join[j])
	{
		lst->stock[k] = join[j];
		j++;
		k++;
	}
	lst->stock[k] = 0;
	if (join)
		free(join);
	return (dest);
}

char			*ft_treatment_nol(char *join, char *dest, int ret, t_line *lst)
{
	int j;

	j = -1;
	if (ret == BUFFER_SIZE)
	{
		free(lst->stock);
		if (!(lst->stock = malloc(sizeof(char) * (ft_strlen(join) + 1))))
			return (0);
		while (join[++j])
			lst->stock[j] = join[j];
		lst->stock[j] = 0;
		dest = 0;
	}
	else if (ret < BUFFER_SIZE)
	{
		if (!(dest = malloc(sizeof(char) * ft_strlen(join) + 1)))
			return (0);
		while (join[++j])
			dest[j] = join[j];
		dest[j] = 0;
	}
	free(join);
	return (dest);
}

char			*ft_treatment_zero(char *join, int i, char *dest)
{
	int j;

	j = 0;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	while (join[j])
	{
		dest[j] = join[j];
		j++;
	}
	dest[j] = 0;
	if (join)
		free(join);
	return (dest);
}
