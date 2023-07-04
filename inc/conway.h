

#ifndef CONWAY_H
# define CONWAY_H

typedef struct s_conway_grid
{
	int **cell_states;
	int **neighbor_counts;
} t_conway_grid;

typedef struct s_conway
{
	int 			width;
	int 			height;
	t_conway_grid	*current_gen;
	t_conway_grid	*next_gen;
} t_conway;

#endif