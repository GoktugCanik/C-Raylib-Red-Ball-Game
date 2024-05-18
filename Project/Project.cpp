

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"


//Platform struct
typedef struct {
    int x;
    int y;
    int width;
    int height;
}Platform;

//Spikes struct
typedef struct {
    int x;
    int y;
}Spike;

//Player struct
typedef struct {
    int x;
    int y;
    float size;
    float gravity;
}Ball;

//Coin struct
typedef struct {
    int x;
    int y;
    float size;
}Coin;


const int s_width = 1366;
const int s_height = 768;

Texture2D texBackground;

// A function to see if player grounded or not
int grounded(Ball ball, Platform platforms[], int count) {

    for (int i = 0; i < count; i++) {
        Platform platform= platforms[i];
        
        Rectangle platform_rec; 
        platform_rec.x = platforms[i].x; platform_rec.y = platforms[i].y;
        platform_rec.width = platforms[i].width; platform_rec.height = platforms[i].height;
        
        Rectangle ball_rec; 
        ball_rec.x = ball.x - ball.size + 15;
        ball_rec.y = ball.y + ball.size / 2; 
        ball_rec.width = ball.size * 2 - 30; 
        ball_rec.height = ball.size / 2 + 1;
        if (CheckCollisionRecs(ball_rec,platform_rec)) {
            return i;
        }
    }
    return -1;
}

int onSpike(Ball ball, Spike spikes[], int spike_count, Image spike_img) {
    for (int i = 0; i < spike_count; i++) {
        Spike spike = spikes[i];

        Rectangle spike_rec;
        spike_rec.x = spike.x;
        spike_rec.y = spike.y;
        spike_rec.width = spike_img.width;
        spike_rec.height = spike_img.height;

        Rectangle ball_rec;
        ball_rec.x = ball.x - ball.size + 15;
        ball_rec.y = ball.y + ball.size / 2;
        ball_rec.width = ball.size * 2 - 30;
        ball_rec.height = ball.size / 2 + 1;

        if (CheckCollisionRecs(ball_rec, spike_rec)) {
            return i;
        }
    }
    return -1;
}


int main()
{


   // Player's character 
    Ball ball;
        ball.x = s_width / 3;
        ball.y = s_height * 0.8;
        ball.size = 30;
        ball.gravity = 4;
    // Creating a camera
        Vector2 camera_offset; camera_offset.x = 0; camera_offset.y = 0;
        Vector2 camera_target; camera_target.x = 0; camera_target.y = 0;

        Camera2D camera;
        camera.offset = camera_offset;
        camera.target = camera_target;
        camera.rotation = 0;
        camera.zoom = 1;

    // Creating Platforms        
        Platform platforms[20];

        platforms[0].x = 0;                           platforms[3].x = 2200;                         platforms[6].x = 3100;
        platforms[0].y = s_height - 10;               platforms[3].y = 350;                          platforms[6].y = 300;
        platforms[0].width = s_width*0.5;             platforms[3].width= s_width * 0.1;             platforms[6].width = int(s_width*0.3);
        platforms[0].height = 10;                     platforms[3].height = int(s_height * 0.02);    platforms[6].height = int(s_height * 0.02);
    
        platforms[1].x = int(s_width * 0.2);          platforms[4].x = int(s_width * 0.9);           platforms[7].x = 3600;
        platforms[1].y = int(s_height * 0.7);         platforms[4].y = int(s_height * 0.6);          platforms[7].y = 450;
        platforms[1].width = int(s_width * 0.2);      platforms[4].width = s_width * 0.5;            platforms[7].width = int(s_width * 0.3);
        platforms[1].height = int(s_height * 0.02);   platforms[4].height = int(s_height * 0.02);    platforms[7].height = int(s_height * 0.02);
     
      platforms[2].x = int(s_width * 0.6);           platforms[5].x = 2600;                          platforms[8].x = 4200;
      platforms[2].y = int(s_height * 0.4);          platforms[5].y = 450;                           platforms[8].y = 600;
      platforms[2].width = int(s_width * 0.25);       platforms[5].width = int(s_width * 0.3);        platforms[8].width = int(s_width * 0.3);
      platforms[2].height = int(s_height * 0.02);    platforms[5].height = int(s_height * 0.02);     platforms[8].height = int(s_height * 0.02);

      platforms[9].x = 4700;                         platforms[10].x = 5500;                          platforms[11].x = 6250;
      platforms[9].y = 400;                          platforms[10].y = s_height - 10;                 platforms[11].y = s_height - 200;
      platforms[9].width = int(s_width * 0.4);       platforms[10].width = int(s_width * 0.7);        platforms[11].width = int(s_width * 0.7);
      platforms[9].height = int(s_height * 0.02);    platforms[10].height = int(s_height * 0.02);     platforms[11].height = int(s_height * 0.02);

      platforms[12].x = 7000;                         platforms[13].x = 7700;                          platforms[14].x = 8500;
      platforms[12].y = 350;                          platforms[13].y = s_height - 200;                 platforms[14].y = s_height - 300;
      platforms[12].width = int(s_width * 0.6);       platforms[13].width = int(s_width * 0.5);        platforms[14].width = int(s_width * 0.4);
      platforms[12].height = int(s_height * 0.02);    platforms[13].height = int(s_height * 0.02);     platforms[14].height = int(s_height * 0.02);

      platforms[15].x = 9400;                         
      platforms[15].y = s_height - 10;
      platforms[15].width = 1500;       
      platforms[15].height = int(s_height * 0.02);    
     
      int platform_count = sizeof(platforms) / sizeof(platforms[0]);
      
      //Creating spikes
      Spike spikes[20];
        
      spikes[0].x = int(s_width * 0.899);          spikes[1].x = 3600;      spikes[2].x = 4900;      spikes[3].x = 6400;
      spikes[0].y = int(s_height * 0.53);          spikes[1].y = 400;       spikes[2].y = 350;       spikes[3].y = s_height - 250;

      int spike_count = sizeof(spikes) / sizeof(spikes[0]);
      
      //Creating Coins
       

      
      

   
    InitWindow(s_width, s_height, "Red Ball Game");
    SetTargetFPS(60);
    
    Image spike_img = LoadImage("img/spike.png");
    ImageResize(&spike_img, spike_img.width / 3, spike_img.height / 3);
    Texture2D spike = LoadTextureFromImage(spike_img);
    UnloadImage(spike_img);
       
    bool canMove = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        //Configuration of Camera
        BeginMode2D(camera);
        if (ball.x > s_width * 0.6) {
            camera.offset.x = -(ball.x - s_width * 0.6);
        }
        else if (ball.x < s_width * 0.4) {
            camera.offset.x = -(ball.x - s_width * 0.4);
       }
        if (camera.offset.x > 0) { camera.offset.x = 0; }
        else if (camera.offset.x > 10000) { camera.offset.x = 10000; }

        //Gravity of character
        ball.y += ball.gravity;
        ball.gravity += 0.3f;
       
        //Platform logic and jumping
        int current_platform = grounded(ball, platforms, platform_count);
        if (current_platform != -1) {
            
            if (ball.gravity > 0) {
                ball.y = platforms[current_platform].y - ball.size;
                ball.gravity = 0;

            }
            if (IsKeyPressed(KEY_SPACE)) {
                ball.gravity = -12;
            }
        }
       
        int current_spike = onSpike(ball, spikes, spike_count, spike_img);
        if (current_spike != -1) {
            
            DrawText("You died!", spikes[current_spike].x, spikes[current_spike].y -100, 30, BLACK);
            ball.gravity = 0; 
            DrawText("Press Space key to spawn again", spikes[current_spike].x, spikes[current_spike].y + 100, 30, BLACK);
            canMove = false;

           if(IsKeyPressed(KEY_SPACE)) {
                ball.x = s_width / 3;
                ball.y = s_height * 0.8;
                canMove = true;
           }
            
        }
        if (ball.x >= 10300) { canMove = false; }

        //Character movement
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            if (canMove) {
                ball.x += -5;
            }
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            if (canMove) {
                ball.x += 5;
            }
        }

        if (ball.x >= 10300) { ball.x = 10300; }
       

        ClearBackground(GREEN);
       // Drawing platforms
        for (int i = 0; i < platform_count; i++) {
            DrawRectangle(
              platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height, BLACK);
        }
        // Drawing spikes
        for (int i = 0; i < platform_count; i++) {
            DrawTexture(spike, spikes[i].x, spikes[i].y, WHITE);
           
        }

        
        //Drawing player's character
        DrawCircle(ball.x, ball.y, ball.size, RED);

            if (ball.x >= 10300) {

                ClearBackground(RAYWHITE);
                DrawText("Congrats! You Passed the First Level!", 10000, s_height/2, 30, BLACK);
            }
           

       DrawTexture(texBackground, 0, 0, RAYWHITE);    
        EndMode2D();
        EndDrawing();
    }
    // Unload textures from GPU memory
    UnloadTexture(spike); 

    CloseWindow();
    return 0;

}

