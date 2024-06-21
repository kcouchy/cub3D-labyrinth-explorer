/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:26:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/20 17:31:43 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	_free_table(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	ft_free(t_data *data)
{
	if (data->walltexture.no_path)
		free(data->walltexture.no_path);
	if (data->walltexture.so_path)
		free(data->walltexture.so_path);
	if (data->walltexture.we_path)
		free(data->walltexture.we_path);
	if (data->walltexture.ea_path)
		free(data->walltexture.ea_path);
	if (data->map)
		_free_table(data->map);
	if (data->cub_fd != -1)
		close (data->cub_fd);
}

int	ft_errorfree(char *type, char *message, t_data *data)
{
	write (STDERR_FILENO, "Error\n", 6);
	write (STDERR_FILENO, type, ft_strlen(type));
	write (STDERR_FILENO, " error: ", 8);
	write (STDERR_FILENO, message, ft_strlen(message));
	ft_free(data);
	return (1);
}

int	ft_error(char *type, char *message)
{
	write (STDERR_FILENO, "Error\n", 6);
	write (STDERR_FILENO, type, ft_strlen(type));
	write (STDERR_FILENO, " error: ", 8);
	write (STDERR_FILENO, message, ft_strlen(message));
	return (1);
}
