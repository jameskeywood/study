#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <time.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024
#define CELL_PADDING 10

const int cols = 7;
const int rows = 6;

int draw_calendar(int total_days, int offset) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *win = SDL_CreateWindow("Study Calendar",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // Load font
	// STORING Robot-Bold.ttf IN ~/.study/ IS NOT A GOOD SOLUTION AND IS ONLY TEMPORARY
	const char *home = getenv("HOME");
    char font_path[256];
    snprintf(font_path, sizeof(font_path), "%s/.study/Roboto-Bold.ttf", home);
    TTF_Font *font = TTF_OpenFont(font_path, 16);
    if (!font) {
        printf("Font load error: %s\n", TTF_GetError());
        return 1;
    }
 
    int cell_width = WINDOW_WIDTH / cols;
    int cell_height = WINDOW_HEIGHT / rows;

    // Render grid
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    int day = 1;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int x = col * cell_width;
            int y = row * cell_height;

            SDL_Rect cell = { x + CELL_PADDING, y + CELL_PADDING,
                              cell_width - 2 * CELL_PADDING,
                              cell_height - 2 * CELL_PADDING };

            SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
            SDL_RenderDrawRect(ren, &cell);

            int cell_index = row * cols + col;
            if (cell_index >= offset && day <= total_days) {
                char label[4];
                sprintf(label, "%d", day++);

                SDL_Color textColor = {0, 0, 0};
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, label, textColor);
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
                SDL_Rect textRect = { x + 15, y + 10, textSurface->w, textSurface->h };
                SDL_RenderCopy(ren, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }
    }

    SDL_RenderPresent(ren);

    SDL_Event e;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

