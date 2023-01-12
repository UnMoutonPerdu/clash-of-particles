/*
 *
 *    Copyright 2015-2018 Fabrice Frances
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
 */

/**
 * @file disc.h
 * @brief Draw DISCs with SDL
 *
 * This module exposes a few functions to ease the use of the SDL library,
 * and a DISC drawing routine.
 * 
 * Use -lm -lSDL when compiling in order to link with math library and SDL library.
 *
 * @author Fabrice Frances
 * @date 23 Jan 2018
 */ 




/**
 * This function creates a SDL window
 *
 * @param title the window title
 * @param width the window width (in pixels)
 * @param height the window height (in pixels)
 */ 	
extern void CreateWindow(char *title, int width, int height);

/**
 * This function terminates the graphical program
 */
extern void CloseWindow(void);

/**
 * This function waits for a mouse click in the SDL window.
 *
 * This is useful for pausing your program without having the cpu run at 100%...
 */
extern void WaitClick(void);

/**
 * This enumeration lists simple colors
 */
enum color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

/**
 * This function clears the window.
 */
extern void EmptySpace(void);

/**
 * This function draws a DISC with "extended-4K virtual resolution" (tm ;-)
 *
 * @param x_center the X coordinate of the DISC center
 * @param y_center the Y coordinate of the DISC center
 * @param radius the radius of the DISC
 * @param color the color of the DISC
 */
extern void DrawDISC(double x_center, double y_center, double radius, enum color color);

/**
 * This function updates the screen display. 
 * Use it when all drawings are done.
 */
extern void UpdateScreen(void);
