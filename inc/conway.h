/*
 * File: conway.h
 * Project: lsconway
 * Created Date: We Jul 2023
 * Author: Mike Felida
 * -----
 * Last Modified: Thu Jul 06 2023
 * Modified By: Mike Felida
 * -----
 * Copyright (c) 2023 Mike Felida
 * -----
 * zlib License
 * 
 * This software is provided 'as-is', without any express or implied warranty.  In
 * no event will the authors be held liable for any damages arising from the use
 * of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, including
 * commercial applications, and to alter it and redistribute it freely, subject to
 * the following restrictions:
 * 
 *      1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software in a
 * product, an acknowledgment in the product documentation would be appreciated
 * but is not required.
 * 
 *      2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 *      3. This notice may not be removed or altered from any source distribution.
 */

#ifndef CONWAY_H
# define CONWAY_H
#include "config.h"

#include <SDL2/SDL.h>

typedef struct s_conway_grid
{
	int **cell_states;
	int **neighbor_counts;
} t_conway_grid;

typedef struct s_conway
{
	int				w;
	int				h;
	t_conway_grid	*current_gen;
	t_conway_grid	*next_gen;
} t_conway;

int				get_cell_state(int x, int y);
int				conway_init(void);
void			update(void);
t_conway_grid	*get_grid(void);
void			place_pattern(char *filepath, int x, int y);
void	draw_from_mouse();

#endif

