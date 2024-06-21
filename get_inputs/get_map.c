/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:30:11 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/20 16:50:33 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

bool	is_not_last(t_data *data)
{
	if (data->walltexture.no_path == NULL)
		return (ft_errorfree("Input",
				"incomplete .cub file (missing NO)\n", data));
	if (data->walltexture.so_path == NULL)
		return (ft_errorfree("Input",
				"incomplete .cub file (missing SO)\n", data));
	if (data->walltexture.we_path == NULL)
		return (ft_errorfree("Input",
				"incomplete .cub file (missing WE)\n", data));
	if (data->walltexture.ea_path == NULL)
		return (ft_errorfree("Input",
				"incomplete .cub file (missing EA)\n", data));
	if (data->floor == -1)
		return (ft_errorfree("Input",
				"incomplete .cub file (missing F)\n", data));
	if (data->ceiling == -1)
		return (ft_errorfree("Input",
				"incomplete .cub file (missing C)\n", data));
	return (0);
}

static char	**_ft_realloc(char **tab)
{
	size_t		i;
	size_t		len;
	char		**output;

	i = -1;
	len = ft_tablen(tab);
	output = malloc(sizeof(char *) * (len + 2));
	if (!output)
		return (NULL);
	while (++i < len)
	{
		output[i] = tab[i];
		if (i >= INT_MAX)
		{
			free(output);
			free(tab);
			return (NULL);
		}
	}
	output[i] = NULL;
	output[i + 1] = NULL;
	free(tab);
	return (output);
}

int	get_map(char *line, t_data *data)
{
	size_t	i;

	data->map = _ft_realloc(data->map);
	if (!data->map)
		return (ft_errorfree("Map", "map is too large\n", data));
	i = ft_tablen(data->map);
	if (i >= INT_MAX)
		return (ft_errorfree("Map", "map is too large\n", data));
	(data->map)[i] = ft_strdup(line);
	if (!(data->map)[i])
		return (1);
	return (0);
}
