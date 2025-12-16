#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// Setting window height and width
#define WIDTH 1200
#define HEIGHT 600
// Defining colors
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_RAY 0xffd43b
#define RAYS_COUNT 1000

// Creating a structure for Circle that takes x and y coordinates and radius
struct Circle
{
    double x;
    double y;
    double radius;
};

struct Ray{
    double x_start, y_start;
    double angle;
};

void FillCircle(SDL_Surface* surface, Circle circle, Uint32 color) {
    double radiusSquared = circle.radius * circle.radius;
    for (double x=circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
        for (double y=circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
            double distance_squared = (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y);
            if (distance_squared <= radiusSquared) {
                SDL_Rect pixel = (SDL_Rect){(int)x, (int)y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_COUNT]) {
    // Placeholder function to generate rays from the circle
    // Actual implementation would depend on ray tracing logic
    for (int i = 0; i < RAYS_COUNT; i++) {
        double angle = ((double) i / RAYS_COUNT) * 2.0 * 3.141592653589793;
        struct Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
        // printf("Ray %d: Start(%.2f, %.2f), Angle: %.2f radians\n", i, ray.x_start, ray.y_start, ray.angle);
    }
}

void CastRays(SDL_Surface* surface, struct Ray rays[RAYS_COUNT], Uint32 color, struct Circle obstacle) {
    // Placeholder function to draw rays on the surface
    // Actual implementation would depend on ray tracing logic
    double obstacle_radius_squared = pow(obstacle.radius, 2);   
    for (int i = 0; i < RAYS_COUNT; i++) {
        struct Ray ray = rays[i];

        int end_of_screen = 0;
        int object_hit = 0;

        double step = 1;
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        while (!end_of_screen && !object_hit) {
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            SDL_Rect pixel = (SDL_Rect){(int)x_draw, (int)y_draw, 1,1};
            SDL_FillRect(surface, &pixel, color);

            // Check for collision with obstacle
            double dist_x = x_draw - obstacle.x;
            double dist_y = y_draw - obstacle.y;
            double distance_squared = dist_x * dist_x + dist_y * dist_y;
            if (distance_squared <= obstacle_radius_squared) {
                object_hit = 1;
                break;
            }
            // Check for end of screen
            if (x_draw < 0 || x_draw >= WIDTH || y_draw < 0 || y_draw >= HEIGHT) {
                end_of_screen = 1;
            }



        }


        // Simple line drawing logic can be implemented here
        // For now, just printing ray info
        // printf("Drawing Ray %d: Start(%.2f, %.2f), Angle: %.2f radians\n", i, ray.x_start, ray.y_start, ray.angle);
    }
}

// Main function
int main(int argc, char* argv[]) {
    // Initializing SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Creating a window
    // SDL_WINDOW_SHOWN makes the window visible -> 0nly after this call
    SDL_Window* window = SDL_CreateWindow(
        "Ray Tracing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );

    // Getting window surface
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    // Filling the surface with white color
    // SDL_Rect ----- pos_x, pos_y, width, height
    // SDL_Rect rect = (SDL_Rect){200, 200,200,200};
    // SDL_FillRect(surface, &rect, COLOR_WHITE);

    struct Circle circle = {200, 200, 40};
    struct Circle shadow_circle = {650, 300, 140};
    SDL_Rect erase_rect = {0,0, WIDTH, HEIGHT};

    struct Ray rays[RAYS_COUNT];
    generate_rays(circle, rays);

    double obstacle_speed_y = 1;
    int simulation_running = 1;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    simulation_running = 0;
                }
            }
            if (event.type == SDL_MOUSEMOTION && (event.motion.state != 0)) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle, rays);
            }
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK); // Clear screen to black
        CastRays(surface, rays, COLOR_RAY, shadow_circle); // Red rays
        FillCircle(surface, circle,COLOR_WHITE ); // White circle
        FillCircle(surface, shadow_circle, COLOR_WHITE ); // White circle


        // Move the obstacle circle
        shadow_circle.y += obstacle_speed_y;
        if (shadow_circle.y - shadow_circle.radius <= 0 || shadow_circle.y + shadow_circle.radius >= HEIGHT) {
            obstacle_speed_y = -obstacle_speed_y; // Reverse direction on collision with window edges
        }

        SDL_UpdateWindowSurface(window);

        SDL_Delay(10); // Delay to control frame rate - here 100 FPS
    }


    // SDL_DestroyWindow(window);
    // SDL_Quit();
    return 0;
}


// g++ ray_tracing.cpp -o ray_tracing -I C:/MinGW/include -L C:/MinGW/lib -lmingw32 -lSDL2main -lSDL2 -lm
