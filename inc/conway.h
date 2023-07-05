

#ifndef CONWAY_H
# define CONWAY_H
#include "config.h"

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

void update();

void change_cell_state(int x, int y, int alive, t_conway_grid *grid);
t_conway *get_grid(void);

#endif

