/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:37:54 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:37:55 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str, const char *str2)
{
	while ((*str != '\0') && (*str == *str2))
	{
		str++;
		str2++;
	}
	return ((unsigned char)*str - (unsigned char)*str2);
}
