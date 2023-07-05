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

int		init_conway_grid_arr(int **);
int	init_conway_grid(t_conway_grid *grid);
void	conway_swap_grids(void);
void	change_cell_state(int x, int y, int alive, t_conway_grid *grid);

int	conway_init(void)
{
	g_conway.current_gen = calloc(1, sizeof(t_conway_grid));
	if (g_conway.current_gen == NULL)
		return 0;
	g_conway.next_gen = calloc(1, sizeof(t_conway_grid));
	if (g_conway.next_gen == NULL)
		return 0;
	if (init_conway_grid(g_conway.current_gen) == 0)
		return 0;
	if (init_conway_grid(g_conway.next_gen) == 0)
		return 0;
	return 1;
}

int	init_conway_grid(t_conway_grid *grid)
{
	init_conway_grid_arr(grid->cell_states);
	if (grid->cell_states == NULL)
		return 0;
	init_conway_grid_arr(grid->neighbor_counts);
	if (grid->neighbor_counts == NULL)
		return 0;
	return 1;
}

int	init_conway_grid_arr(int **grid)
{
	grid = calloc(GRID_HEIGHT, sizeof(int *));
	if (grid == NULL)
		return 0;
	grid[0] = 
		calloc(GRID_HEIGHT * GRID_WIDTH, sizeof(int));
	if (grid[0] == NULL)
		return 0;
	for (int i = 1; i < GRID_HEIGHT; i++)
	{
		grid[i] = grid[0] + i * GRID_WIDTH;
	}
	return 1;
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

int	get_cell_state(int x, int y)
{
	return g_conway.current_gen->cell_states[y][x];
}

t_conway_grid *get_grid(void)
{
	return g_conway.current_gen;
}