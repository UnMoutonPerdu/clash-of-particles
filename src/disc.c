/*

   Copyright 2015-2018 Fabrice Frances
   This work is free. You can redistribute it and/or modify it under the
   terms of the Do What The Fuck You Want To Public License, Version 2,
   as published by Sam Hocevar. See http://www.wtfpl.net/ for more details

*/

// Uncomment the following define to use SDL2.0 instead of SDL1.2,
// or add -DSDL2 to the compile line
//#define SDL2

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include "disc.h"

static int window_width, window_height;

/******************************************************************************************
 * Layer 1: Interface to SDL/SDL2
 ******************************************************************************************/

#ifdef SDL2
#include <SDL2/SDL.h>
static SDL_Renderer *renderer;
static SDL_Window *window;
#else
#include <SDL/SDL.h>
#endif

static SDL_Surface *screen;
static const int MAX_INTENSITY = 255;
static int bpp;

/*
 * Add intensity to the existing intensity value of pixel at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
static void IntensifyPixel(int x, int y, int red, int grn, int blu)
{
    if (x<0 || x>=window_width || y<0 || y>=window_height) return;
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    // TODO: find a better intensity sum function
#if defined(__MACOS__) || defined(__MACOSX__)
#  define B 3
#  define G 2
#  define R 1
#else
#  define B 0
#  define G 1
#  define R 2
#endif
    blu += p[B]; p[B] = blu > MAX_INTENSITY ? MAX_INTENSITY : blu;
    grn += p[G]; p[G] = grn > MAX_INTENSITY ? MAX_INTENSITY : grn;
    red += p[R]; p[R] = red > MAX_INTENSITY ? MAX_INTENSITY : red;
}

void UpdateScreen()
{
#ifdef GUI
#ifdef SDL2
    SDL_RenderPresent(renderer);
#else
    SDL_UpdateRect(screen, 0, 0, window_width, window_height);
#endif
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
        }
    }
#endif
}

static void SigHandler(int signum)
{
    SDL_Quit();
    exit(signum);
}

static void InitSDL(char *title, int width, int height)
{
#ifdef GUI
    if (SDL_Init(SDL_INIT_VIDEO)!=0) {
        fprintf(stderr,"Error in SDL_Init : %s\n",SDL_GetError());
        exit(-1);
    }

#ifdef SDL2
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_SHOWN);

    if (window==NULL) {
        fprintf(stderr,"Error in SDL_CreateWindow : %s\n",SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    screen = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
#else
    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen==NULL) {
        fprintf(stderr,"Error, couldn't set %dx%d video mode : %s\n",
                window_width, window_height, SDL_GetError());
        exit(-1);
    }
    SDL_WM_SetCaption(title, NULL);
#endif

    bpp = screen->format->BytesPerPixel;
    if (bpp < 3) {
        fprintf(stderr,"Please switch to 24 or 32 bits per pixel\n");
        SDL_Quit();
        exit(-1);
    }

    SDL_EventState(SDL_KEYDOWN,         SDL_IGNORE);
    SDL_EventState(SDL_KEYUP,           SDL_IGNORE);
    SDL_EventState(SDL_MOUSEMOTION,     SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP,   SDL_IGNORE);
    SDL_EventState(SDL_SYSWMEVENT,      SDL_IGNORE);
#ifdef SDL2
    SDL_EventState(SDL_MOUSEWHEEL,      SDL_IGNORE);
    SDL_EventState(SDL_WINDOWEVENT,     SDL_IGNORE);
    SDL_EventState(SDL_TEXTEDITING,     SDL_IGNORE);
    SDL_EventState(SDL_TEXTINPUT,       SDL_IGNORE);
#else
    SDL_EventState(SDL_VIDEORESIZE,    SDL_IGNORE);
    SDL_EventState(SDL_VIDEOEXPOSE,    SDL_IGNORE);
    SDL_EventState(SDL_ACTIVEEVENT,    SDL_IGNORE);
#endif
    signal(SIGINT,SigHandler);
    signal(SIGTERM,SigHandler);

    window_width = width;
    window_height = height;
#endif
}

static void TerminateSDL()
{
#ifdef SDL2
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
#endif
    SDL_Quit();
}


/******************************************************************************************
 * Brute force circle draw function in "4K virtual resolution" (tm) ;-)
 ******************************************************************************************/

void DrawDISC(double x0, double y0, double radius, enum color color)
{
#ifdef GUI
    double r2 = radius*radius;
    y0 = window_height-1 - y0;    // reverse y so that 0 is at the bottom of the window
    const double SUB_PIXEL_SIZE = 0.5;
    const int LIGHT_CHUNK = (int)(MAX_INTENSITY * SUB_PIXEL_SIZE * SUB_PIXEL_SIZE);
    const int RED   = color & 1 ? LIGHT_CHUNK : 0;
    const int GREEN = color & 2 ? LIGHT_CHUNK : 0;
    const int BLUE  = color & 4 ? LIGHT_CHUNK : 0;
    IntensifyPixel((int)(x0+0.5),(int)(y0+0.5),RED,GREEN,BLUE);
    for (double dy=SUB_PIXEL_SIZE; dy<=radius; dy+=SUB_PIXEL_SIZE)
    {
        IntensifyPixel((int)(x0+dy+0.5),(int)(y0   +0.5),RED,GREEN,BLUE);
        IntensifyPixel((int)(x0-dy+0.5),(int)(y0   +0.5),RED,GREEN,BLUE);
        IntensifyPixel((int)(x0   +0.5),(int)(y0+dy+0.5),RED,GREEN,BLUE);
        IntensifyPixel((int)(x0   +0.5),(int)(y0-dy+0.5),RED,GREEN,BLUE);
        double limit = r2 - dy*dy;
        for (double dx=SUB_PIXEL_SIZE; dx<=radius && dx*dx<=limit; dx+=SUB_PIXEL_SIZE)
        {
            IntensifyPixel((int)(x0+dx+0.5),(int)(y0+dy+0.5),RED,GREEN,BLUE);
            IntensifyPixel((int)(x0-dx+0.5),(int)(y0+dy+0.5),RED,GREEN,BLUE);
            IntensifyPixel((int)(x0+dx+0.5),(int)(y0-dy+0.5),RED,GREEN,BLUE);
            IntensifyPixel((int)(x0-dx+0.5),(int)(y0-dy+0.5),RED,GREEN,BLUE);
        }
    }
#endif
}

void CreateWindow(char *title, int width, int height)
{
#ifdef GUI
    window_width = width;
    window_height = height;
    InitSDL(title, window_width, window_height);
#endif
}

void EmptySpace()
{
#ifdef GUI
    SDL_Rect all = { 0, 0, window_width, window_height };
    SDL_FillRect(screen, &all, 0);
#endif
}

void WaitClick()
{
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
    SDL_Event event;
    do {
        SDL_WaitEvent(&event);
    } while (event.type!=SDL_MOUSEBUTTONDOWN);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
}

void CloseWindow() {
#ifdef GUI
    TerminateSDL();
#endif
}
