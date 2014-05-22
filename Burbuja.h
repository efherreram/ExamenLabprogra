//
//  Burbuja.h
//  ExamenLabprogra
//
//  Created by Edwin Herrera on 5/16/14.
//  Copyright (c) 2014 Edwin Herrera. All rights reserved.
//

#ifndef ExamenLabprogra_Burbuja_h
#define ExamenLabprogra_Burbuja_h

#include <list>

class Burbuja{
    
public:
    SDL_Surface* surface;
    int x;
    int y;
    SDL_Surface *screen;
    int velocidad;
    int puntos;
    std::string tipo;
    
    bool clicked;
    
    Burbuja(){
        
    }
    
    
    void imprimir(){
        //Holds offsets
        SDL_Rect offset;
        
        //Get offsets
        offset.x = x;
        offset.y = y;
        
        //Blit
        SDL_BlitSurface( surface, NULL, screen, &offset );
 
    }
    
    virtual void logica(int click_x, int click_y, int vel){
        if(click_x>=this->x && click_x <= this->x + this->surface->w && click_y >= this->y &&
           click_y<= this->y + this->surface->h){
            
            this->clicked = true;
            
        }
        avanzar(vel);
    }
    
    virtual void avanzar(int vel){
        this->x+=vel;
    }
    
    virtual ~Burbuja(){
        
    }
    
};





#endif
