/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 10:09:32 by jwoo              #+#    #+#             */
/*   Updated: 2020/12/31 18:42:45 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			len;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (n == 0 || (&ptr1 == &ptr2))
		return (0);
	len = 0;
	while (len + 1 < n)
	{
		if (ptr1[len] != ptr2[len])
			break ;
		if (ptr1[len] == ptr2[len])
			len++;
	}
	return (ptr1[len] - ptr2[len]);
}
