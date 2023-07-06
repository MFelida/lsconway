/*
 * File: main.c
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
#include "display.h"
#include "conway.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>

int main(int argc, char *argv[])
{
	char bin_path[PATH_MAX];
	char pattern_path[PATH_MAX];
	int	game_running;

	if (argc > 1)
		strcpy(pattern_path, argv[1]);
	else 
		strcpy(pattern_path, "patterns/gosperglidergun.cells");

	memset(bin_path, 0, PATH_MAX);
	strncpy(bin_path, SDL_GetBasePath(), PATH_MAX);
	strncat(bin_path, "../", PATH_MAX - strlen(bin_path) - 1);
	strncat(bin_path, pattern_path, PATH_MAX - strlen(bin_path) - 1);

	game_running = conway_init();
	if (game_running)
		place_pattern(bin_path, 10, 10);
	game_running = game_running && initialize_window();
	while (game_running)
	{
		get_input(&game_running);
		update();
		render();
		SDL_Delay(FRAME_TIME_MS);
	}
	fprintf(stderr, "End of main reached.\n");
}