//Joseph Sheldon
//27th May 2020
//Joe's Stupid Pong Clone

#include <Arduboy2.h>
Arduboy2 arduboy;

//variables here
int gamestate = 0;
int ballx = 62;
int bally = 30;
int ballsize = 4;
int ballright = 1;
int balldown = 1;
int paddlewidth = 4;
int paddleheight = 9;
int playerx = 0;
int playery = 30;
int computery = 30;
int computerx = 127 - paddlewidth;
int playerscore = 0;
int computerscore = 0;
int hard = 10;
int score = 5;

void resetgame() {
  ballx = 63;
  playerscore = 0;
  computerscore = 0;
}

void setup() {
  arduboy.begin();
  //set-up here
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);
  arduboy.clear();
}

void loop() {
  if (!arduboy.nextFrame()){
    return;
  }
  arduboy.clear();
  arduboy.pollButtons();
  //game code here
  switch (gamestate) {

    case 0:
      //Title screen
      arduboy.setCursor(0, 0);
      arduboy.print("Welcome to:");
      arduboy.print("\n");
      arduboy.print("Joe's Stupid Pong!");
      arduboy.print("\n");
      arduboy.print("\n");
      arduboy.print("Press A to start");
      arduboy.print("\n");
      arduboy.print("Press B for settings");
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 1;
      }
      if (arduboy.justPressed(B_BUTTON)) {
        gamestate = 4;
      }
      break;

    case 1:
      //gameplay screen
      arduboy.setCursor(20, 0);
      arduboy.print(playerscore);
      arduboy.setCursor(101, 0);
      arduboy.print(computerscore);
      arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);
      arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);
      arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE);
      if (ballright == 1) {
        ballx = ballx +1;
      }
      if (ballright == -1) {
        ballx = ballx - 1;
      }
      if (balldown == 1) {
        bally = bally + 1;
      }
      if (balldown == -1) {
        bally = bally - 1;
      }
      if (ballx == playerx + paddlewidth && playery < bally + ballsize && playery + paddleheight > bally) {
        ballright = 1;
      }
      if (ballx + ballsize == computerx && computery < bally + ballsize && computery + paddleheight > bally) {
        ballright = -1;
      }
      if (bally == 0) {
        balldown = 1;
      }
      if (bally + ballsize == 63) {
        balldown = -1;
      }
      if (arduboy.pressed(UP_BUTTON) && playery > 0) {
        playery = playery - 1;
      }
      if (arduboy.pressed(DOWN_BUTTON) && playery + paddleheight < 63) {
        playery = playery + 1;
      }
      if (ballx > 112 || random(1, hard) == 1) {
        if (bally < computery) {
          computery = computery - 1;
        }
        if (bally + ballsize > computery + paddleheight) {
          computery = computery + 1;
        }  
      }
      if (ballx < -10) {
        ballx = 63;
        computerscore = computerscore + 1;
      }
      if (ballx > 130) {
        ballx = 63;
        playerscore = playerscore + 1;
      }
      if (playerscore == score) {
        gamestate = 2;
      }
      if (computerscore == score) {
        gamestate = 3;
      }
      break;

    case 2:
      //win screen
      arduboy.setCursor(0, 0);
      if (hard >= 12) {
        arduboy.print("You did it, but");
        arduboy.print("\n");
        arduboy.print("are you proud?");
        arduboy.print("\n");
        arduboy.print("\n");
        arduboy.print("Press A to reset");
      }
      else {
        arduboy.print("Well done!");
        arduboy.print("\n");
        arduboy.print("\n");
        arduboy.print("Press A to reset");
      }
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 0;
      }
      resetgame();
      break;

    case 3:
      //game over screen
      arduboy.setCursor(0, 0);
      if (hard == 2){
        arduboy.print("I fucking told you");
        arduboy.print("\n");
        arduboy.print("it was impossible");
      }
      if (hard >= 12) {
        arduboy.print("Cor blimey, you're");
        arduboy.print("\n");
        arduboy.print("rubbish!");
      }
      if (hard <= 11 && hard >= 3) {
        arduboy.print("You weren't fast");
        arduboy.print("\n");
        arduboy.print("enough, mate");
      }
      arduboy.setCursor(0, 40);
      arduboy.print("Press A to reset");
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 0;
      }
      resetgame();
      break;

    case 4:
    //Settings
    arduboy.setCursor(0, 0);
    arduboy.print("left/right for hard");
    arduboy.print("\n");
    arduboy.print("Lower is harder");
    arduboy.print("\n");
    arduboy.print(hard);
    if (hard <= 5 && hard >= 3) {
      arduboy.print("-tricky");
    }
    if (hard == 2) {
      arduboy.print("-impossible");
    }
    if (hard >= 12) {
      arduboy.print("-grow a pair");
    }
    arduboy.print("\n");
    arduboy.print("\n");
    arduboy.print("up/down for score");
    arduboy.print("\n");
    arduboy.print(score);
    arduboy.print("\n");
    arduboy.print("\n");
    arduboy.print("A to continue");
    if (arduboy.justPressed(RIGHT_BUTTON)){
      hard = hard + 1;
    }
    if (arduboy.justPressed(LEFT_BUTTON)){
      hard = hard - 1;
    }
    if (arduboy.justPressed(UP_BUTTON)){
      score = score + 1;
    }
    if (arduboy.justPressed(DOWN_BUTTON)){
      score = score - 1;
    }
    if (arduboy.justPressed(A_BUTTON)){
      gamestate = 0;
    }
    if (hard > 20) {
      hard = 20;
    }
    if (hard < 2) {
      hard = 2;
    }
    if (score < 1) {
      score = 1;
    }
  }
  arduboy.display();
  }
