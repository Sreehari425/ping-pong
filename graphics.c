#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

// ASM externs
extern long long ball_x;
extern long long ball_y;
extern long long paddle1_y;
extern long long paddle2_y;
extern long long player1_score;
extern long long player2_score;
extern void update_game_state(void);

// Paddle constants
const int paddle_width = 20;
const int paddle_height = 100;
const int paddle_speed = 12;

// Function to draw a digit using rectangles (simple 7-segment style)
void draw_digit(SDL_Renderer *renderer, int digit, int x, int y) {
    int segments[10][7] = {
        {1,1,1,1,1,1,0}, // 0
        {0,1,1,0,0,0,0}, // 1
        {1,1,0,1,1,0,1}, // 2
        {1,1,1,1,0,0,1}, // 3
        {0,1,1,0,0,1,1}, // 4
        {1,0,1,1,0,1,1}, // 5
        {1,0,1,1,1,1,1}, // 6
        {1,1,1,0,0,0,0}, // 7
        {1,1,1,1,1,1,1}, // 8
        {1,1,1,1,0,1,1}  // 9
    };
    
    int seg_w = 20, seg_h = 4;
    int vert_w = 4, vert_h = 16;
    
    // Horizontal segments: top, middle, bottom
    if (segments[digit][0]) { // top
        SDL_Rect seg = {x, y, seg_w, seg_h};
        SDL_RenderFillRect(renderer, &seg);
    }
    if (segments[digit][6]) { // middle
        SDL_Rect seg = {x, y + 16, seg_w, seg_h};
        SDL_RenderFillRect(renderer, &seg);
    }
    if (segments[digit][3]) { // bottom
        SDL_Rect seg = {x, y + 32, seg_w, seg_h};
        SDL_RenderFillRect(renderer, &seg);
    }
    
    // Vertical segments
    if (segments[digit][1]) { // top right
        SDL_Rect seg = {x + 16, y + 4, vert_w, vert_h};
        SDL_RenderFillRect(renderer, &seg);
    }
    if (segments[digit][2]) { // bottom right
        SDL_Rect seg = {x + 16, y + 20, vert_w, vert_h};
        SDL_RenderFillRect(renderer, &seg);
    }
    if (segments[digit][4]) { // bottom left
        SDL_Rect seg = {x, y + 20, vert_w, vert_h};
        SDL_RenderFillRect(renderer, &seg);
    }
    if (segments[digit][5]) { // top left
        SDL_Rect seg = {x, y + 4, vert_w, vert_h};
        SDL_RenderFillRect(renderer, &seg);
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Ping Pong ASM+C", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    // Paddle 1 controls (W/S)
                    case SDLK_w:
                        paddle1_y -= paddle_speed;
                        if (paddle1_y < 0) paddle1_y = 0;
                        break;
                    case SDLK_s:
                        paddle1_y += paddle_speed;
                        if (paddle1_y > 480 - paddle_height) paddle1_y = 480 - paddle_height;
                        break;

                    // Paddle 2 controls (Up/Down arrows)
                    case SDLK_UP:
                        paddle2_y -= paddle_speed;
                        if (paddle2_y < 0) paddle2_y = 0;
                        break;
                    case SDLK_DOWN:
                        paddle2_y += paddle_speed;
                        if (paddle2_y > 480 - paddle_height) paddle2_y = 480 - paddle_height;
                        break;

                    default:
                        break;
                }
            }
        }

        update_game_state();

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // Draw ball
        SDL_Rect ball = {(int)ball_x, (int)ball_y, 20, 20};
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderFillRect(ren, &ball);

        // Draw left paddle
        SDL_Rect paddle1 = {10, (int)paddle1_y, paddle_width, paddle_height};
        SDL_RenderFillRect(ren, &paddle1);

        // Draw right paddle
        SDL_Rect paddle2 = {610, (int)paddle2_y, paddle_width, paddle_height};
        SDL_RenderFillRect(ren, &paddle2);

        // Draw scores using simple 7-segment display
        // Player 1 score (left side)
        draw_digit(ren, (int)(player1_score % 10), 280, 30);
        if (player1_score >= 10) {
            draw_digit(ren, (int)(player1_score / 10), 250, 30);
        }
        
        // Player 2 score (right side)
        draw_digit(ren, (int)(player2_score % 10), 350, 30);
        if (player2_score >= 10) {
            draw_digit(ren, (int)(player2_score / 10), 320, 30);
        }
        
        // Draw center line
        SDL_Rect center_line = {319, 20, 2, 50};
        SDL_RenderFillRect(ren, &center_line);

        SDL_RenderPresent(ren);

        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
