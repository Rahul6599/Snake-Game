#include <iostream>
#include<stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool GameOver;

const int width = 20;
const int height = 20;
int x, y;           // snake head coordinate
int fruitX, fruitY; // fruit coordinate
int ntails;
int tailX[100],tailY[100];
int Score;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

void setup()
{
    GameOver = false;
    dir = STOP;
    x = width / 2;  // initial snake head X  Coordinate
    y = height / 2; //  initial snake head Y Coordinate

    fruitX = rand() % width;  // initial fruit X  Coordinate
    fruitY = rand() % height; // initial fruit Y  Coordinate

    Score = 0; // Initial score of snake
}

void Draw()
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";

            if (j == x && i == y)
                cout << "O";
            else if (j == fruitX && i == fruitY)
                cout << "F";
            else
            {
                bool print=false;

                for(int k=0;k<ntails;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }

                if(!print)
                cout<<" ";
            }
                

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "SCORE:: " << Score << endl;
    
}

void Input()
{
    if (_kbhit()) // check keyboard key press or not
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            GameOver = true;
            break;
        }
    }
}

void Logic()
{

    int prevX=tailX[0];
    int prevY=tailY[0];

    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;

    for(int i=1;i<ntails;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }


    
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //GameOver=true;

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;

        if(y<0)
        y=height-1;
        else if(y>=height)
        y=0;

        for(int i=0;i<ntails;i++)
        {
            if(tailX[i]==x && tailY[i]==y)
            GameOver=true;
        }

    if (x == fruitX && y == fruitY)
    {
        Score += 10;

        fruitX = rand() % width;  // new  fruit X  Coordinate
        fruitY = rand() % height; // new  fruit Y  Coordinate
        ntails++;
    }
}

int main()
{
    setup();
    while (!GameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
        
    }

    return 0;
}
