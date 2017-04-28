/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:41:45 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:41:47 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!*little)
		return ((char *)big);
	if (!*big || len == 0)
		return (NULL);
	if (*big == *little)
		if (ft_strnstr(big + 1, little + 1, len - 1) - 1 == big)
			return ((char *)big);
	return (ft_strnstr(big + 1, little, len - 1));
}
