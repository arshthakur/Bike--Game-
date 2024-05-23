#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <thread>  // For sleep
#include <chrono>  // For sleep duration

using namespace std;

// Constants for game
const int WIDTH = 20;
const int HEIGHT = 10;
const char BIKE_CHAR = 'B';
const char TRACK_CHAR = '.';
const char OBSTACLE_CHAR = 'O';

// Game variables
int bikePos = WIDTH / 2;
bool gameOver = false;
int score = 0;

// Function to display the game track
void displayTrack()
{
  system("cls");
  for (int i = 0; i < HEIGHT; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      if (i == HEIGHT - 1 && j == bikePos)
      {
        cout << BIKE_CHAR;
      }
      else if (i == 0 && (j == bikePos - 1 || j == bikePos + 1))
      {
        cout << OBSTACLE_CHAR;
      }
      else
      {
        cout << TRACK_CHAR;
      }
    }
    cout << endl;
  }
  cout << "Score: " << score << endl;
}

// Function to handle user input
void handleInput()
{
  if (_kbhit())
  {
    switch (_getch())
    {
    case 'a':
      bikePos--;
      if (bikePos < 0)
        bikePos = 0;
      break;
    case 'd':
      bikePos++;
      if (bikePos >= WIDTH)
        bikePos = WIDTH - 1;
      break;
    }
  }
}

// Function to update the game logic
void updateGame()
{
  // Move obstacles down
  static int obstaclePos = bikePos;
  static int obstacleRow = 0;

  if (obstacleRow == HEIGHT - 1)
  {
    obstacleRow = 0;
    obstaclePos = rand() % WIDTH;
    score++;
  }
  else
  {
    obstacleRow++;
  }

  // Check for collision
  if (obstacleRow == HEIGHT - 1 && abs(obstaclePos - bikePos) <= 1)
  {
    gameOver = true;
  }
}

// Main function
int main()
{
  while (!gameOver)
  {
    displayTrack();
    handleInput();
    updateGame();
    this_thread::sleep_for(chrono::milliseconds(200));
  }

  cout << "Game Over! Your final score is: " << score << endl;
  return 0;
}
