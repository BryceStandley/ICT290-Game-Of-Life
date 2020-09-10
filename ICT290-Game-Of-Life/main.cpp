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
void reshape(int, int);
bool readConfig(void);
void elementryCA(void);
void drawCA(void);
void init(void);
void generatePixels(int, int, int, int);

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

    elementryCA();

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
    
   
    

    glutDisplayFunc(display);
    glutIdleFunc(display);
    

    
    /*
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutCreateWindow("Conway's Game Of Life - OpenGL - ICT290 - Bryce Standley");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    //glutTimerFunc(1000 / 60, timer, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, (float)ScreenWidth, 0.0f, (float)ScreenHeight);
    glTranslatef(0, 0, -20);
    */
}

void display()
{


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //glTranslatef(0, 0, -10);

    drawCA();
/*
    GLdouble x = -1;
    GLdouble y = 1;
    GLdouble yPos = 1.0 / row;
    GLdouble xPos = 1.0 / col;

    //std::cout << "xPos: " << (double)xPos << std::endl;
    
    //glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex3f(x, y, 0);
    glVertex3f(x, y - yPos, 0);
    glVertex3f(x + xPos, y - yPos, 0);

    glVertex3f(x, y, 0);
    glVertex3f(x + xPos, y - yPos, 0);
    glVertex3f(x + xPos, y, 0);
    glEnd();
    
    glBegin(GL_TRIANGLES); // Triangles
    glVertex2d(x, y); // top left 1 0,0

    glVertex2d(x, y - yPos); //bottom left 2 0,-1
    glVertex2d(x + xPos, y - yPos); //bottom right 3 1,-1

    glVertex2d(x, y); // top left 1 0,0
    glVertex2d(x + xPos, y - yPos); //bottom right 3 1,-1
    glVertex2d(x + xPos, y); //top left 4 1,0
    glEnd();
    */

    //glDrawPixels(col, row, GL_LUMINANCE, GL_UNSIGNED_BYTE, image_buffer);
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


void elementryCA()
{
    for (int i = 0; i < col; i++)
    {
        std::cout << std::endl;
        for (int j = 0; j < row; j++)
        {
            grid[i][j] = rand() % 2;
            std::cout << grid[i][j];

        }
        
    }
}

void drawCA()
{
    GLdouble x = -1;
    GLdouble y = 1;

    GLdouble yPos = 1.0 / row;
    GLdouble xPos = 1.0 / col;

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

void generatePixels(int xOff, int yOff, int width, int height)
{
    int offset = 0;
    for (int r = row - 1; r >= 0; r--) {
        for (int c = 0; c < col; c++) {
            image_buffer[col * offset + c] = grid[c][r];
            LOG("image buffer: ", image_buffer[col * offset + c]);
        }
        offset++;
    }
}

