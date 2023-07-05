
#include "config.h"
#include "conway.h"
#include "util.h"

#include <stdio.h>

t_conway g_conway;

int	conway_init(void)
{

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

t_conway *get_grid(void)
{
	return &g_conway;
}