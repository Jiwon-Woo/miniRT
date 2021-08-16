/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:50:41 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/04 14:40:22 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		itoa_sign(int n)
{
	if (n < 0)
		return (-1);
	else if (n == 0)
		return (0);
	else
		return (1);
}

static size_t	itoa_len(int n)
{
	size_t		len;

	len = 0;
	if (itoa_sign(n) <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char			*integer;
	size_t			len;
	size_t			index;
	int				sign;
	unsigned int	num;

	sign = itoa_sign(n);
	len = itoa_len(n);
	num = sign * n;
	integer = (char *)malloc(sizeof(char) * (len + 1));
	if (integer == NULL)
		return (NULL);
	index = len;
	integer[index] = 0;
	while (--index > 0)
	{
		integer[index] = (num % 10) + '0';
		num /= 10;
	}
	if (sign == -1)
		integer[index] = '-';
	else
		integer[index] = num + '0';
	return (integer);
}
