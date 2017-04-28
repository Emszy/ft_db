/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:40:59 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:41:00 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str, const char *str2, size_t n)
{
	size_t count;

	count = 0;
	while (count < n)
	{
		if (*str != *str2)
			return ((unsigned char)*str - (unsigned char)*str2);
		if (*str == '\0' && *str2 == '\0')
			return (0);
		str++;
		str2++;
		count++;
	}
	return (0);
}
