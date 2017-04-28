/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:26:45 by ebucheit          #+#    #+#             */
/*   Updated: 2016/12/06 13:36:40 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		read_string(int fd, char **saved)
{
	char		*temp;
	int			r_bytes;

	temp = ft_strnew(BUFF_SIZE);
	r_bytes = 1;
	while (r_bytes && ft_strchr(*saved, '\n') == NULL)
	{
		r_bytes = read(fd, temp, BUFF_SIZE);
		if (r_bytes >= 0)
			temp[r_bytes] = '\0';
		else
		{
			ft_strdel(&temp);
			return (-1);
		}
		*saved = ft_strjoin(*saved, temp);
		ft_strclr(temp);
	}
	ft_strdel(&temp);
	return (r_bytes);
}

int				get_next_line(const int fd, char **line)
{
	static char		*saved;
	char			*temp;
	int				r_bytes;

	if (!saved)
		saved = ft_strnew(BUFF_SIZE);
	r_bytes = read_string(fd, &saved);
	if (r_bytes == -1)
	{
		ft_strdel(&saved);
		return (-1);
	}
	if ((temp = ft_strchr(saved, '\n')))
	{
		*temp = '\0';
		*line = ft_strdup(saved);
		saved = temp + 1;
		return (1);
	}
	*line = ft_strdup(saved);
	ft_strdel(&saved);
	ft_strdel(&temp);
	saved = NULL;
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
