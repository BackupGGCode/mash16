#include "gpu.h"
#include <SDL/SDL.h>

void init_pal(cpu_state* state)
{
    uint32_t pal[] =
    {
        PAL_TRANS,  PAL_BLACK,   PAL_GRAY,    PAL_RED,
        PAL_PINK,   PAL_DKBROWN, PAL_BROWN,   PAL_ORANGE,
        PAL_YELLOW, PAL_GREEN,   PAL_LTGREEN, PAL_DKBLUE,
        PAL_BLUE,   PAL_LTBLUE,  PAL_SKYBLUE, PAL_WHITE
    };
    load_pal((uint8_t*)&pal[0],1,state);
}

void load_pal(uint8_t* pal, int alpha, cpu_state* state)
{
    int b = 3 + alpha;
    for(int i=0; i<16; ++i)
    {
        uint32_t col = (pal[i*b] << 16) | (pal[i*b + 1] << 8) | (pal[i*b + 2]);
        *((uint32_t*)&state->pal[i]) = col;
    }
}

void blit_screen(SDL_Surface* sfc, cpu_state* state)
{
    SDL_LockSurface(sfc);
	uint32_t* dst = (uint32_t*)sfc->pixels;
    
    for(int y=0; y<240; ++y)
    {
        for(int x=0; x<160; ++x)
        {
            uint8_t rgb = state->vm[y*160 + x];
            dst[y*320 + x*2] = !(rgb >> 4) ? state->pal[state->bgc]
                                           : state->pal[rgb >> 4];
            dst[y*320 + x*2 + 1] = !(rgb & 0x0f) ? state->pal[state->bgc]
                                                 : state->pal[rgb & 0x0f];
        }
    }
    SDL_UnlockSurface(sfc);
    /* Force screen update. */
    SDL_UpdateRect(sfc,0,0,0,0);
}
