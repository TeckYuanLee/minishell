/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:06:40 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:29:29 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	a;

	a = n;
	if (a < 0)
	{
		ft_putchar_fd('-', fd);
		a *= -1;
	}
	if (a > 9)
	{
		ft_putnbr_fd((a / 10), fd);
		ft_putnbr_fd((a % 10), fd);
	}
	else if (a <= 9)
		ft_putchar_fd((a + 48), fd);
}
