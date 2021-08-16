/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:20:25 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/04 13:22:57 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	put_sign(int n)
{
	if (n < 0)
		return (-1);
	else if (n == 0)
		return (0);
	else
		return (1);
}

static void	put_num(unsigned int num, int fd)
{
	if (num < 10)
	{
		num = num + '0';
		write(fd, &num, 1);
		return ;
	}
	put_num(num / 10, fd);
	put_num(num % 10, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	int				sign;
	unsigned int	num;

	sign = put_sign(n);
	if (sign == -1)
		write(fd, "-", 1);
	num = sign * n;
	put_num(num, fd);
}
