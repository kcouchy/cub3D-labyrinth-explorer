/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:57:04 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/20 13:37:52 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_cub(char *argv)
{
	char	*cub;
	int		i;
	int		j;

	cub = ".cub";
	i = ft_strlen(argv);
	j = ft_strlen(cub);
	if (i < j)
		return (1);
	while (j > 0)
	{
		if (argv[i] != cub[j])
			return (1);
		j--;
		i--;
	}
	return (0);
}

int	empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_spc(line[i]))
			break ;
		i++;
	}
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

int	extract_data(char *line, t_data *data)
{
	char	*temp;

	temp = line;
	while (is_spc(*temp))
		temp++;
	if (!strncmp(temp, "NO", 2) || !strncmp(temp, "SO", 2)
		|| !strncmp(temp, "WE", 2) || !strncmp(temp, "EA", 2))
	{
		if (get_textures(line, data))
			return (1);
	}
	else if (!strncmp(temp, "F", 1) || !strncmp(temp, "C", 1))
	{
		if (get_colours(line, data))
			return (1);
	}
	else
	{
		if (is_not_last(data))
			return (1);
		if (get_map(line, data))
			return (1);
	}
	return (0);
}

void	ft_mapsize(t_data *data)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	data->map_height = ft_tablen(data->map);
	data->map_length = 0;
	while (i < (size_t)data->map_height)
	{
		line_len = ft_strlen(data->map[i++]);
		if (line_len > (size_t)data->map_length)
			data->map_length = line_len;
	}
}

int	read_cub(int fd, t_data *data)
{
	char	*line;

	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!empty_line(line))
		{
			if (extract_data(line, data))
			{
				free(line);
				return (1);
			}
		}
		free(line);
	}
	if (is_not_last(data))
		return (1);
	if (!data->map)
		return (ft_errorfree("Input", "incomplete .cub file (no map)\n", data));
	ft_mapsize(data);
	return (0);
}
