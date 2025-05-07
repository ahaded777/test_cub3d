/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:29:49 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/04 11:35:22 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		r = (r * 10) + (str[i] - 48);
		if (r > 255)
			ft_print_error("Error\nColor value must be between 0 and 255.\n");
		i++;
	}
	if (str[i] || r > 255)
		return (-1);
	return (r);
}
