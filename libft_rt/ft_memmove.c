/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 10:09:55 by jwoo              #+#    #+#             */
/*   Updated: 2020/12/31 20:11:12 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	size_t			i;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (ptr_dst > ptr_src)
	{
		i = len;
		while (i-- > 0)
			ptr_dst[i] = ptr_src[i];
		return (dst);
	}
	while (i < len)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}
