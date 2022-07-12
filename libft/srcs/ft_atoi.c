/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:01:58 by telee             #+#    #+#             */
/*   Updated: 2022/06/01 13:12:43 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		a;
	long	integer;
	long	sign;

	a = 0;
	integer = 0;
	sign = 1;
	while (str[a] && (str[a] == 32 || (str[a] > 8 && str[a] < 14)))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{	
		if (str[a] == '-')
			sign *= -1;
		a++;
	}
	while (str[a] && str[a] > 47 && str[a] < 58)
	{
		if (((integer * 10) / 10 != integer) && sign == -1)
			return (0);
		if (((integer * 10) / 10 != integer) && sign == 1)
			return (-1);
		integer = integer * 10 + (str[a] - 48);
		a++;
	}
	return (sign * integer);
}
