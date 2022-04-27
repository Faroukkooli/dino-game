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

#include "obstacle1.h"
#include "animation.h"

bool Obstacle_load(SDL_Renderer *renderer, Obstacle *obstacle, const char *image)
{
    // Load obstacle image
    if(!Image_load(renderer, &obstacle->image, image))
    {
        return false;
    }

    return true;
}

void Obstacle_destroy(Obstacle *obstacle)
{
    Image_destroy(&obstacle->image);
}

void Obstacle_setX(Obstacle *obstacle, int x)
{
    // Obstacle x coordinate
    obstacle->image.rect.x = x;
}

void Obstacle_setY(Obstacle *obstacle, int y)
{
    // Obstacle y coordinate
    obstacle->image.rect.y = y;
}

void Obstacle_setCoordinates(Obstacle *obstacle, int x, int y)
{
    Obstacle_setX(obstacle, x);
    Obstacle_setY(obstacle, y);
}

void Obstacle_moveX(Obstacle *obstacle, int x)
{
    Obstacle_setX(obstacle, obstacle->image.rect.x + x);
}
void Obstacle_moveY(Obstacle *obstacle, int y)
{
    Obstacle_setY(obstacle, obstacle->image.rect.y + y);
}

void Obstacle_setDirection(Obstacle *obstacle, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        obstacle->direction &= ~DIRECTION_DOWN;
        obstacle->direction |= DIRECTION_UP;
        break;
    case SDLK_DOWN:
            obstacle->direction &= ~DIRECTION_UP;
            obstacle->direction |= DIRECTION_DOWN;
            break;
    }
}

void Obstacle_unsetDirection(Obstacle *obstacle, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        obstacle->direction &= ~DIRECTION_UP;
        break;
    case SDLK_DOWN:
            obstacle->direction &= ~DIRECTION_DOWN;
            break;
    }
}

void Obstacle_render(SDL_Renderer *renderer, Obstacle *obstacle)
{

    // Render obstacle
    Image_render(renderer, &obstacle->image);

}
void Obstacle_move(Obstacle *obstacle, int screenWidth, int screenHeight, int framerate, Animation *animation)
{
    int obstacleStep = obstacle->speed / framerate;

    if(obstacle->direction & DIRECTION_LEFT)

    {
        Obstacle_moveX(obstacle, -obstacleStep);

        // if the plane passes the obstacle
       if(obstacle->image.rect.x <= animation->plane.image.rect.x + animation->plane.image.rect.w
        // Confused on this one
        && obstacle->image.rect.x + obstacle->image.rect.w >= animation->plane.image.rect.x
        // Bottom of the obstacle < Top of the player
         && obstacle->image.rect.x + obstacle->image.rect.h >= animation->plane.image.rect.y
        // Top of the obstacle < Bottom of player
         && obstacle->image.rect.y <= animation->plane.image.rect.y + animation->plane.image.rect.h)

          {
           animation->gameover = true;
          }

      if(animation->jet.image.rect.x <= animation->plane.image.rect.x + animation->plane.image.rect.w

       && animation->jet.image.rect.x + animation->jet.image.rect.w >= animation->plane.image.rect.x

       && animation->jet.image.rect.x + animation->jet.image.rect.h >= animation->plane.image.rect.y

         && animation->jet.image.rect.y + animation->jet.image.rect.h >= animation->plane.image.rect.y + animation->plane.image.rect.h)

         {
          animation->gameover = true;
         }

        if(obstacle->image.rect.x < - obstacle->image.rect.w)
        {
            obstacle->image.rect.x = (screenWidth + obstacle->image.rect.w)+rand()%5;
        }


//        if((animation->tower.image.rect.x + animation->tower.image.w) - (animation->shop.image.rect.x + animation->shop.image.w) <100)
//        {
//            obstacle->image.rect.x = (screenWidth + obstacle->image.rect.w)+rand()%5;
//        }
    }
}
