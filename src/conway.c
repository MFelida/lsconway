/*
 * File: conway.c
 * Project: lsconway
 * Created Date: We Jul 2023
 * Author: Mike Felida
 * -----
 * Last Modified: Wed Jul 05 2023
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

#include "config.h"
#include "conway.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

t_conway g_conway;

int	conway_init(void)
{
	g_conway.current_gen = malloc (sizeof(t_conway_grid));
	g_conway.next_gen = malloc(sizeof(t_conway_grid));

	return 1;
}

int	init_conway_grid(t_conway_grid *grid)
{
	grid->cell_states = malloc(GRID_HEIGHT * size_t(int *));
	grid->cell_states[0] = 
		malloc(GRID_HEIGHT * GRID_WIDTH * sizeof(int));
}

void	update()
{
	
}

void	conway_swap_grids(void)
{
	t_conway_grid *swap;

	swap = g_conway.current_gen;
	g_conway.current_gen =g_conway.next_gen;
	g_conway.next_gen = swap;
}

void	place_pattern(char *filepath, int x, int y)
{
	FILE	*fp;
	char	read_buffer[1024];
	int		i;

	fp = fopen(filepath, "r");
	if (fp == NULL){
		fprintf(stderr, "Failed to open file: %s", filepath);
		return ;
	}
	while (read_line(fp, read_buffer))
	{
		if (read_buffer[0] == '!')
			continue;
		i = 0;
		while (read_buffer[i])
		{
			if (read_buffer[i] == 'O')
				change_cell_state(x + i, y, 1, g_conway.current_gen);
			i++;
		}
		y++;
	}

}

void	change_cell_state(int x, int y, int alive, t_conway_grid *grid)
{
	alive = !!alive;
	if (g_conway.current_gen->cell_states[y][x] == alive)
		return;
	grid->cell_states[y][x] = alive;
	alive += alive - 1;
	for (int iy = y - 1; iy <= y + 1; iy++)
	{
		for (int ix = x - 1; ix <= x + 1; ix++)
		{
			if (ix != x || iy != y)
				grid->neighbor_counts[iy][ix] += alive;
		}
	}
}

t_conway *get_grid(void)
{
	return &g_conway;
}