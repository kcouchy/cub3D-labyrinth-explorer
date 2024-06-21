/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:18:54 by blebas            #+#    #+#             */
/*   Updated: 2024/06/21 12:30:09 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	length_map(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (j > len)
				len++;
			j++;
		}
		i++;
	}
	return (len);
}

void	init_img(t_data *data)
{
	double	max_dimension;

	data->map_length = length_map(data);
	data->map_height = ft_tablen(data->map);
	if (data->map_length >= data->map_height)
		max_dimension = data->map_length;
	else
		max_dimension = data->map_height;
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->scalew = data->win_width / (max_dimension * (data->win_width / 125));
	data->scaleh = data->win_height / (max_dimension * (data->win_height / 125));
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	ft_put_pixel_to_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->win_width)
	{
		y = 0;
		while (y < data->win_height)
		{
			if (y < data->win_height / 2)
				mlx_put_pixel(data->img, x, y, data->ceiling);
			else
				mlx_put_pixel(data->img, x, y, data->floor);
			y++;
		}
		x++;
	}
}
