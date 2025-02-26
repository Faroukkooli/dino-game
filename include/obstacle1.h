/*
 * Copyright (c) 2018 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "utils.h"
#include "image.h"

typedef struct Animation Animation;

struct Obstacle
{
    // Obstacle
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

};
typedef struct Obstacle Obstacle;


bool Obstacle_load(SDL_Renderer *renderer, Obstacle *obstacle, const char *image);
void Obstacle_destroy(Obstacle *obstacle);

void Obstacle_setX(Obstacle *obstacle, int x);
void Obstacle_setY(Obstacle *obstacle, int y);
void Obstacle_setCoordinates(Obstacle *obstacle, int x, int y);

void Obstecle_moveX(Obstacle *obstacle, int x);
void Obstacle_moveY(Obstacle *obstacle, int y);

void Obstacle_move(Obstacle *obstacle, int screenWidth, int screenHeight, int framerate, Animation *animation);

void Obstacle_setDirection(Obstacle *obstacle, SDL_Keycode keycode);
void Obstacle_unsetDirection(Obstacle *obstacle, SDL_Keycode keycode);

void Obstacle_render(SDL_Renderer *renderer, Obstacle *obstacle);

#endif // OBSTACLE_H
