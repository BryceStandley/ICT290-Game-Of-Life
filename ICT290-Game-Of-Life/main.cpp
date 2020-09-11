// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  What does this program do?
//  This program is a implementation of Conway's Game of Life using C++ and OpenGL
//  
//  The starting grid size and starting pattern are read in from a given config file and used to start the simulation
//
//  Program written by Bryce Standley 
//  Murdoch Student Number: 33046367
//  Date: 09/06/2020
//  Unit: ICT290 Computer Graphics
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <GL/glew.h>
#include <GL/glut.h>

#define WHITE 1,1,1
#define BLACK 0,0,0
#define ScreenWidth 800
#define ScreenHeight 800
#define LOG(foo, x) std::cout << foo << x << std::endl
typedef unsigned char pixel;

void display(void);
//void reshape(int, int);
bool readConfig(void);
void elementryCA(void);
void drawCA(void);
void init(void);
void timer(int);
int countneighbors(int, int);
void generateRandomStates(void);

std::string configFileName = "gol_cfg.txt";
int gridSizeSquare;
bool debugMode = true;

const int col = 10;
const int row = 10;
int grid[col][row];
pixel image_buffer[col * row];



int main(int argc, char** argv)
{
    //Note config must be placed in the same file as exe and wont file config file in debug mode
    //if (readConfig())
    //{    
    //}

    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize(ScreenWidth, ScreenHeight); // 800x600 window
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Conway's Game Of Life - OpenGL - ICT290 - Bryce Standley");


    init();

    glutMainLoop();

    return 0;
}

void init()
{
    generateRandomStates();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(500, timer, 0);
}


void timer(int time)
{
    elementryCA();
    glutTimerFunc(500, timer, 0);
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawCA();

    glFlush();
}


bool readConfig()
{
    if (!debugMode)
    {
        std::ifstream configFile;
        configFile.open(configFileName);

        if (!configFile.is_open())
        {
            std::cout << "Error when opening config file " << configFileName << " Does the file exist? " << "'" << configFile.eof() << "'" << std::endl;
            return false;
        }

        while (configFile)
        {
            std::string line;
            std::getline(configFile, line, ':');

            configFile >> gridSizeSquare;

            configFile >> std::ws;

            if (!configFile)
            {
                break;
            }

            std::cout << "The grid size is " << gridSizeSquare << " x " << gridSizeSquare << std::endl;
        }
        configFile.close();
        return true;
    }
    else
    {
        gridSizeSquare = 10;
        return true;
    }
}

void generateRandomStates()
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
}

void elementryCA()
{
    int nextGen[col][row];

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            int state = grid[i][j];

            int neighbors = countneighbors(i, j);


            if (state == 0 && neighbors == 3)
            {
                nextGen[i][j] = 1;
            }
            else if (state == 1 && (neighbors < 2 || neighbors > 3))
            {
                nextGen[i][j] = 0;
            }
            else
            {
                nextGen[i][j] = state;
            }
            
        }
    }

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            grid[i][j] = nextGen[i][j];
        }
    }
}

int countneighbors(int x, int y)
{
    int sum = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int wrapCol = (x + i + col) % col;
            int wrapRow = (y + j + row) % row;

            sum += grid[wrapCol][wrapRow];
        }
    }
    sum -= grid[x][y];
    return sum;
}

void drawCA()
{
    GLdouble x = -1;
    GLdouble y = 1;

    GLdouble yPos = 2.0 / row;
    GLdouble xPos = 2.0 / col;

    x -= xPos;
    for (int i = 0; i < col; i++)
    {
        x += xPos;
        y = 1;
        //std::cout << std::endl;
        for (int j = 0; j < row; j++)
        {
            if (grid[i][j] == 1)
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0, 0, 0);
            }
            //counter clockwise
            glBegin(GL_TRIANGLES);
            glVertex3f(x, y, 0);
            glVertex3f(x, y - yPos, 0);
            glVertex3f(x + xPos, y - yPos, 0);

            glVertex3f(x, y, 0);
            glVertex3f(x + xPos, y - yPos, 0);
            glVertex3f(x + xPos, y, 0);
            glEnd();
            y -= yPos;
        }
    } 
}