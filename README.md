# Pong-Game

### 📝 Description of the Code

This C program is a complete implementation of a **Pong game** using the **Raylib** graphics and audio library. The code includes multiple features to enhance user experience, such as game modes, difficulty levels, sound effects, UI design, and pause/game over functionality.

---

### 🧱 Structure & Features Breakdown

#### 1. **Window & Initialization**

* Initializes an 850x500 window using `InitWindow()`.
* Initializes audio support with `InitAudioDevice()`.
* Sets a 60 FPS game loop with `SetTargetFPS(60)`.

#### 2. **Assets**

* Loads sound effects:

  * `hit.wav`: When the ball hits a paddle.
  * `click.wav`: For button clicks.
  * `win.wav`: On game win.
  * `gameover_bg.mp3`: Background music on game over.
* Loads textures:

  * `photo.png`: Menu background.
  * `gameover.png`: Game over screen background.

#### 3. **Game Modes**

* **Player vs AI** and **Player vs Player** options.
* Level Selection:

  * **Beginner**: Slower ball and AI speed.
  * **Expert**: Faster gameplay for challenge.

#### 4. **Pause Feature**

* Pressing `P` pauses/resumes the game.
* Pause menu includes:

  * Resume button
  * Return to Home/Menu button

#### 5. **Gameplay Mechanics**

* Ball physics:

  * Moves and bounces off screen edges and paddles.
  * Slight speed increase on paddle hit.
* Paddle control:

  * Right paddle: `Up` / `Down` arrow keys.
  * Left paddle: `W` / `S` keys (in PvP mode).
  * In AI mode, left paddle auto-tracks the ball.
* Collision handled with `CheckCollisionCircleRec()`.

#### 6. **Scoring & Game Over**

* Players score when opponent misses the ball.
* First to reach `maxScore` (3) wins.
* On game over:

  * Shows “Game Over” screen with winner’s message.
  * Plays win sound and background music.
  * Press `R` to restart or click "Quit" to exit.

#### 7. **Menu System**

* Custom UI with buttons:

  * Game mode select
  * Difficulty level
  * Start Game
* Buttons change color on hover and play sound on click.

#### 8. **Resource Cleanup**

* Properly unloads all sounds and textures.
* Closes the audio and window at the end.

This code is great for beginners learning:

* Game loops and event handling
* Collision detection
* UI interaction with mouse
* Sound and texture management
* Simple AI behavior

Let me know if you want this translated into **Bangla**, or if you want this formatted as a **GitHub README section**.
