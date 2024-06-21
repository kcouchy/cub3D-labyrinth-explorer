/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:46:18 by blebas            #+#    #+#             */
/*   Updated: 2024/06/20 15:48:44 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	load_png(t_data *data)
{
	data->walltexture.so_walltexture = mlx_load_png(data->walltexture.so_path);
	if (!data->walltexture.so_walltexture)
		return (ft_errorfree("Texture", "Can't load texture (SO)\n", data));
	data->walltexture.ea_walltexture = mlx_load_png(data->walltexture.ea_path);
	if (!data->walltexture.ea_walltexture)
		return (ft_errorfree("Texture", "Can't load texture (EA)\n", data));
	data->walltexture.no_walltexture = mlx_load_png(data->walltexture.no_path);
	if (!data->walltexture.no_walltexture)
		return (ft_errorfree("Texture", "Can't load texture (NO)\n", data));
	data->walltexture.we_walltexture = mlx_load_png(data->walltexture.we_path);
	if (!data->walltexture.we_walltexture)
		return (ft_errorfree("Texture", "Can't load texture (WE)\n", data));
	return (0);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t		*pixel;

	if (tex_x >= (int)texture->width)
		tex_x = (int)texture->width - 1;
	if (tex_y >= (int)texture->height)
		tex_y = (int)texture->height - 1;
	if (tex_x < 0 || tex_y < 0)
		return (0xFF000000);
	pixel = texture->pixels
		+ (tex_y * texture->width + (texture->width - 1 - tex_x))
		* texture->bytes_per_pixel;
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8)
		| pixel[3]);
}

mlx_texture_t	*get_texture_side(t_data *data, t_drawwall drawwall)
{
	mlx_texture_t	*texture_wall;

	if (drawwall.walldirection == 'N')
		texture_wall = data->walltexture.no_walltexture;
	if (drawwall.walldirection == 'S')
		texture_wall = data->walltexture.so_walltexture;
	if (drawwall.walldirection == 'W')
		texture_wall = data->walltexture.we_walltexture;
	if (drawwall.walldirection == 'E')
		texture_wall = data->walltexture.ea_walltexture;
	return (texture_wall);
}

static void	_ft_draw_wall2(t_drawwall drawwall, t_gridpos *tex,
	mlx_texture_t *texture)
{
	if (drawwall.walldirection == 'N')
		tex->x = ((int)drawwall.intercept.x % BLOCK_RES);
	else if (drawwall.walldirection == 'S')
		tex->x = (BLOCK_RES - ((int)drawwall.intercept.x % BLOCK_RES));
	else if (drawwall.walldirection == 'E')
		tex->x = ((int)drawwall.intercept.y % BLOCK_RES);
	else if (drawwall.walldirection == 'W')
		tex->x = (BLOCK_RES - ((int)drawwall.intercept.y % BLOCK_RES));
	tex->x = (tex->x * texture->width) / BLOCK_RES;
}

void	ft_draw_wall(t_data *data, t_drawwall drawwall, int i)
{
	double			proj_height;
	int				start;
	t_gridpos		tex;
	double			scale;
	mlx_texture_t	*texture;

	proj_height = (((data->win_width / 2) / tan(FOV_RAD / 2)) * BLOCK_RES)
		/ drawwall.raylength;
	start = (data->win_height / 2) - (proj_height / 2);
	if (start < 0)
		start = 0;
	texture = get_texture_side(data, drawwall);
	tex.y = 0;
	if (proj_height >= data->win_height)
		tex.y = ((proj_height - data->win_height) / 2)
			* (texture->height / proj_height);
	_ft_draw_wall2(drawwall, &tex, texture);
	scale = texture->height / proj_height;
	while (proj_height-- > 0 && start < data->win_height)
	{
		mlx_put_pixel(data->img, i, start++,
			get_texture_color(texture, tex.x, tex.y));
		tex.y += scale;
	}
}
