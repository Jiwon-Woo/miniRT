/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:50:24 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/02 17:31:37 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;
	size_t	src_len;

	size = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (dstsize > 0)
	{
		while (src[size] && size + 1 < dstsize)
		{
			dst[size] = src[size];
			size++;
		}
		dst[size] = '\0';
	}
	src_len = 0;
	while (src[src_len])
		src_len++;
	return (src_len);
}
