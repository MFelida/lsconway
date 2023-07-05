/*
 * File: display.c
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

#include "display.h"
#include "config.h"

#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window		*window;
SDL_Renderer	*renderer;

int	initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return 0;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_INPUT_GRABBED);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return 0;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return 0;
	}
	atexit(destroy_window);
	return 1;
}

void	destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void	get_input(int *game_running)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		*game_running = 0;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			*game_running = 0;
		break;
	default:
		break;
	}
}

void	render(void)
{
	SDL_Rect	rect;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int x = CELL_SIZE; x < WINDOW_WIDTH; x += CELL_SIZE)
	{
		rect.h = WINDOW_HEIGHT;
		rect.w = 1;
		rect.x = x - 1;
		rect.y = 0;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
		SDL_RenderFillRect(renderer, &rect);
	}
	SDL_RenderPresent(renderer);
}