/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intercept.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:08:28 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/20 15:02:23 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define OFFSET 0.000001

void	find_first_hor(t_data *data, double angle, t_gridpos *hor_int,
	t_drawwall *hor_wall)
{
	if (angle < M_PI)
	{
		hor_int->y = (int)(data->pos.y / BLOCK_RES) * BLOCK_RES - OFFSET;
		hor_wall->walldirection = 'S';
	}
	else
	{
		hor_int->y = (int)(data->pos.y / BLOCK_RES) * BLOCK_RES + BLOCK_RES;
		hor_wall->walldirection = 'N';
	}
	hor_int->x = data->pos.x + ((data->pos.y - hor_int->y) / tan(angle));
}

t_drawwall	find_hor_intercept(t_data *data, double angle)
{
	t_gridpos	hor_int;
	t_drawwall	hor_wall;

	find_first_hor(data, angle, &hor_int, &hor_wall);
	while (!is_off_map(data, hor_int) && !is_wall(data, hor_int))
	{
		if (angle < M_PI)
		{
			hor_int.y -= BLOCK_RES;
			hor_int.x += BLOCK_RES / tan(angle);
		}
		if (angle >= M_PI)
		{
			hor_int.y += BLOCK_RES;
			hor_int.x -= BLOCK_RES / tan(angle);
		}
	}
	if (is_off_map(data, hor_int))
		hor_wall.raylength = INFINITY;
	else
		hor_wall.raylength = sqrt(pow(fabs(data->pos.x - hor_int.x), 2)
				+ pow(fabs(data->pos.y - hor_int.y), 2));
	hor_wall.intercept.x = hor_int.x;
	hor_wall.intercept.y = hor_int.y;
	return (hor_wall);
}

void	find_first_vert(t_data *data, double angle, t_gridpos *vert_int,
	t_drawwall *vert_wall)
{
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		vert_int->x = ((int)(data->pos.x / BLOCK_RES) * BLOCK_RES) - OFFSET;
		vert_wall->walldirection = 'E';
	}
	else
	{
		vert_int->x = ((int)(data->pos.x / BLOCK_RES) * BLOCK_RES) + BLOCK_RES;
		vert_wall->walldirection = 'W';
	}
	vert_int->y = data->pos.y + ((data->pos.x - vert_int->x) * tan(angle));
}

t_drawwall	find_vert_intercept(t_data *data, const double angle)
{
	t_gridpos	vert_int;
	t_drawwall	vert_wall;

	find_first_vert(data, angle, &vert_int, &vert_wall);
	while (!is_off_map(data, vert_int) && !is_wall(data, vert_int))
	{
		if (angle > M_PI_2 && angle < 3 * M_PI_2)
		{
			vert_int.x -= BLOCK_RES;
			vert_int.y += BLOCK_RES * tan(angle);
		}
		if (angle <= M_PI_2 || angle >= 3 * M_PI_2)
		{
			vert_int.x += BLOCK_RES;
			vert_int.y -= BLOCK_RES * tan(angle);
		}
	}
	if (is_off_map(data, vert_int))
		vert_wall.raylength = INFINITY;
	else
		vert_wall.raylength = sqrt(pow(fabs(data->pos.x - vert_int.x), 2)
				+ pow(fabs(data->pos.y - vert_int.y), 2));
	vert_wall.intercept.x = vert_int.x;
	vert_wall.intercept.y = vert_int.y;
	return (vert_wall);
}
