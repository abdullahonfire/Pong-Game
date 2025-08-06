#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

int main(){
    
    //Window 
    int screenWidth = 850;
    int screenHeight = 500;
    InitWindow(screenWidth,screenHeight, "Pong Game");
    InitAudioDevice();
    SetTargetFPS(60);
   
    // sound 
    Sound hit;
    Sound click;
    Sound win;
  

    
    //Sound
    hit = LoadSound("hit.wav");
    click = LoadSound("click.wav");
    win = LoadSound("win.wav");
    Sound gameOverMusic = LoadSound("gameover_bg.MP3");
    bool gameOverMusicPlayed = false;
    bool winSoundPlayed = false;

    
    // photo
    // Game Over Background
Texture2D gameOverBackground = LoadTexture("gameover.png");

    // Background Image
Texture2D menuBackground = LoadTexture("photo.png");

    
    //Menu 
    bool menuMode = true;
    bool playerVsAI = true;
    bool gameOver = false;
    int maxScore = 3;
    
  Rectangle quitBtn = { screenWidth / 2 - 100, 200, 200, 40 }; //quitBtn
  Vector2 mouse = GetMousePosition();
    

    
    //Pause 
    bool pause = false;
bool showPauseMenu = false;
Rectangle resumeBtn = {screenWidth / 2 - 100, screenHeight / 2 - 30, 200, 40};
Rectangle homeBtn = {screenWidth / 2 - 100, screenHeight / 2 + 30, 200, 40};

    
    // Level Selection
    bool isBeginner = true;
    bool levelSelected = false;
    
    // Difficulty
    float ballSpeed = 4;
    
    // Score
    int player1Score = 0;
    int player2Score = 0;
    
    //Ball
    float ballX = screenWidth / 2;
    float ballY = screenHeight / 2;
    float ballRadius = 10;
    float ballSpeedX = 4;
    float ballSpeedY = 4;
    float speedIncrement = 0.2f;
    Color ballColor = YELLOW;
    
    //Paddle
    float paddleWidth = 12;
    float paddleHeight = 80;
    float paddleCurve = 0.7f;
    float paddleSpeed = 6;
    float aiPaddleSpeed = 4;
    
    float leftPaddleX = 10;
    float leftPaddleY = screenHeight / 2 - paddleHeight / 2;
    
    float rightPaddleX = screenWidth - 20;
    float rightPaddleY = screenHeight / 2 - paddleHeight / 2;
    
    // Menu 
     Rectangle aiBtn = {260, 140, 280, 40};         // Player vs AI
Rectangle pvpBtn = {260, 190, 280, 40};        // Player vs Player
Rectangle beginnerBtn = {260, 260, 130, 40};   // Beginner
Rectangle proBtn = {410, 260, 130, 40};        // Pro
Rectangle startBtn = {300, 330, 200, 40};      // Start Game

    
    while(!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        
        if (IsKeyPressed(KEY_P)) {   //Pause
            pause = !pause;
            showPauseMenu = pause;
            PlaySound(click);
        }

        
        // Menu mode 
        if (menuMode) {
            BeginDrawing();
            Rectangle src = { 0, 0, (float)menuBackground.width, (float)menuBackground.height };
    Rectangle dst = { 0, 0, (float)screenWidth, (float)screenHeight };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(menuBackground, src, dst, origin, 0.0f, WHITE);


            
            DrawText("PONG GAME", screenWidth / 2-120, 50 , 40, BLACK);
            DrawText("Select Game Mode", 280, 100, 20, PINK);
            
            // AI Button
            DrawRectangleRec(aiBtn, CheckCollisionPointRec(mouse , aiBtn) ? LIGHTGRAY :(playerVsAI ? BLUE : GRAY));
            DrawText("Player vs AI", aiBtn.x + 80, aiBtn.y + 10, 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, aiBtn)) {
                playerVsAI = true;
                levelSelected = false;
                PlaySound(click);
            }
            
            // PVP Button
            DrawRectangleRec(pvpBtn, CheckCollisionPointRec(mouse, pvpBtn) ? LIGHTGRAY : (!playerVsAI ? BLUE : GRAY));
            DrawText("Player vs Player", pvpBtn.x + 65, pvpBtn.y + 10, 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, pvpBtn)) {
                playerVsAI = false;
                levelSelected = false;
                PlaySound(click);
            }
            
            // Show level options only when mode is selected
            DrawText("Select Level", 320, 230, 20, LIME);
            
            // Beginner button
            DrawRectangleRec(beginnerBtn, CheckCollisionPointRec(mouse , beginnerBtn) ? LIGHTGRAY : (isBeginner ? BLUE : GRAY));
            DrawText("Beginner", beginnerBtn.x + 20, beginnerBtn.y + 10, 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, beginnerBtn)) {
                isBeginner = true;
                levelSelected = true;
                PlaySound(click);
            }

            // Professional button
            DrawRectangleRec(proBtn, CheckCollisionPointRec(mouse , proBtn) ? LIGHTGRAY : (!isBeginner ? BLUE : GRAY));
            DrawText("Expert", proBtn.x + 10, proBtn.y + 10, 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, proBtn)) {
                isBeginner = false;
                levelSelected = true;
                PlaySound(click);
            }

            // Start Button - Only enabled if level selected
            if (levelSelected) {
                DrawRectangleRec(startBtn, CheckCollisionPointRec(mouse, startBtn) ? GREEN : DARKGRAY);
            } else {
                DrawRectangleRec(startBtn, GRAY);
                DrawText("Please select a level!", screenWidth / 2 - 110, startBtn.y + 50, 20, RED);
            }

            DrawText("Start Game", startBtn.x + 50, startBtn.y + 10, 20, WHITE);

            if (levelSelected && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, startBtn)) {
                menuMode = false;

                if (isBeginner) {
                    ballSpeed = 4;
                    aiPaddleSpeed = 4;
                } else {
                    ballSpeed = 6;
                    aiPaddleSpeed = 6;
                }

                // Reset
                player1Score = 0;
                player2Score = 0;
                ballX = screenWidth / 2;
                ballY = screenHeight / 2;
                ballSpeedX = ballSpeed;
                ballSpeedY = ballSpeed;
                gameOver = false;
                PlaySound(click);
            }

            EndDrawing();
            continue;
        }
        
        if (pause) {
            BeginDrawing();
            ClearBackground((Color){20, 160, 133, 255});
            
            if (showPauseMenu) {
    // Dark overlay
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));

    // Draw Pause Title
    DrawText("Game Paused", screenWidth / 2 - 100, screenHeight / 2 - 100, 30, WHITE);

    // Resume Button
    DrawRectangleRec(resumeBtn, CheckCollisionPointRec(mouse, resumeBtn) ? LIGHTGRAY : DARKGRAY);
    DrawText("Resume", resumeBtn.x + 60, resumeBtn.y + 10, 20, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, resumeBtn)) {
        pause = false;
        showPauseMenu = false;
        PlaySound(click);
    }

    // Home Button
    DrawRectangleRec(homeBtn, CheckCollisionPointRec(mouse, homeBtn) ? LIGHTGRAY : DARKGRAY);
    DrawText("Home", homeBtn.x + 70, homeBtn.y + 10, 20, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, homeBtn)) {
        pause = false;
        showPauseMenu = false;
        menuMode = true;
        levelSelected = false;
        ballX = screenWidth / 2;
        ballY = screenHeight / 2;
        player1Score = 0;
        player2Score = 0;
        ballSpeedX = ballSpeed;
        ballSpeedY = ballSpeed;
        PlaySound(click);
    }

   }

            
            EndDrawing();
            continue;
        }

        
        
        
        if(!gameOver) {
            ballX += ballSpeedX;
            ballY += ballSpeedY;
            
            // Ball Bounce Top/Bottom    
            if(ballY+ballRadius >= screenHeight || ballY-ballRadius <= 0){
               ballSpeedY *= -1;
            }
            
            //Player
            if (IsKeyDown(KEY_UP)){
                rightPaddleY -= paddleSpeed;
            }
            if (IsKeyDown(KEY_DOWN)){
                rightPaddleY += paddleSpeed;
            }
            
            if (!playerVsAI) {
                if (IsKeyDown(KEY_W)) leftPaddleY -= paddleSpeed;
                if (IsKeyDown(KEY_S)) leftPaddleY += paddleSpeed;
            }
            
            //Right paddle screen lock
            if (rightPaddleY<0){
                rightPaddleY = 0;
            }
            if (rightPaddleY + paddleHeight > screenHeight){
                rightPaddleY = screenHeight - paddleHeight;
            }
            
            //AI Movement
            if (playerVsAI) {
                float aiTargetY = ballY - 10 + GetRandomValue(-20, 20);
                if (aiTargetY > leftPaddleY + paddleHeight / 2) {
                    leftPaddleY += aiPaddleSpeed * 0.9f;
                } else if (aiTargetY < leftPaddleY + paddleHeight / 2) {
                    leftPaddleY -= aiPaddleSpeed * 0.9f;
                }
            }

            //Left paddle screen lock 
            if (leftPaddleY<0){
                leftPaddleY = 0;
            }
            if (leftPaddleY + paddleHeight > screenHeight){
                leftPaddleY = screenHeight - paddleHeight;
            }

            Rectangle leftPaddle = {leftPaddleX, leftPaddleY, paddleWidth, paddleHeight};
            Rectangle rightPaddle = {rightPaddleX, rightPaddleY, paddleWidth, paddleHeight};
            
            //Ball reflect on paddle
            if (CheckCollisionCircleRec((Vector2){ballX, ballY}, ballRadius, leftPaddle)){
                ballSpeedX *= -1;
                ballX = leftPaddleX + paddleWidth + ballRadius;
                ballSpeedX += (ballSpeedX > 0) ? speedIncrement : -speedIncrement;
                PlaySound(hit);
            }
            if (CheckCollisionCircleRec((Vector2){ballX, ballY}, ballRadius, rightPaddle)){
                ballSpeedX *= -1;
                ballX = rightPaddleX - ballRadius;
                ballSpeedX += (ballSpeedX > 0) ? speedIncrement : -speedIncrement;
                PlaySound(hit);            
            }
            
            // Scoring
            if (ballX < 0) {
                player2Score++;
                ballX = screenWidth / 2;
                ballY = screenHeight / 2;
                ballSpeedX = ballSpeed;
                ballSpeedY = ballSpeed;
            }
            if (ballX > screenWidth) {
                player1Score++;
                ballX = screenWidth / 2;
                ballY = screenHeight / 2;
                ballSpeedX = -ballSpeed;
                ballSpeedY = -ballSpeed;
            }
            
            if (player1Score >= maxScore || player2Score >= maxScore) {
                gameOver = true;
                PlaySound(win);
            }
        }

        // Draw 
        BeginDrawing();
        ClearBackground((Color){20, 160, 133, 255});
        DrawRectangle(screenWidth / 2, 0, screenWidth / 2 ,screenHeight ,(Color){38, 185, 154, 255});
        
        DrawCircle(screenWidth / 2,screenHeight / 2, 100 ,(Color){129, 204, 184, 255});
        
        //Center line
        for(int y = 0; y < screenHeight; y += 20){
            DrawRectangle(screenWidth / 2 - 1, y,2,10,Fade(WHITE,0.3f));
        }
        
        // Paddles 
        DrawRectangleRounded((Rectangle){leftPaddleX,leftPaddleY, paddleWidth, paddleHeight}, paddleCurve , 16, WHITE);
        DrawRectangleRounded((Rectangle){rightPaddleX, rightPaddleY, paddleWidth, paddleHeight}, paddleCurve, 16, WHITE);
        
        //Ball
        DrawCircle((int)ballX,(int)ballY,ballRadius, ballColor);
        
        //Scores 
        DrawText(TextFormat("%d", player1Score), screenWidth / 2 - 60, 20 ,40, WHITE);
        DrawText(TextFormat("%d", player2Score), screenWidth / 2 + 40, 20, 40, WHITE);
        
        
       //Win Message and Game Over UI
        if (gameOver) {
    // Play win sound only once
    if (!winSoundPlayed) {
        PlaySound(win);
        winSoundPlayed = true;
    }

    // Play game over background music only once
    if (!gameOverMusicPlayed) {
        PlaySound(gameOverMusic);
        gameOverMusicPlayed = true;
    }

       
       DrawTexturePro(gameOverBackground,
               (Rectangle){0, 0, (float)gameOverBackground.width, (float)gameOverBackground.height},
               (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
               (Vector2){0, 0}, 0.0f, WHITE);


    // Game Over Title
    DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 50) / 2, 50, 50, ORANGE);

    // Who wins
    const char *winner = player1Score >= maxScore ? "Player 1 Wins!" : "Player 2 Wins!";
    DrawText(winner, screenWidth / 2 - MeasureText(winner, 30) / 2, 120, 30, BLACK);

    // Restart instruction
    DrawText("Press [R] to Restart", screenWidth / 2 - MeasureText("Press [R] to Restart", 20) / 2, 170, 20, PINK);

    // Quit Button
    Rectangle quitBtn = { screenWidth / 2 - 100, 220, 200, 40 };
    DrawRectangleRec(quitBtn, CheckCollisionPointRec(mouse, quitBtn) ? LIGHTGRAY : DARKGRAY);
    DrawText("Quit", quitBtn.x + 80, quitBtn.y + 10, 20, WHITE);

    // Restart
    if (IsKeyPressed(KEY_R)) {
    menuMode = true;
    levelSelected = false;
    ballX = screenWidth / 2;
    ballY = screenHeight / 2;
    player1Score = 0;
    player2Score = 0;
    ballSpeedX = ballSpeed;
    ballSpeedY = ballSpeed;
    gameOver = false;
    winSoundPlayed = false;
    gameOverMusicPlayed = false;  // <---- ADD THIS LINE
    PlaySound(click);
   }


    
    // Quit and close window
       if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, quitBtn)) {
           PlaySound(click);
           CloseWindow();  // Close the window immediately
           break;          // Exit main loop
        }

  }

        EndDrawing();
    }

    // Cleanup
    UnloadSound(hit);
    UnloadSound(click);
    UnloadSound(win);
    UnloadTexture(menuBackground);
    UnloadTexture(gameOverBackground);
    UnloadSound(gameOverMusic);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}