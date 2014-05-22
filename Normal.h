//
//  Normal.h
//  ExamenLabprogra
//
//  Created by Edwin Herrera on 5/18/14.
//  Copyright (c) 2014 Edwin Herrera. All rights reserved.
//

#ifndef ExamenLabprogra_Normal_h
#define ExamenLabprogra_Normal_h

#include "Burbuja.h"

class Normal : public Burbuja{
public:
    
    Normal(){
        
    }
    Normal(SDL_Surface* surface, int x, int y, SDL_Surface* screen){
        this->surface = surface;
        this->x = x;
        this->y = y;
        this->screen = screen;
        this->clicked = false;
        this->puntos = 1;
        this->tipo = "normal";
        
    }
    
    
    virtual ~Normal(){
        
    }
    

    
};



#endif
