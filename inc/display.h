

#ifndef DISPLAY_H
# define DISPLAY_H

#include <SDL2/SDL.h>

int		initialize_window(SDL_Window *window, SDL_Renderer *renderer);
void	destroy_window(SDL_Window *window, SDL_Renderer *renderer);
void	get_input(int *game_running);
void	render(SDL_Renderer *renderer);
#endif