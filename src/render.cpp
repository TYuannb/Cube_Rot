#include"../head/render.h"
#include<iostream>

//render part *************************************************
Render::Render(Screen* scr, Model* md):screen(scr),model(md){
    for(int i=0; i<MAP_SIZE_Y; ++i){
        for(int j=0; j<MAP_SIZE_X; ++j) m_map[i][j] = ' ';
    }
}

void Render::cleanScreen(){
    for(int i=0; i<MAP_SIZE_Y; ++i){
        for(int j=0; j<MAP_SIZE_X; ++j) m_map[i][j] = ' ';
    }
}

void Render::updateVertices(){
    auto ps = reinterpret_cast<double(*)[2]>(screen);
    for(int i=0;i<8;++i){
        updateVertex(ps[i], '*');
    }
}

void Render::updateVertex(double* p, char sym){
    int x = round(p[0]*MAP_SIZE_X*SCALE/2) + MAP_SIZE_X/2;
    int y = round(p[1]*MAP_SIZE_Y*SCALE/2) + MAP_SIZE_Y/2;
    m_map[y][x] = sym;
}

void Render::updateEdges(){
    auto ps = reinterpret_cast<double(*)[2]>(screen);
    //p000-p001
    updateEdge(ps[0],ps[1],'*');
    //p001-p011
    updateEdge(ps[1],ps[3],'*');
    //p011-p010
    updateEdge(ps[3],ps[2],'*');
    //p010-p001
    updateEdge(ps[2],ps[0],'*');

    //p100-p101
    updateEdge(ps[4],ps[5],'*');
    //p101-p111
    updateEdge(ps[5],ps[7],'*');
    //p111-p110
    updateEdge(ps[7],ps[6],'*');
    //p110-p100
    updateEdge(ps[6],ps[4],'*');

    //p000-p100
    updateEdge(ps[0],ps[4],'*');
    //p001-p101
    updateEdge(ps[1],ps[5],'*');
    //p011-p111
    updateEdge(ps[3],ps[7],'*');
    //p010-p110
    updateEdge(ps[2],ps[6],'*');
}

void Render::updateEdge(double *p1, double *p2, char sym){
    
    double x1 = p1[0]*MAP_SIZE_X*SCALE/2 + MAP_SIZE_X/2;
    double y1 = p1[1]*MAP_SIZE_Y*SCALE/2 + MAP_SIZE_Y/2;
    double x2 = p2[0]*MAP_SIZE_X*SCALE/2 + MAP_SIZE_X/2;
    double y2 = p2[1]*MAP_SIZE_Y*SCALE/2 + MAP_SIZE_Y/2;

    double tx12 = (x2-x1)/SCAN;
    double ty12 = (y2-y1)/SCAN;
    double x = x1;
    double y = y1;
    int rx, ry;
    for(int i = 0;i<SCAN+1;++i){
        rx = round(x);
        ry = round(y);
        m_map[ry][rx] = sym;
        x += tx12;
        y += ty12;
    }
}

void Render::updateSurfaces(){
    auto ps = reinterpret_cast<double(*)[2]>(screen);
    int enum_s = 0;
    for(int i=0;i<6;++i){
        enum_s = model->getSurfaces()[i];
        switch(enum_s){
            case(0):
                //p000-p001-010
                updateSurface(ps[0],ps[1],ps[2],'%');
                //p011-p010-001
                updateSurface(ps[3],ps[2],ps[1],'%');
                break;
            case(1):
                //p000-p100-p101
                updateSurface(ps[0],ps[4],ps[5],'+');
                //p101-p001-p000
                updateSurface(ps[5],ps[1],ps[0],'+');
                break;
            case(2):
                //p000-p010-p100
                updateSurface(ps[0],ps[2],ps[4],'.');
                //p110-p010-p100
                updateSurface(ps[6],ps[2],ps[4],'.');
                break;
            case(3):
                //p010-p011-p110
                updateSurface(ps[2],ps[3],ps[6],'T');
                //p111-p011-p110
                updateSurface(ps[7],ps[3],ps[6],'T');
                break;
            case(4):
                //p001-p011-p101
                updateSurface(ps[1],ps[3],ps[5],',');
                //p111-p011-p101
                updateSurface(ps[7],ps[3],ps[5],',');
                break;
            case(5):
                //p100-p110-p101
                updateSurface(ps[4],ps[6],ps[5],'#');
                //p111-p110-p101
                updateSurface(ps[7],ps[6],ps[5],'#');
                break;
        }
    }

    
}

void Render::updateSurface(double* p1, double* p2, double* p3, char sym){
    double x1 = p1[0];
    double y1 = p1[1];
    double x2 = p2[0];
    double y2 = p2[1];
    double x3 = p3[0];
    double y3 = p3[1];

    double tx12 = (x2-x1)/SCAN;
    double ty12 = (y2-y1)/SCAN;
    double tx13 = (x3-x1)/SCAN;
    double ty13 = (y3-y1)/SCAN;
    
    double ps1[2] = {x1,y1};
    double ps2[2] = {x1,y1};
    std::cout<<ps1[0]<<' '<<ps1[1]<<std::endl;
    for(int i = 0;i<SCAN+1;++i){
        updateEdge(ps1,ps2,sym);
        ps1[0] += tx12;
        ps1[1] += ty12;
        ps2[0] += tx13;
        ps2[1] += ty13;
    }
}

void Render::rendScreen(){
    printf("\033c");
    for(int i=0;i<MAP_SIZE_Y;++i){
        for(int j=0;j<MAP_SIZE_X;++j){
            std::cout<<m_map[i][j];
        }
        std::cout<<std::endl;
    }
}


//renderManager part *************************************************
RenderManager::RenderManager(){
    model = new Model();
    screen = new Screen(model);
    render = new Render(screen,model);
}

RenderManager::~RenderManager(){
    if(model) delete model;
    if(screen) delete screen;
    if(render) delete render;
}

void RenderManager::Play(){
    model->updateCentre();
    screen->updateScreen();
    //render->updateVertices();
    //render->updateEdges();
    
    render->updateSurfaces();
    render->rendScreen();
    render->cleanScreen();
    model->rotX(0.3);
    model->rotY(0.8);
    model->rotZ(1);
}
