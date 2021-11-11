#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "sdl.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"
#include "math.h"

int done = 0;
int frame_counter = 0;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

int main(int argc, char *argv[]){

    callTitleScreen();

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, front_right_sensor;
    int left_sensor =0;
    int right_sensor=0;
    clock_t start_time, end_time;
    int msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.

    // default
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);


/*

    // default
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);

    // Maze 1 & 2
    insertAndSetFirstWall(&head, 2,  220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  400, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  620, 340, 20, 10);

    insertAndSetFirstWall(&head, 1,  320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  520, 440, 120, 10);

    //Maze 3 & 4
    insertAndSetFirstWall(&head, 2,  640-10-220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  640-200-20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  640-280-20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  640-10-300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-110-300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  640-10-400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-400-220, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  640-10-620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-620-20, 340, 20, 10);


    insertAndSetFirstWall(&head, 1,  640-10-320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  640-200-120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  640-80-120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  640-10-200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-310-200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  640-10-500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-20-500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  640-10-520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-120-520, 440, 120, 10);

    // Maze 5 & 6
    int i;
    insertAndSetFirstWall(&head, 12,  120, 450, 10, 30);
    insertAndSetFirstWall(&head, 12,  220, 450, 10, 30);
    for (i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,  20 + i , 350 + i, 10, 10); //1
        insertAndSetFirstWall(&head, i,  20 +100 + i , 350 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 12,  20, 280, 10, 70);
    insertAndSetFirstWall(&head, 12,  120, 280, 10, 70);
    for (i = 0; i < 180; i++){
        insertAndSetFirstWall(&head, i,  20 +190 - i/2 , 100 + i, 10, 10); //1
    }
    for (i = 0; i < 105; i++){
        insertAndSetFirstWall(&head, i,  20 +105/2 - i/2 , 175 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 2,  20, 175, 105/2, 10);
    insertAndSetFirstWall(&head, 2,  20, 20, 10, 155);
    insertAndSetFirstWall(&head, 2,  20, 20, 300, 10);
    insertAndSetFirstWall(&head, 2,  320, 20, 10, 60);
    insertAndSetFirstWall(&head, 2,  80, 100, 130, 10);
    insertAndSetFirstWall(&head, 2,  80, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  80, 80, 160, 10);

    double j;
    for (i = 0; i < 50; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              320 + 30*sin(10*j * M_PI/180),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    for (i = 0; i < 75; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              240 + 30*sin(10*j * M_PI/180),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    insertAndSetFirstWall(&head, 2,  345, 330, 105, 10);
    insertAndSetFirstWall(&head, 2,  450, 190, 10, 150);
    insertAndSetFirstWall(&head, 2,  380, 190, 70, 10);
    insertAndSetFirstWall(&head, 2,  380, 20, 10, 170);
    insertAndSetFirstWall(&head, 2,  380, 20, 260, 10);

    insertAndSetFirstWall(&head, 2,  255, 455, 345, 10);
    insertAndSetFirstWall(&head, 2,  600, 100, 10, 365);
    insertAndSetFirstWall(&head, 2,  530, 100, 70, 10);
    insertAndSetFirstWall(&head, 2,  530, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  530, 80, 110, 10);


    // Maze 7 & 8
    int i;
    insertAndSetFirstWall(&head, 12,  640-10-120, 450, 10, 30);
    insertAndSetFirstWall(&head, 12,  640-10-220, 450, 10, 30);

    for (i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,  640-10-(20 + i) , 350 + i, 10, 10); //1
        insertAndSetFirstWall(&head, i,  640-10-(20 +100 + i) , 350 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 12,  640-10-20, 280, 10, 70);
    insertAndSetFirstWall(&head, 12,  640-10-120, 280, 10, 70);

    for (i = 0; i < 180; i++){
        insertAndSetFirstWall(&head, i,  640-10-(20 +190 - i/2) , 100 + i, 10, 10); //1
    }
    for (i = 0; i < 105; i++){
        insertAndSetFirstWall(&head, i,  640-10-(20 +105/2 - i/2) , 175 + i, 10, 10); //1
    }


    insertAndSetFirstWall(&head, 2,  640-105/2-20, 175, 105/2, 10);
    insertAndSetFirstWall(&head, 2,  640-10-20, 20, 10, 155);
    insertAndSetFirstWall(&head, 2,  640-300-20, 20, 300, 10);
    insertAndSetFirstWall(&head, 2,  640-10-320, 20, 10, 60);
    insertAndSetFirstWall(&head, 2,  640-130-80, 100, 130, 10);
    insertAndSetFirstWall(&head, 2,  640-10-80, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  640-160-80, 80, 160, 10);


    double j;
    for (i = 0; i < 50; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              640-10-(320 + 30*sin(10*j * M_PI/180)),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    for (i = 0; i < 75; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              640-10-(240 + 30*sin(10*j * M_PI/180)),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }

    insertAndSetFirstWall(&head, 2,  640-105-345, 330, 105, 10);
    insertAndSetFirstWall(&head, 2,  640-10-450, 190, 10, 150);
    insertAndSetFirstWall(&head, 2,  640-70-380, 190, 70, 10);
    insertAndSetFirstWall(&head, 2,  640-10-380, 20, 10, 170);
    insertAndSetFirstWall(&head, 2,  640-260-380, 20, 260, 10);

    insertAndSetFirstWall(&head, 2,  640-345-255, 455, 345, 10);
    insertAndSetFirstWall(&head, 2,  640-10-600, 100, 10, 365);
    insertAndSetFirstWall(&head, 2,  640-70-530, 100, 70, 10);
    insertAndSetFirstWall(&head, 2,  640-10-530, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  640-110-530, 80, 110, 10);

    // Shanghai F1
    insertAndSetFirstWall(&head, 1, 0, OVERALL_WINDOW_HEIGHT-10, OVERALL_WINDOW_WIDTH, 10);
    insertAndSetFirstWall(&head, 2, 0, OVERALL_WINDOW_HEIGHT-90, OVERALL_WINDOW_WIDTH/2-80, 10);
    insertAndSetFirstWall(&head, 3, OVERALL_WINDOW_WIDTH/2-90, 160, 10, 240);
    insertAndSetFirstWall(&head, 4, OVERALL_WINDOW_WIDTH/2-10, 80, 10, OVERALL_WINDOW_HEIGHT-90);
    insertAndSetFirstWall(&head, 5, 0, 0, OVERALL_WINDOW_WIDTH, 10);
    insertAndSetFirstWall(&head, 6, 0, 0, 10, 160);
    insertAndSetFirstWall(&head, 7, 0, 160, OVERALL_WINDOW_WIDTH/2-80, 10);
    insertAndSetFirstWall(&head, 8, 80, 80, OVERALL_WINDOW_WIDTH-160, 10);
    insertAndSetFirstWall(&head, 9, 80, 80, OVERALL_WINDOW_WIDTH-160, 10);
    insertAndSetFirstWall(&head, 10, OVERALL_WINDOW_WIDTH-10, 0, 10, OVERALL_WINDOW_HEIGHT-80);
    insertAndSetFirstWall(&head, 11, 80, 80, OVERALL_WINDOW_WIDTH-160, 10);
    insertAndSetFirstWall(&head, 12, OVERALL_WINDOW_WIDTH-90, 80, 10, 240);
    insertAndSetFirstWall(&head, 13, OVERALL_WINDOW_WIDTH-170, 80, 10, 240);
    insertAndSetFirstWall(&head, 14, OVERALL_WINDOW_WIDTH-170, 320, 90, 10);
    insertAndSetFirstWall(&head, 15, OVERALL_WINDOW_WIDTH-250, 160, 10, 240);
    insertAndSetFirstWall(&head, 16, OVERALL_WINDOW_WIDTH-250, OVERALL_WINDOW_HEIGHT-90, 250, 10);

*/


    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderClear(renderer);
        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, left_sensor, right_sensor);
        robotMotorMove(&robot);
        printf("Frame %d\n", frame_counter);

        //Check if robot reaches endpoint. and check sensor values

        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){ //Default
        //if (checkRobotReachedEnd(&robot, 640, 340, 10, 100)){ //Maze 1
        //if (checkRobotReachedEnd(&robot, 220, 480, 100, 10)){ //Maze 2
        //if (checkRobotReachedEnd(&robot, 0, 340, 10, 100)){ // Maze 3
        //if (checkRobotReachedEnd(&robot, 640-10-320, 480, 100, 10)){ //Maze 4
        //if (checkRobotReachedEnd(&robot, 640, 20, 10, 60)){ //Maze 5
        //if (checkRobotReachedEnd(&robot, 120, 480, 100, 10)){ //Maze 6
        //if (checkRobotReachedEnd(&robot, 0, 20, 10, 60)){ //Maze 7
        //if (checkRobotReachedEnd(&robot, 640-10-220, 480, 100, 10)){ //Maze 8
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {

            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0){
                printf("Getting close on the FRONT (L). Score = %d\n", front_left_sensor);
            }
            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0){
                printf("Getting close on the FRONT (R). Score = %d\n", front_right_sensor);
            }
            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor>0){
                printf("Getting close on the RIGHT. Score = %d\n", right_sensor);
            }

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor>0){
                printf("Getting close on the LEFT. Score = %d\n", left_sensor);

            }
         }
         printf("--------------------------------------------\n");
         frame_counter ++;



        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
            if(state[SDL_SCANCODE_ESCAPE]){
                callPauseScreen();
                window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
                renderer = SDL_CreateRenderer(window, -1, 0);

            }

        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}

void callTitleScreen(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Texture * image_texture = initialize_texture_from_file("Resources/TitleScreen.png", renderer);
    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = image_width;
    texture_destination.h = image_height;

    bool running = true;
    SDL_Event e;
    while(running)
    {
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Process events
        while(SDL_PollEvent(&e))
        {
            if(state[SDL_SCANCODE_RETURN]){
                running = false;
            }
        }
        // Clear screen
        SDL_RenderClear(renderer);
        // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Re-render game screen
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void callPauseScreen(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Texture * image_texture = initialize_texture_from_file("Resources/PauseScreen.png", renderer);
    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = image_width;
    texture_destination.h = image_height;

    bool running = true;
    SDL_Event e;
    while(running)
    {
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Process events
        while(SDL_PollEvent(&e))
        {
            if(state[SDL_SCANCODE_RETURN]){
                running = false;
            }
        }
        // Clear screen
        SDL_RenderClear(renderer);
        // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Re-render game screen
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
}


SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}
