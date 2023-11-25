#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#define WIDTH 50
#define HEIGHT 10

struct Snake
{
    int vel_x;
    int vel_y;
    int length;
    int top;
    int body[WIDTH * HEIGHT][2];
};

int foodPos[2];
struct Snake snake;
int temp;

char snakeChar = 'X';
char backgroundChar = ' ';
char borderChar = '0';
char foodChar = 'D';

void initialize()
{
    // Initialize all values of the array
    for (int i = 0; i < (HEIGHT * WIDTH); i++)
    {
        snake.body[i][0] = -1;
        snake.body[i][1] = -1;
    }

    snake.body[0][0] = (int)WIDTH / 2;
    snake.body[0][1] = (int)HEIGHT / 2;

    snake.body[0][0] = (int)(WIDTH / 2) - 1;
    snake.body[0][1] = (int)HEIGHT / 2;

    snake.body[0][0] = (int)(WIDTH / 2) - 2;
    snake.body[0][1] = (int)HEIGHT / 2;

    snake.length = 3;

    snake.vel_x = 1;
    snake.vel_y = 0;
}

int checkGameOver()
{
    for (int i = 0; i < (WIDTH * HEIGHT); i++)
    {
        if (snake.body[i][0] == 0 || snake.body[i][0] == WIDTH - 1 || snake.body[i][1] == 0 || snake.body[i][1] == HEIGHT - 1)
        {
            return 1;
        }
    }
    return 0;
}

void gameOver()
{
    exit(0);
}

int snakeIsHere(int x, int y)
{
    for (int i = 0; i < (WIDTH * HEIGHT); i++)
    {
        // check x and y
        if (x == snake.body[i][0] && y == snake.body[i][1])
        {
            return 1;
        }
    }
    return 0;
}

void putFood()
{
    // foodPos[0] = (rand() % (WIDTH - 2)) + 1;
    // foodPos[1] = (rand() % (HEIGHT - 2)) + 1;

    foodPos[0] = snake.body[0][0] + 6;
    foodPos[1] = snake.body[0][1];
}

int hasEatenFood()
{
    if (snakeIsHere(foodPos[0], foodPos[1]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void update()
{
    if (checkGameOver())
    {
        gameOver();
    }

    if (hasEatenFood())
    {
        snake.length++;
        putFood();
    }

    // Shift all places to right
    for (int i = (HEIGHT * WIDTH) - 1; i >= 0; i--)
    {
        snake.body[i + 1][0] = snake.body[i][0];
        snake.body[i + 1][1] = snake.body[i][1];
    }

    snake.body[0][0] += snake.vel_x;
    snake.body[0][1] += snake.vel_y;

    snake.top++;

    // Do a cleanup
    while (snake.top + 1 > snake.length)
    {
        snake.body[snake.top][0] = -1;
        snake.body[snake.top][1] = -1;
        snake.top--;
    }
}

void render()
{
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            if (snakeIsHere(i, j))
            {
                printf("%c", snakeChar);
            }
            else if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1)
            {
                printf("%c", borderChar);
            }
            else if (i == foodPos[0] && j == foodPos[1])
            {
                printf("%c", foodChar);
            }
            else
            {
                printf("%c", backgroundChar);
            }
        }
        printf("\n");
    }
}

void updateVelocity()
{
    if ()
    {
        printf("\nGot it");
    }
}

void main()
{
    system("clear");

    initialize();

    putFood();

    while (1)
    {
        update();
        render();
        usleep(500000);
        updateVelocity();
        system("clear");
    }
}