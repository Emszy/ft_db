/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:34:27 by ebucheit          #+#    #+#             */
/*   Updated: 2016/10/03 14:44:55 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char*)dst;
	i = 0;
	while (i < len)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (dst);
}
