#pragma once
#include<iostream>
#include<bits/stdc++.h>
#include"model.h"
#include"help_func.h"
#define MAP_SIZE_Y 40
#define MAP_SIZE_X 2*MAP_SIZE_Y
#define SCAN 40
#define SCALE 1.6/sqrt(3)


class Render{
public:
    Render(Screen*, Model*);
public:
    void cleanScreen();
    void updateVertices();
    void updateVertex(double*, char);
    void updateEdges();
    void updateEdge(double*, double*, char);
    void updateSurfaces();
    void updateSurface(double*, double*, double*, char);
    void rendScreen();
private:
    char m_map[MAP_SIZE_Y][MAP_SIZE_X];
    Model* model;
    Screen* screen;
};

class RenderManager{
public:
    RenderManager();
    ~RenderManager();
public:
    void Play();
private:
    Model* model;
    Screen* screen;
    Render* render;
};
