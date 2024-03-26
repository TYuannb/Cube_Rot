#include"head/model.h"
#include"head/render.h"
#include<unistd.h>

int main(){
    RenderManager rm{};
    for(int i=0;i<10000;++i){
        rm.Play();
        usleep(15000);
        //break;
    }
    
    return 0;
}