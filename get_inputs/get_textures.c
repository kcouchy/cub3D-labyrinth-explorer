/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:20:27 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/07 13:37:38 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	_is_id(char c)
{
	return (c == 'N' || c == 'O' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'A');
}

static int	_save_texture(char *path, char **target)
{
	if (*target)
		return (1);
	*target = path;
	return (0);
}

static int	_save_textures(char *path, t_data *data, char c)
{
	if (c == 'N')
		if (_save_texture(path, &data->walltexture.no_path))
			return (ft_errorfree("Input", "duplicate NO wall texture\n", data));
	if (c == 'S')
		if (_save_texture(path, &data->walltexture.so_path))
			return (ft_errorfree("Input", "duplicate SO wall texture\n", data));
	if (c == 'W')
		if (_save_texture(path, &data->walltexture.we_path))
			return (ft_errorfree("Input", "duplicate WE wall texture\n", data));
	if (c == 'E')
		if (_save_texture(path, &data->walltexture.ea_path))
			return (ft_errorfree("Input", "duplicate EA wall texture\n", data));
	return (0);
}

int	get_textures(char *line, t_data *data)
{
	char	*temp;
	char	*path;
	char	c;

	temp = line;
	while (is_spc(*temp))
		temp++;
	c = *temp;
	while (_is_id(*temp))
		temp++;
	while (is_spc(*temp))
		temp++;
	path = ft_strdup(temp);
	if (!path)
		return (1);
	temp = path;
	while (*temp && !is_spc(*temp))
		temp++;
	*temp = '\0';
	if (_save_textures(path, data, c))
	{
		free(path);
		return (1);
	}
	return (0);
}
