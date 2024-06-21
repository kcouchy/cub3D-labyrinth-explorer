/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:52:06 by blebas            #+#    #+#             */
/*   Updated: 2024/06/20 17:00:38 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_square(t_data *data, int x, int y, int colour)
{
	int	y_buf;
	int	x_buf;

	y_buf = y;
	x_buf = x;
	while (x < (data->scalew + x_buf))
	{
		y = y_buf;
		while (y < (data->scaleh + y_buf))
		{
			if (x > 0 && y > 0 && x < data->win_width && y < data->win_height)
				mlx_put_pixel(data->img, x, y, colour);
			y++;
		}
		x++;
	}
}

void	ft_draw_minimap(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				ft_draw_square(data, (j * data->scalew) + 20,
					(i * data->scaleh) + 20, ft_pixel(0, 0, 0, 255));
			else if (data->map[i][j] == '0' || is_direc(data->map[i][j]))
				ft_draw_square(data, (j * data->scalew) + 20,
					(i * data->scaleh) + 20, ft_pixel(255, 255, 255, 100));
			j++;
		}
		i++;
	}
	ft_draw_square(data,
		(((data->pos.x - BLOCK_RES / 2) / BLOCK_RES) * data->scalew) + 20,
		(((data->pos.y - BLOCK_RES / 2) / BLOCK_RES) * data->scaleh) + 20,
		ft_pixel(255, 0, 0, 255));
}
