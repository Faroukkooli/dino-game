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

#include "animation.h"
#include "obstacle1.h"

bool Animation_start(SDL_Renderer *renderer, int width, int height)
{
    Animation animation = {0};
    animation.renderer  = renderer;
    animation.width     = width;
    animation.height    = height;
    animation.gameover  = false;

    // Load animation assets
    if(!Animation_load(&animation))
        return false;


    // Initialize framerate manager : 30 FPS
    FPSmanager fpsmanager;
    SDL_initFramerate(&fpsmanager);
    SDL_setFramerate(&fpsmanager, 60);

    // Initialize start frame
    int frame = SDL_getFramecount(&fpsmanager);


    // Event loop exit flag
    bool quit = false;

    // Event loop
    while(!quit && !animation.gameover)
    {
        SDL_Event e;

        // Get available event
        while(SDL_PollEvent(&e))
        {
            // Handle animation events
            quit = Animation_handleEvent(&animation, &e);
        }

        // Each new frame
        int currentFrame = SDL_getFramecount(&fpsmanager);
        if(currentFrame != frame)
        {
            // Update animation frame
            Animation_update(&animation, SDL_getFramerate(&fpsmanager));

            currentFrame = frame;
        }

        // Render animation
        Animation_render(&animation);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    Animation_destroy(&animation);

    return true;
}


bool Animation_load(Animation *animation)
{
    // Load the ocean image
    if(!Background_load(animation->renderer, &animation->background, OCEAN_IMG))
        return false;

    // Background move direction
    animation->background.direction = DIRECTION_LEFT;

    // Background speed in pixel/second
    animation->background.speed = OCEAN_SPEED;

    if(!Plane_load(animation->renderer, &animation->plane, PLANE_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->plane.margin = PLANE_MARGIN;


    // Set plane initial position
    Plane_setX(&animation->plane, (animation->width - animation->plane.image.rect.w) / 7); // Horiz. center
    Plane_setY(&animation->plane,  (animation->height - animation->plane.image.rect.h)* 94/100);

    // Plane move direction
    animation->plane.direction = DIRECTION_STOP;

    // Plane move speed in pixel/second
    animation->plane.speed = PLANE_SPEED;

// SHOP OBSTACLE HERE********************************************************************************************

    if(!Obstacle_load(animation->renderer, &animation->shop, SHOP_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->shop.margin = SHOP_MARGIN;


    // Set shop initial position
    Obstacle_setX(&animation->shop, (animation->width - animation->shop.image.rect.w)); // Horiz.
    Obstacle_setY(&animation->shop,  (animation->height - animation->shop.image.rect.h) * 94/100);

    // shop move direction
    animation->shop.direction = DIRECTION_LEFT;

    // shop move speed in pixel/second
    animation->shop.speed = SHOP_SPEED;

// TOWER OBSTACLE HERE*********************************************************************************************

    if(!Obstacle_load(animation->renderer, &animation->tower, TOWER_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->tower.margin = TOWER_MARGIN;


    // Set tower initial position
    Obstacle_setX(&animation->tower, (animation->width - animation->tower.image.rect.w)*0.6); // Horiz.
    Obstacle_setY(&animation->tower,  (animation->height - animation->tower.image.rect.h) * 94/100);

    // tower move direction
    animation->tower.direction = DIRECTION_LEFT;

    // tower move speed in pixel/second
    animation->tower.speed = TOWER_SPEED;

// JET OBSTACLE HERE************************************************************************************************

  if(!Obstacle_load(animation->renderer, &animation->jet, JET_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->jet.margin = JET_MARGIN;


    // Set jet initial position
    Obstacle_setX(&animation->jet, (animation->width - animation->jet.image.rect.w)*1.5); // Horiz.
    Obstacle_setY(&animation->jet,  (animation->height - animation->jet.image.rect.h) * 30/100);

    // jet move direction
    animation->jet.direction = DIRECTION_LEFT;

    // jet move speed in pixel/second
    animation->jet.speed = JET_SPEED;


    return true;
}

void Animation_destroy(Animation *animation)
{
    Plane_destroy(&animation->plane);
    Background_destroy(&animation->background);
}

bool Animation_handleEvent(Animation *animation, SDL_Event *e)
{
    bool quit = false;

    // User requests quit
    if(e->type == SDL_QUIT)
    {
        quit = true;
    }
    else if(e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            quit = true;
            break;

        case SDLK_UP:
        case SDLK_DOWN:

           Plane_setDirection(&animation->plane, e->key.keysym.sym);
            break;
        }
    }
    else if(e->type == SDL_KEYUP)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_UP:
            break;
        case SDLK_DOWN:

            Plane_unsetDirection(&animation->plane, e->key.keysym.sym);
            break;
        }
    }

    return quit;
}

void Animation_update(Animation *animation, int framerate)
{
    // Move ocean
    Background_move(&animation->background, framerate, animation);

    // Move plane
    Plane_move(&animation->plane, animation->width, animation->height, framerate);

    // Move shop
    Obstacle_move(&animation->shop, animation->width, animation->height, framerate, animation);

    // Move tower
    Obstacle_move(&animation->tower, animation->width, animation->height, framerate, animation);

    // Move jet
    Obstacle_move(&animation->jet, animation->width, animation->height, framerate, animation);
}

void Animation_render(Animation *animation)
{
    // Render ocean
    Background_render(animation->renderer, &animation->background, animation->width, animation->height);

    // Render plane
    Plane_render(animation->renderer, &animation->plane);

    // Render shop
    Obstacle_render(animation->renderer, &animation->shop);

    // Render tower
    Obstacle_render(animation->renderer, &animation->tower);

    // Render jet
    Obstacle_render(animation->renderer, &animation->jet);
}
