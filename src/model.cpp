#include"../head/model.h"

// Model part ******************************************
void Model::rotX(double rotv_x){
        rotv_x *= M_PI/180;
        auto pv = reinterpret_cast<double(*)[3]>(this);
        for(int i=0;i<8;++i){
            pv[i][1] = pv[i][1]*cos(rotv_x) - pv[i][2]*sin(rotv_x);
            pv[i][2] = pv[i][1]*sin(rotv_x) + pv[i][2]*cos(rotv_x);
        }
}

void Model::rotY(double rotv_y){
        rotv_y *= M_PI/180;
        auto pv = reinterpret_cast<double(*)[3]>(this);
        for(int i=0;i<8;++i){
            pv[i][0] = pv[i][0]*cos(rotv_y) + pv[i][2]*sin(rotv_y);
            pv[i][2] = -pv[i][0]*sin(rotv_y) + pv[i][2]*cos(rotv_y);
        }
}

void Model::rotZ(double rotv_z){
        rotv_z *= M_PI/180;
        auto pv = reinterpret_cast<double(*)[3]>(this);
        for(int i=0;i<8;++i){
            pv[i][0] = pv[i][0]*cos(rotv_z) - pv[i][1]*sin(rotv_z);
            pv[i][1] = pv[i][0]*sin(rotv_z) + pv[i][1]*cos(rotv_z);
        }
        //std::cout<<pv[0][0]<<" "<<pv[0][1]<<" "<<pv[0][2]<<std::endl;
}

void Model::updateCentre(){
    auto pv = reinterpret_cast<double(*)[3]>(this);
    s_centre[0] = pv[0][0]+pv[1][0]+pv[2][0]+pv[3][0];
    s_centre[1] = pv[0][0]+pv[1][0]+pv[4][0]+pv[5][0];
    s_centre[2] = pv[0][0]+pv[2][0]+pv[4][0]+pv[6][0];
    s_centre[3] = pv[6][0]+pv[7][0]+pv[2][0]+pv[3][0];
    s_centre[4] = pv[5][0]+pv[7][0]+pv[1][0]+pv[3][0];
    s_centre[5] = pv[4][0]+pv[5][0]+pv[6][0]+pv[7][0];
    for(int i=0;i<6;++i){
        surfaces[i] = i;
    }

    for(int i=0;i<5;++i){
        bool flag = false;
        for(int j=0;j<5;++j){
            if(s_centre[surfaces[j]]<s_centre[surfaces[j+1]]){
                swap(surfaces[j],surfaces[j+1]);
                flag = true;
            }
        }
        if(!flag) break;
    }
    /*
    for(int i=0;i<6;++i){
        std::cout<<static_cast<int>(surfaces[i])<<std::endl;
    }
    */
}

char* Model::getSurfaces(){
    return surfaces;
}

//Screen part ******************************************
Screen::Screen(Model* m):model(m){}

void Screen::updateScreen(){
    auto ps = reinterpret_cast<double(*)[2]>(this);
    auto pm = reinterpret_cast<double(*)[3]>(model);
    for(int i=0;i<8;++i){
        double prop = LEN_SV/(LEN_VO+pm[i][0]);
        ps[i][0] = prop*pm[i][1];
        ps[i][1] = prop*pm[i][2];
    }
}
