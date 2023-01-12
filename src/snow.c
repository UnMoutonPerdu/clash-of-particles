/*
 * Copyright 2018 F. Frances
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the DWTFYWT Public License, Version 2,
 * as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
 *
 * Compile:
 *
 * gcc -Wall -O3 disc.c snow.c -lm -lSDL
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "disc.h"

/* Window size */
#define SIZE 900

typedef struct snowflake *snowflake;
struct snowflake { double x, y, radius, vx, vy; enum color color; };

void generate_snow(int nb, snowflake cloud[nb], unsigned int seed)
{
    srand(seed);
    const int MAX_RADIUS = 10;
    for (int i=0; i<nb; i++) {
        cloud[i] = malloc(sizeof(struct snowflake));
        cloud[i]->x = MAX_RADIUS + rand() % (SIZE - 2*MAX_RADIUS);
        cloud[i]->y = MAX_RADIUS + rand() % (SIZE - 2*MAX_RADIUS);
        cloud[i]->radius = 5 + rand() % (MAX_RADIUS - 4); // radius in [5..MAX_RADIUS]
        double v = (5 + rand() % 6) / 10.0;    // v in [0.5 .. 1.0]
        double ang = (rand() % 360) / 360.0 * 2 * 3.141592654;
        cloud[i]->vx = v * cos(ang);
        cloud[i]->vy = v * sin(ang);
        cloud[i]->color = 1 + rand()%7;
    }
}

void draw_snow(int nb, snowflake cloud[nb])
{
    EmptySpace();
    for (int i=0; i<nb; i++)
        DrawDISC(cloud[i]->x, cloud[i]->y, cloud[i]->radius, cloud[i]->color );
    UpdateScreen();
}

void update_snow(int nb, snowflake cloud[nb])
{
    for (int i=0; i<nb; i++) {
        snowflake flake = cloud[i];
        double x = flake->x + flake->vx;
        double y = flake->y + flake->vy;
        double r = flake->radius;
        if (x-r < 0)     { flake->vx = -flake->vx; x = r - (x-r); }
        if (x+r >= SIZE) { flake->vx = -flake->vx; x = SIZE - r - (x+r - SIZE); }
        if (y-r < 0)     { flake->vy = -flake->vy; y = r - (y-r); }
        if (y+r >= SIZE) { flake->vy = -flake->vy; y = SIZE - r - (y+r - SIZE); }
        flake->x = x; flake->y = y;
    }
}

int main(void)
{
    int nb;
    printf("How many snowflakes? "); scanf("%d", &nb);

    snowflake cloud[nb];
    CreateWindow("Let It Snow", SIZE, SIZE);
    generate_snow(nb, cloud, 6502);

    for  (int i=0; i<10000; i++) {
        draw_snow(nb, cloud);
        update_snow(nb, cloud);
    }

    CloseWindow();

    for (int i = 0; i < nb; i++) {
        free(cloud[i]);
    }
}
