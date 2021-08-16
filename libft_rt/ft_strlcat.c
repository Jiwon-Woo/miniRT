/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:50:15 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/02 17:30:49 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	add;

	if (dst == NULL && src == NULL)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	add = 0;
	while ((add + dst_len + 1 < dstsize) && src[add])
	{
		dst[dst_len + add] = src[add];
		add++;
	}
	dst[dst_len + add] = '\0';
	return (src_len + dst_len);
}
