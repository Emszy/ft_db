/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:40:01 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:40:04 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t index;
	size_t ret;

	index = 0;
	while (dst[index] && index < size)
		index++;
	ret = index;
	while (src[index - ret] && index < size - 1)
	{
		dst[index] = src[index - ret];
		index++;
	}
	if (ret < size)
		dst[index] = '\0';
	return (ret + ft_strlen(src));
}
