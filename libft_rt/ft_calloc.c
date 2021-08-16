/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 00:01:47 by jwoo              #+#    #+#             */
/*   Updated: 2020/12/31 23:35:40 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = NULL;
	if (count * size == 0)
	{
		ptr = malloc(1);
		if (ptr == NULL)
			return (NULL);
		*(char *)ptr = 0;
	}
	else
	{
		ptr = malloc(count * size);
		if (ptr == NULL)
			return (NULL);
		while (i < count * size)
			((char *)ptr)[i++] = 0;
	}
	return (ptr);
}
