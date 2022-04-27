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

#include "plane.h"

bool Plane_load(SDL_Renderer *renderer, Plane *plane, const char *image)
{
    // Load plane image
    if(!Image_load(renderer, &plane->image, image))
    {
        return false;
    }

    return true;
}

void Plane_destroy(Plane *plane)
{
    Image_destroy(&plane->image);
}

void Plane_setX(Plane *plane, int x)
{
    // Plane x coordinate
    plane->image.rect.x = x;
}

void Plane_setY(Plane *plane, int y)
{
    // Plane y coordinate
    plane->image.rect.y = y;
}

void Plane_setCoordinates(Plane *plane, int x, int y)
{
    Plane_setX(plane, x);
    Plane_setY(plane, y);
}

void Plane_moveY(Plane *plane, int y)
{
    Plane_setY(plane, plane->image.rect.y + y);
}

void Plane_setDirection(Plane *plane, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        plane->direction &= ~DIRECTION_DOWN;
        plane->direction |= DIRECTION_UP;
        break;
    case SDLK_DOWN:
            plane->direction &= ~DIRECTION_UP;
            plane->direction |= DIRECTION_DOWN;
            break;
    }
}

void Plane_unsetDirection(Plane *plane, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        plane->direction &= ~DIRECTION_UP;
        break;
    case SDLK_DOWN:
            plane->direction &= ~DIRECTION_DOWN;
            break;
    }
}

void Plane_render(SDL_Renderer *renderer, Plane *plane)
{

    // Render plane
    Image_render(renderer, &plane->image);

}
void Plane_move(Plane *plane, int screenWidth, int screenHeight, int framerate)
{
    int planeStep = plane->speed / framerate;

    if( (plane->direction & DIRECTION_UP)
            && plane->image.rect.y - planeStep >= plane->margin)
    {
        Plane_moveY(plane, -planeStep);
        if(plane->image.rect.y<30)
        {

          Plane_setDirection(plane, SDLK_DOWN);

        }
    }
    else if( (plane->direction & DIRECTION_DOWN)
             && plane->image.rect.y < (screenHeight - plane->image.rect.h)*94 / 100)
    {
        Plane_moveY(plane, planeStep);
    }
}
