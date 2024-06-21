/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:20:30 by kcouchma          #+#    #+#             */
/*   Updated: 2024/06/20 18:21:00 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	_is_id(char c)
{
	return (c == 'F' || c == 'C');
}

static int	_is_num(char c)
{
	return (c >= '0' && c <= '9');
}

static int	_atouc(char **temp)
{
	int	output;

	output = 0;
	if (!(**temp >= '0' && **temp <= '9'))
		return (-1);
	while (**temp >= '0' && **temp <= '9')
	{
		if (output > 255)
			return (-1);
		output = output * 10;
		output = output + **temp - 48;
		(*temp)++;
	}
	if (output > 255)
		return (-1);
	return (output);
}

long	ctoi(char *colours)
{
	long	i;
	long	rgb;
	long	num;
	char	*temp;

	i = 3;
	temp = colours;
	num = 0;
	rgb = 0;
	while (i)
	{
		if (!temp)
			return (-1);
		num = _atouc(&temp);
		if (num == -1)
			return (-1);
		rgb += num;
		rgb <<= 8;
		while (*temp == ',' || is_spc(*temp))
			temp++;
		i--;
	}
	rgb += 255;
	return (rgb);
}

int	get_colours(char *line, t_data *data)
{
	char	*temp;
	char	*colours;
	char	c;
	long	rgb;

	temp = line;
	while (is_spc(*temp))
		temp++;
	c = *temp;
	if (_is_id(*temp))
		temp++;
	while (is_spc(*temp))
		temp++;
	colours = temp;
	while (*temp && (_is_num(*temp) || *temp == ',' || is_spc(*temp)))
		temp++;
	*temp = '\0';
	rgb = ctoi(colours);
	if (rgb == -1)
		return (ft_errorfree("Input", "invalid colour (R,G,B)\n", data));
	if (c == 'F')
		data->floor = rgb;
	else if (c == 'C')
		data->ceiling = rgb;
	return (0);
}
