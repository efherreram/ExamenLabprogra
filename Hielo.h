//
//  Hielo.h
//  ExamenLabprogra
//
//  Created by Edwin Herrera on 5/19/14.
//  Copyright (c) 2014 Edwin Herrera. All rights reserved.
//

#ifndef ExamenLabprogra_Hielo_h
#define ExamenLabprogra_Hielo_h

#include "Burbuja.h"

class Hielo : public Burbuja{
public:
    
    Hielo(){
        
    }
    Hielo(SDL_Surface* surface, int x, int y, SDL_Surface* screen){
        this->surface = surface;
        this->x = x;
        this->y = y;
        this->screen = screen;
        this->clicked = false;
        this->puntos = 1;
        this->tipo = "hielo";
        
    }
    
    
    virtual ~Hielo(){
        
    }
    
    
    
};

#endif
