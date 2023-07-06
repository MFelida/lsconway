/*
 * File: conway.c
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

#include "config.h"
#include "conway.h"
#include "util.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_conway g_conway;

int		init_conway_grid_arr(int ***grid);
int	init_conway_grid(t_conway_grid *grid);
void	conway_swap_grids(void);
void	change_cell_state(int x, int y, int alive, t_conway_grid *grid);
void current_to_next(void);
void	print_grid(int **grid);
int	wrap_index(int n, int limit);

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
	init_conway_grid_arr(&grid->cell_states);
	if (grid->cell_states == NULL)
		return 0;
	init_conway_grid_arr(&grid->neighbor_counts);
	if (grid->neighbor_counts == NULL)
		return 0;
	return 1;
}

int	init_conway_grid_arr(int ***grid)
{
	*grid = calloc(GRID_HEIGHT, sizeof(int *));
	if (*grid == NULL)
		return 0;
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		(*grid)[i] = 
			calloc(GRID_WIDTH, sizeof(int));
		if ((*grid)[i] == NULL)
			return 0;
	}
	return 1;
}

void	update(void)
{
	static uint32_t last_update = 0;
	int neighbors;
	int live;
	
	if (SDL_GetTicks() - last_update < GEN_DURATION_MS)
		return;

	current_to_next();
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			neighbors = g_conway.current_gen->neighbor_counts[y][x];
			live = g_conway.current_gen->cell_states[y][x];
			if (neighbors == 3)
				change_cell_state(x, y, 1, g_conway.next_gen);
			else if (neighbors == 2 && live)
				change_cell_state(x, y, 1, g_conway.next_gen);
			else if (live)
				change_cell_state(x, y, 0, g_conway.next_gen);
		}
	}
	conway_swap_grids();
	last_update = SDL_GetTicks();
}

void	draw_from_mouse(void)
{
	int x;
	int y;
	uint32_t state = SDL_GetMouseState(&x, &y);
	
	if (!(state & SDL_BUTTON(1)))
		return;

	if (x > 0 && x < WINDOW_WIDTH
		&& y > 0 && y < WINDOW_HEIGHT)
	{
		change_cell_state(
			x / CELL_SIZE,
			y / CELL_SIZE,
			1,
			g_conway.current_gen);
	}
}

void	conway_swap_grids(void)
{
	t_conway_grid *swap;

	swap = g_conway.current_gen;
	g_conway.current_gen = g_conway.next_gen;
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
	if (g_conway.current_gen->cell_states[y][x] == alive)
		return;
	grid->cell_states[y][x] = alive;
	alive += alive - 1;
	for (int iy = y - 1; iy <= y + 1; iy++)
	{
		for (int ix = x - 1; ix <= x + 1; ix++)
		{
			if (ix == x && iy == y)
				continue;
			grid->neighbor_counts[wrap_index(iy, GRID_HEIGHT)][wrap_index(ix, GRID_WIDTH)] += alive;
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

void	current_to_next(void)
{
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		memcpy(g_conway.next_gen->neighbor_counts[i],
				g_conway.current_gen->neighbor_counts[i], GRID_WIDTH * sizeof(int));
		memcpy(g_conway.next_gen->cell_states[i],
				g_conway.current_gen->cell_states[i], GRID_WIDTH * sizeof(int));
	}
}

void	print_grid(int **grid)
{
	for (int j = 0; j < GRID_HEIGHT; j++)
	{
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			fprintf(stderr, "%d ", grid[j][i]);
		}
		fprintf(stderr, "\n");
	}
}

int	wrap_index(int n, int limit)
{
	if (n < 0)
		return n + limit;
	if (n >= limit)
		return n - limit;
	return n;
}