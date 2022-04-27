#include "background.h"
#include "animation.h"

bool Background_load(SDL_Renderer *renderer, Background *background, const char *file)
{
    return Image_load(renderer, &background->image, file);
}

void Background_destroy(Background *background)
{
    Image_destroy(&background->image);
}

void Background_move(Background *background, int framerate, Animation *animation)
{
    background->image.rect.x -= background->speed / framerate;
    if(background->image.rect.x <= 0)
        background->image.rect.x = background->image.rect.w;
}


void Background_render(SDL_Renderer *renderer, Background *background, int width, int height)
{
    // Unused width
    (void) width;

    SDL_Rect crop = background->image.rect;

    if(background->direction == DIRECTION_LEFT)
    {
        if(background->image.rect.x < width)
        {
            crop.x = 0;
            crop.w = background->image.rect.w - background->image.rect.x;

            SDL_Point pos = { background->image.rect.x, 0 };
            Image_renderCrop(renderer, &background->image, &crop, &pos);
        }

        if(background->image.rect.x != 0)
        {
            crop.x = background->image.rect.w - background->image.rect.x;
            crop.w = MIN(background->image.rect.x, width);

            SDL_Point pos = { 0, 0 };
            Image_renderCrop(renderer, &background->image, &crop, &pos);
        }
    }
}
