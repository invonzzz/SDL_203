#include <iostream>
#include "SDL.h"
#include <locale.h>
using namespace std;
int W = 640;
int H = 480;
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
    double A, B, a, b, temp;
    double mash;
    cout << "Введите A = "; cin >> A;
    cout << "Введите B = "; cin >> B;
    if (A > B)
    {
        temp = A;
        A = B;
        B = temp;
    }
    cout << "Введите a = "; cin >> a;
    cout << "Введите b = "; cin >> b;
    cout << "Введите масштаб графика = "; 
    do
    {
        cin >> mash;
    } while (mash < 0);
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL не смог запуститься! SDL_Error: %s\n", SDL_GetError());
    else
    {
        SDL_Window* window = SDL_CreateWindow(u8"Парабола", 100, 100, W, H, SDL_WINDOW_SHOWN);
        if (window == NULL) printf("Окно не может быть создано! SDL_Error: %s\n", SDL_GetError());
        else
        {
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderDrawLine(renderer, 0, H / 2, W, H / 2);
            SDL_RenderDrawLine(renderer, W / 2, 0, W / 2, H);
            SDL_RenderDrawLine(renderer, W / 2, 0, W / 2 - 10, 15);
            SDL_RenderDrawLine(renderer, W / 2, 0, W / 2 + 10, 15);
            SDL_RenderDrawLine(renderer, W, H / 2, W - 10, H / 2 + 10);
            SDL_RenderDrawLine(renderer, W, H / 2, W - 10, H / 2 - 10);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_Point dest; dest.x, dest.y;
            for (double i = A; i <= B; i = i + 0.01)
            {
                dest.x = mash * i + W / 2;
                dest.y = -mash * (a * (i * i) + b) + H / 2;
                SDL_RenderDrawPoint(renderer, dest.x, dest.y);
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(10000);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}