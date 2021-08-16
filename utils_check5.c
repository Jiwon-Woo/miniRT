/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:10 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_specifier(char **factor, t_rt *rt)
{
	if (ft_strlen(factor[0]) == 0 || ft_strlen(factor[0]) == -1)
		return (0);
	else if (ft_strlen(factor[0]) == 1 && ft_strncmp(factor[0], "R\0", 2) == 0)
		return (check_r(factor, rt));
	else if (ft_strlen(factor[0]) == 1 && ft_strncmp(factor[0], "A\0", 2) == 0)
		return (check_a(factor, rt));
	else if (ft_strlen(factor[0]) == 1 && ft_strncmp(factor[0], "c\0", 2) == 0)
		return (check_c(factor, rt));
	else if (ft_strlen(factor[0]) == 1 && ft_strncmp(factor[0], "l\0", 2) == 0)
		return (check_l(factor, rt));
	else if (ft_strlen(factor[0]) == 2 && ft_strncmp(factor[0], "sp\0", 3) == 0)
		return (check_sp(factor, rt));
	else if (ft_strlen(factor[0]) == 2 && ft_strncmp(factor[0], "pl\0", 3) == 0)
		return (check_pl(factor, rt));
	else if (ft_strlen(factor[0]) == 2 && ft_strncmp(factor[0], "sq\0", 3) == 0)
		return (check_sq(factor, rt));
	else if (ft_strlen(factor[0]) == 2 && ft_strncmp(factor[0], "cy\0", 3) == 0)
		return (check_cy(factor, rt));
	else if (ft_strlen(factor[0]) == 2 && ft_strncmp(factor[0], "tr\0", 3) == 0)
		return (check_tr(factor, rt));
	else
		return (-1);
}

int		check_line(char *line, t_rt *rt)
{
	int		ret;
	int		word;
	char	**factor;
	int		i;

	word = word_num(line);
	factor = split_space(line);
	if (factor == 0)
		return (-1);
	ret = check_specifier(factor, rt);
	i = -1;
	while (++i < word)
	{
		free(factor[i]);
		factor[i] = 0;
	}
	free(factor);
	factor = 0;
	return (ret);
}

int		check_arg_ret_fd(int argc, char **argv)
{
	int	fd;
	int	argv_len;

	if (argc == 1 || argc > 3 ||
		(argc == 3 && ft_strncmp(argv[2], "--save\0", 7) != 0))
	{
		printf("Invalid argument.\nERROR!\n");
		return (-1);
	}
	argv_len = ft_strlen(argv[1]);
	if (argv_len <= 3 || ft_strncmp(argv[1] + argv_len - 3, ".rt\0", 4) != 0)
	{
		printf("This is not an rt file.\nERROR!\n");
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		printf("Unavailable fd number.\nERROR!\n");
		return (-1);
	}
	return (fd);
}

int		read_file_gnl(int fd, t_rt *rt)
{
	int		ret;
	char	*line;

	line = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (check_line(line, rt) == -1)
			break ;
		free(line);
	}
	if (ret < 0)
	{
		printf("Fail to read file.\nERROR!\n");
		return (-1);
	}
	if (check_line(line, rt) == -1)
	{
		printf("Invaild input for rt file.\nERROR!\n");
		free(line);
		return (-1);
	}
	free(line);
	return (1);
}

int		check_rt_file(int fd, t_rt *rt)
{
	if (read_file_gnl(fd, rt) == -1)
		return (-1);
	if (rt->r.screen_x <= 0 || rt->r.screen_y <= 0 || rt->a.ratio <= 0 ||
		vec3_len(rt->a.color) == 0.0 || ft_lstsize(rt->c) == 0)
	{
		printf("There are no required factors.\nError!\n");
		return (-1);
	}
	return (1);
}
