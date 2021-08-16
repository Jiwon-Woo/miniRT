/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:22 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:26 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*empty_line(void)
{
	char	*ret;

	ret = (char *)malloc(1);
	if (ret == 0)
		return (0);
	ret[0] = 0;
	return (ret);
}

static char	*str_char_append(char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	len = ft_strlen(str);
	if (str == 0)
		return (0);
	ret = (char *)malloc(len + 2);
	if (ret == 0)
		return (0);
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	ret[len] = c;
	ret[len + 1] = 0;
	free(str);
	str = 0;
	return (ret);
}

static int	ret_gnl(char **line, char *gnl, int rs)
{
	if (rs == 0)
	{
		*line = gnl;
		gnl = 0;
		return (0);
	}
	if (rs < 0 && gnl != 0)
	{
		free(gnl);
		gnl = 0;
	}
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	static char *gnl[OPEN_MAX];
	char		buf;
	int			rs;

	if (fd < 0 || fd > OPEN_MAX || line == 0)
		return (-1);
	if (gnl[fd] == 0)
		gnl[fd] = empty_line();
	while ((rs = read(fd, &buf, 1)) > 0)
	{
		if (buf == '\n')
		{
			*line = gnl[fd];
			gnl[fd] = 0;
			return (1);
		}
		gnl[fd] = str_char_append(gnl[fd], buf);
	}
	return (ret_gnl(line, gnl[fd], rs));
}
