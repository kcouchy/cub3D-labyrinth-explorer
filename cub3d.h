/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:29:41 by blebas            #+#    #+#             */
/*   Updated: 2024/06/21 12:30:57 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ***************** */
/*      INCLUDES     */
/* ***************** */

# include <fcntl.h>
# include <math.h>
# include "minilibx/mlx42.h"
# include "Libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <stdio.h>

/* ***************** */
/*      DEFINES      */
/* ***************** */

# define DEFAULT_WIN_W 640	// window width in pixels
# define DEFAULT_WIN_H 480	// window height in pixels
# define BLOCK_RES 1000		// height/width/depth of walls (in units)
# define FOV_RAD 1.0472		// 60 degree FOV in radians
# define MOVESPEED 40.0f	// units moved per key hook cycle
# define TURNSPEED 0.05f	// radians for view rotation per key hook cycle

/* ***************** */
/*     STRUCTURES    */
/* ***************** */

typedef struct walltexture
{
	mlx_texture_t	*no_walltexture;	// mlx pointer to texture pngs
	mlx_texture_t	*so_walltexture;
	mlx_texture_t	*we_walltexture;
	mlx_texture_t	*ea_walltexture;
	char			*no_path;			// path to texture pngs
	char			*so_path;
	char			*we_path;
	char			*ea_path;
}		t_walltexture;

typedef struct s_gridpos
{
	double		x;
	double		y;
}	t_gridpos;

typedef struct s_drawwall
{
	char		walldirection;	// NSEW to select correct wall texture
	double		raylength;		// closest hor/vert wall intercept length
	t_gridpos	intercept;		// intercept coordinates for texture mapping
}	t_drawwall;

typedef struct s_data
{
	void			*mlx;
	int				cub_fd;
	double			win_width;
	double			win_height;
	mlx_image_t		*img;
	t_walltexture	walltexture;	// NSEW wall texture paths and pointers
	long			ceiling;		// ceiling colour (RGBA)
	long			floor;			// floor colour (RGBA)
	char			**map;			// copy of map input
	int				map_length;		// in number of squares (chars)
	int				map_height;		// in number of squares (chars)
	double			scalew;			// x scaling factor for minimap
	double			scaleh;			// y scaling factor for minimap
	t_gridpos		pos;			// position of the player
	double			view_dir;		// direction of player's POV in radians
}	t_data;

/******************************************************************************/
/* BUILD_MAZE/DRAW_WALL.C                                                     */
/******************************************************************************/

/**
 * @brief Loads wall texture pngs, stores pointers to them in data.walltexture 
 * structure
 * 
 * @param data input structure
 * @return true all textures are successfully loaded
 * @return false there is an error (message specifies which texture fails)
 */
bool		load_png(t_data *data);

/**
 * @brief Called from the raycasting function, will calculate the appropriate
 * wall size for each image column, retrieve the pixel colours from the 
 * correct wall texture png (with rescaling) using get_texture_color() and 
 * get_texture_side(), and call mlx_put_pixel() to set image memory.
 * 
 * @param data input structure
 * @param drawwall raycasting structure containing intercept information
 * @param i image column (0 -> WIN_W)
 */
void		ft_draw_wall(t_data *data, t_drawwall drawwall, int i);

/******************************************************************************/
/* BUILD_MAZE/FIND_INTERCEPT.C                                                */
/******************************************************************************/

/**
 * @brief Raycasting function to find the closest intercept with a horizontally
 * orientated wall (east-west)
 * 
 * @param data input structure
 * @param angle angle of the current ray in radians
 * @return t_drawwall structure containing:
 * - the ray length from the player to the intercept
 * - the x/y coordinates of the intercept (Returns INFINITY if there is no 
 * intercept or intercept is outside of the map).
 * - the wall orientation (NESW
 */
t_drawwall	find_hor_intercept(t_data *data, double angle);

/**
 * @brief Raycasting function to find the closest intercept with a vertically
 * orientated wall (north-south)
 * 
 * @param data input structure
 * @param angle angle of the current ray in radians
 * @return t_drawwall structure containing:
 * - the ray length from the player to the intercept
 * - the x/y coordinates of the intercept (Returns INFINITY if there is no 
 * intercept or intercept is outside of the map).
 * - the wall orientation (NESW)
 */
t_drawwall	find_vert_intercept(t_data *data, double angle);

/******************************************************************************/
/* BUILD_MAZE/MINIMAP.C                                                       */
/******************************************************************************/

/**
 * @brief Handles the drawing of induvidual minimap squares using the minimap 
 * scalew/h scaling factor.
 * 
 * @param data input structure
 * @param x start coordinates (top left corner) to draw the square
 * @param y start coordinates (top left corner) to draw the square
 * @param colour square colour (RGB: black = map, red = player)
 */
void		ft_draw_square(t_data *data, int x, int y, int colour);

/**
 * @brief Draws the minimap on the top left corner of the screen, scaled to 
 * a maximum size based on the longest map axis (length or width)
 * 
 * @param data input structure
 */
void		ft_draw_minimap(t_data *data);

/******************************************************************************/
/* BUILD_MAZE/MOVEMENTS.C                                                     */
/******************************************************************************/

/**
 * @brief Handles movement (NSEW) calculations, sends to check_and_move() 
 * to make sure the move will not put the player into a wall or beyond the map.
 * 
 * @param data input structure
 * @param angle movement angle in radians
 */
void		move(t_data *data, double angle);

/**
 * @brief Handles head movement/viewpoint rotation (left/right arrow) 
 * calculations, updates data->view_dir with new view direction.
 * Calls functions to redraw image:
 * - ft_put_pixel_to_background() ceiling and floor colours
 * - raycast() draws walls
 * - ft_draw_minimap() draws minimap
 * 
 * @param data input structure
 * @param dir rotation direction
 */
void		rotate(t_data *data, int dir);

/**
 * @brief Generic keyhook function called by mlx_loop_hook()
 * 
 * @param param data structure
 */
void		ft_hook(void *param);

/**
 * @brief Helper function for movements (WASD), checks to make sure the move 
 * will not put the player into a wall (is_wall() or off the map (is_off_map())
 * before updating the player position and calling functions to redraw the 
 * image:
 * - ft_put_pixel_to_background() ceiling and floor colours
 * - raycast() draws walls
 * - ft_draw_minimap() draws minimap
 * 
 * @param data inout structure
 * @param check_wall grid position to check before moving
 */
void		check_and_move(t_data *data, t_gridpos check_wall);

/******************************************************************************/
/* BUILD_MAZE/RAYCAST.C                                                       */
/******************************************************************************/

/**
 * @brief Helper function to ensure viewing and raycasting angles stay within 
 * the range of 0 -> 2 * PI, and are never exactly zero (for calculations to 
 * avoid divide-by-zero errors).
 * 
 * @param angle angle in radians
 * @return double corrected angle (if necessary)
 */
double		norm_angle(double angle);

/**
 * @brief Helper function to ensure that a grid position is within the map 
 * (data->map array).
 * 
 * @param data input structure
 * @param intercept grid position to test
 * @return true intercept position is off the map
 * @return false intercept position is on the map
 */
bool		is_off_map(t_data *data, t_gridpos intercept);

/**
 * @brief Helper function to ensure that a grid position is within the map 
 * (data->map array).
 * 
 * @param data input structure
 * @param intercept grid position to test
 * @return true intercept position is on a wall edge
 * @return false intercept position is not on a wall edge
 */
bool		is_wall(t_data *data, t_gridpos intercept);

/**
 * @brief Calls find_hor_intercept() and find_vert_intercept() to find vertical
 * and horzontal wall intercepts of the ray, returns the shortest one.
 * 
 * @param data input structure
 * @param ray_angle ray being cast in radians
 * @return t_drawwall structure containing:
 * - the ray length from the player to the closest intercept
 * - the x/y coordinates of the closest intercept.
 * - the wall orientation (NESW)
 */
t_drawwall	ray_len(t_data *data, double ray_angle);

/**
 * @brief Calculates raycasting using the window width (WIN_W) and player field
 * of view (FOV_RAD). Calls norm_angle() to keep angle in range, calculates the
 * raylength (shortest of find_hor_intercept() and find_vert_intercept()). Calls
 * ft_draw_wall to draw the wall, then loops over to cover the FOV_RAD.
 * 
 * @param data input structure
 */
void		raycast(t_data *data);

/******************************************************************************/
/* BUILD_MAZE/TEXTURE.C                                                       */
/******************************************************************************/

/**
 * @brief Converts colour from individual pixel values to an int with 8 bits per
 * colour channel (RGBA)
 * 
 * @param r Red (0-255)
 * @param g Green (0-255)
 * @param b Blue (0-255)
 * @param a Alpha (transparency 0-255)
 * @return int32_t Colour as int
 */
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

/**
 * @brief Initiates image using mlx_new_image and related data structure 
 * variables
 * 
 * @param data input structure
 */
void		init_img(t_data *data);

/**
 * @brief Draws image background:
 * - top half = data->ceiling colour
 * - bottom half = data->floor colour
 * 
 * @param data 
 */
void		ft_put_pixel_to_background(t_data *data);

/******************************************************************************/
/* GET_INPUTS/CHECK_MAP.C                                                     */
/******************************************************************************/

/**
 * @brief Helper function to determine if a character is a space:
 * - SPACE
 * - HORIZONTAL/VERTICAL TAB
 * - FORM FEED
 * - CARRIAGE RETURN
 * * BUT NOT NEW LINE
 * 
 * @param c input character
 * @return true if is space
 * @return false if is not space or is new line
 */
bool		is_spc(char c);

/**
 * @brief Helper function to determine if a character is a direction (NSEW)
 * 
 * @param c input character
 * @return true 
 * @return false 
 */
bool		is_direc(char c);

/**
 * @brief Helper function to determine if a character is a valid map character:
 * - 1/0 or is_direc()
 * 
 * @param c input character
 * @return true 
 * @return false 
 */
bool		is_valid(char c);

/**
 * @brief Helps to determine if a map is closed by verifying that all 0s and 
 * is_direc() (representing the player) are surrounded by map characters.
 * 
 * @param map data->map copy of input map
 * @param row map coordinates to check
 * @param col map coordinates to check
 * @return true 
 * @return false 
 */
bool		check_0(char **map, size_t row, size_t col);

/**
 * @brief Checks map contains only valid characters (0,1,N,E,S,W,' '), and is 
 * closed (check_0()).
 * 
 * @param data input map
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			map_is_open(t_data *data);

/******************************************************************************/
/* GET_INPUTS/ERROR.C                                                         */
/******************************************************************************/

/**
 * @brief Frees all malloc'd parts of structure if they have been initialised
 * 
 * @param data input structure to free
 */
void		ft_free(t_data *data);

/**
 * @brief Prints an error message to STDERR_FILENO then calls ft_free
 * 
 * @param type Type of error message
 * @param message Error message
 * @param data input structure to free
 * @return int returns 1
 */
int			ft_errorfree(char *type, char *message, t_data *data);

/**
 * @brief Prints an error message to STDERR_FILENO
 * 
 * @param type Type of error message
 * @param message Error message
 * @return int returns 1
 */
int			ft_error(char *type, char *message);

/******************************************************************************/
/* GET_INPUTS/GET_COLOURS.C                                                   */
/******************************************************************************/

/**
 * @brief Retrieves the colour code (RGB) from the .cub input file, converts to 
 * int (RGBA) using ctoi(colour to int) and _atouc(argument to unsigned char)
 * Checks each component of the colour is valid (0 -> 255), and is given in the
 * format 255,255,255
 * Skips spaces at the beginning of the line, and ignores extraneous infomation
 * after the colour code
 * 
 * @param line line from the .cub file containing the colour
 * @param data input structure
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			get_colours(char *line, t_data *data);

/******************************************************************************/
/* GET_INPUTS/GET_MAP.C                                                       */
/******************************************************************************/

/**
 * @brief Helper function to return the number of rows in an array
 * 
 * @param tab input array
 * @return int number of rows
 */
int			ft_tablen(char **tab);

/**
 * @brief Helper function that checks that the map is the last information to 
 * be extracted from the .cub file. If any of the wall textures are colours are
 * uninitialised, will return an error.
 * 
 * @param data input structure
 * @return true via ft_errorfree()
 * @return false 
 */
bool		is_not_last(t_data *data);

/**
 * @brief Get the map object from the .cub file, copy and store it in data->map.
 * Calls _ft_realloc() to build the map, and verifies that it does not go beyond
 * MAX_INT in either height or width.
 * 
 * @param line line from the .cub file containing the map row
 * @param data input structure
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			get_map(char *line, t_data *data);

/******************************************************************************/
/* GET_INPUTS/GET_TEXTURES.C                                                  */
/******************************************************************************/

/**
 * @brief Retrieves the four texture paths from the .cub input file, and stores
 * them in data.walltexture.XXpath
 * Skips spaces at the beginning of the line, and ignores extraneous infomation
 * after the texture path
 * 
 * @param line line from the .cub file containing the path to wall texture pngs
 * @param data input structure
 * @return int returns 1 via _save_textures(ft_errorfree()) if error, 
 * otherwise 0
 */
int			get_textures(char *line, t_data *data);

/******************************************************************************/
/* GET_INPUTS/GNL.C & GNL_UTILS.C                                             */
/******************************************************************************/

/**
 * @brief Simple version of get_next_line, returns a line read from a file 
 * descriptor. Can only handle one fd at a time.
 * @param fd The file descriptor to read from.
 * @return char * The line that was read or NULL if there is nothing else 
 * to read, or an error occurred, or ctrl+C (SIGINT) was intercepted.
 */
char		*gnl(int fd);

/**
 * @brief Helper for gnl(), to find and return the index of a newline in an 
 * input char string
 * 
 * @param buffer line
 * @return int newline index, or -1 if not found
 */
int			ft_findnl(char *buffer);

/**
 * @brief Helper for gnl(), to copy the entire length of str2 into str1. Used
 * to reset the buffer, shifting the data after a newline to the left (both 
 * pointers are on the same string). There is therefore no check that str1 is 
 * as long or longer than str2.
 * 
 * @param str1 string (pointer) to copy to
 * @param str2 string (pointer) to be copied from
 * @return char* Null-terminated str1
 */
char		*ft_strcpy(char *str1, char *str2);

/******************************************************************************/
/* GET_INPUTS/PARSE_INPUT.C                                                   */
/******************************************************************************/

/**
 * @brief Checks for .cub suffix on the input file
 * 
 * @param argv input file name
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			check_cub(char *argv);

/**
 * @brief Reads input file line by line using gnl(), dispatches to get() 
 * functions and ft_mapsize() to save data to data structure
 * 
 * @param fd input .cub file
 * @param data input structure
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			read_cub(int fd, t_data *data);

/******************************************************************************/
/* GET_INPUTS/PARSE_MAP.C                                                     */
/******************************************************************************/

/**
 * @brief Once the map has been copied to data->map, reallocates to replace 
 * empty part of map with spaces to make it square. Ensures there is only one
 * player start position given (NESW character), and initialises the player 
 * position (data->pos) and view direction in radians (data->view_dir).
 * 
 * @param data input structure
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			parse_map(t_data *data);

/******************************************************************************/
/* MAIN.C                                                                     */
/******************************************************************************/

/**
 * @brief Handles cleanup on game closure. Calls mlx functions to delete 
 * texture pngs, close and terminate the window, and call ft_free().
 * 
 * @param data input structure
 */
void		quit_game(t_data *data);

/**
 * @brief Opens the input .cub file, calls:
 * - read_cub() to read the file and extract the data
 * 
 * @param argv the second input argument (argv[1]) that should correspond to 
 * the full .cub filename
 * @param data input structure
 * @return int returns 1 via ft_errorfree() if error, otherwise 0
 */
int			open_cub(char *argv, t_data *data);

/**
 * @brief Checks the number of input arguments (argc == 2), initialises part of
 * the data structure using data_init().
 * Open input file open_cub(), check map using map_is_open() and parse_map(),
 * verify that wall texture pngs can be successfully loaded using load_png().
 * 
 * @param argc number of input arguments
 * @param argv array of input arguments
 * @return int 1 via ft_error() or ft_errorfree() if error, otherwise 0
 */
int			main(int argc, char **argv);

#endif
