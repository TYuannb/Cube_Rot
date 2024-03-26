#pragma once
#include<bits/stdc++.h>
#include<iostream>
#include"help_func.h"
#define LEN_SV 2
#define LEN_VO 4


class Model{
public:
    Model() = default;
    ~Model() = default;
public:
    void rotX(double rotv_x = 1);
    void rotY(double rotv_y = 1);
    void rotZ(double rotv_z = 1);
    void updateCentre();
    char* getSurfaces();
private:
    double p000[3] = {1,1,1};
    double p001[3] = {1,1,-1};
    double p010[3] = {1,-1,1};
    double p011[3] = {1,-1,-1};
    double p100[3] = {-1,1,1};
    double p101[3] = {-1,1,-1};
    double p110[3] = {-1,-1,1};
    double p111[3] = {-1,-1,-1};
private:
    char surfaces[6] = {0,1,2,3,4,5};
    double s_centre[6] = {4,0,0,0,0,-4};
};

class Screen{
public:
    Screen(Model*);
    void updateScreen();
private:
    double p000[3] = {0,0};
    double p001[3] = {0,0};
    double p010[3] = {0,0};
    double p011[3] = {0,0};
    double p100[3] = {0,0};
    double p101[3] = {0,0};
    double p110[3] = {0,0};
    double p111[3] = {0,0};
    Model* model;
};
