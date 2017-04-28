/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:32:58 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:33:00 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ca;
	int				index;

	index = 0;
	ca = (unsigned char)c;
	ptr = (unsigned char*)s;
	while (n--)
	{
		if (ptr[index] == ca)
			return (ptr + index);
		index++;
	}
	return (NULL);
}
