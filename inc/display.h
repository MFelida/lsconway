

#ifndef DISPLAY_H
# define DISPLAY_H

#include <SDL2/SDL.h>

int		initialize_window(void);
void	destroy_window(void);
void	get_input(int *game_running);
void	render(void);
#endif