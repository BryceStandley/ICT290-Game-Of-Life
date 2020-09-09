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
#include <GL/glew.h>
#include <GL/glut.h>

void display(void);
void reshape(int, int);
void readConfig(void);

std::string configFileName = "gol_cfg.txt";
int gridSizeSquare;


int main(int argc, char** argv)
{
    //Note config must be placed in the same file as exe and wont file config file in debug mode
    readConfig();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(800, 600); // 800x600 window
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Conway's Game Of Life - OpenGL - ICT290 - Bryce Standley");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    //More Glut Func settings go here

    glutMainLoop();

    return 0;
}


void display()
{

}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();


}

void readConfig()
{
    std::ifstream configFile;
    configFile.open(configFileName);

    if (!configFile.is_open())
    {
        std::cout << "Error when opening config file " << configFileName << " Does the file exist? " << "'" << configFile.eof() << "'" << std::endl;
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
}

