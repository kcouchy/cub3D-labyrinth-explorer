/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:05:02 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/20 17:25:48 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_spc(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == 'f');
}

bool	is_direc(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

bool	is_valid(char c)
{
	return (c == '1' || c == '0' || is_direc(c));
}

bool	check_0(char **map, size_t row, size_t col)
{
	size_t	nb_rows;

	nb_rows = 0;
	while (map[nb_rows])
		nb_rows++;
	if (row == 0 || col == 0 || row == nb_rows - 1)
		return (1);
	if (col >= ft_strlen(map[row - 1])
		|| col >= ft_strlen(map[row + 1]))
		return (1);
	if (!is_valid(map[row - 1][col]) ||
			!is_valid(map[row + 1][col]) ||
			!is_valid(map[row][col - 1]) ||
			!is_valid(map[row][col + 1]))
		return (1);
	return (0);
}

int	map_is_open(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!(is_valid(data->map[i][j]) == 1
				|| data->map[i][j] == ' '))
				return (ft_errorfree("Map",
						"invalid character (use 0,1,N,E,S,W,' ')\n", data));
			if (data->map[i][j] == '0' || is_direc(data->map[i][j]))
			{
				if (check_0(data->map, i, j))
					return (ft_errorfree("Map", "invalid map\n", data));
			}
			j++;
		}
		i++;
	}
	return (0);
}
