/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:29:08 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:33:19 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *srce, int c, size_t n)
{
	unsigned int	start;
	unsigned char	*dst;
	unsigned char	*src;
	unsigned char	found;

	dst = (unsigned char*)dest;
	src = (unsigned char*)srce;
	found = (unsigned char)c;
	start = 0;
	while (start < n)
	{
		if ((*dst++ = *src++) == found)
			return (dst);
		start++;
	}
	return (NULL);
}
