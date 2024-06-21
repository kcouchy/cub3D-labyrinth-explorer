/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:27:34 by blebas            #+#    #+#             */
/*   Updated: 2024/06/20 15:40:59 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move(t_data *data, double angle)
{
	t_gridpos	check_wall;
	t_drawwall	x;
	t_drawwall	y;
	double		len;

	len = MOVESPEED;
	x = find_hor_intercept(data, norm_angle(angle));
	y = find_vert_intercept(data, norm_angle(angle));
	if (x.raylength < y.raylength)
		len = x.raylength;
	else
		len = y.raylength;
	if (len < 0)
		len = -len;
	if (len > MOVESPEED)
		len = MOVESPEED;
	check_wall.x = data->pos.x + cos(angle) * len;
	check_wall.y = data->pos.y - sin(angle) * len;
	return (check_and_move(data, check_wall));
}

void	rotate(t_data *data, int dir)
{
	data->view_dir = norm_angle(data->view_dir - (TURNSPEED * dir));
	ft_put_pixel_to_background(data);
	raycast(data);
	ft_draw_minimap(data);
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(data, -1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(data, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move(data, data->view_dir);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move(data, data->view_dir - M_PI);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move(data, data->view_dir + M_PI_2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(data, data->view_dir - M_PI_2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	ft_put_pixel_to_background(data);
	raycast(data);
	ft_draw_minimap(data);
}

void	check_and_move(t_data *data, t_gridpos check_wall)
{
	if (is_off_map(data, check_wall) || is_wall(data, check_wall))
		return ;
	data->pos.x = check_wall.x;
	data->pos.y = check_wall.y;
}
