/*
 * File: config.h
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

#ifndef CONFIG_H
# define CONFIG_H

#define WINDOW_WIDTH	1600
#define WINDOW_HEIGHT	1000

#define FPS				240
#define FRAME_TIME_MS	(1000.0/FPS)

#define GEN_PER_SECOND	30
#define GEN_DURATION_MS	(1000.0/GEN_PER_SECOND)

#define CELL_SIZE		4
#define	CELL_SPACING	2
#define GRID_WIDTH		(WINDOW_WIDTH / CELL_SIZE)
#define GRID_HEIGHT		(WINDOW_HEIGHT / CELL_SIZE)

#endif