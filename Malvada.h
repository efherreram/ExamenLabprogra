//
//  Malvada.h
//  ExamenLabprogra
//
//  Created by Edwin Herrera on 5/18/14.
//  Copyright (c) 2014 Edwin Herrera. All rights reserved.
//

#ifndef ExamenLabprogra_Malvada_h
#define ExamenLabprogra_Malvada_h

#include "Burbuja.h"

class Malvada : public Burbuja{
public:
    
    Malvada(){
        
    }
    Malvada(SDL_Surface* surface, int x, int y, SDL_Surface* screen){
        this->surface = surface;
        this->x = x;
        this->y = y;
        this->screen = screen;
        this->clicked = false;
        this->puntos = -1;
        this->tipo = "malo";
        
    }

    
    virtual ~Malvada(){
        
    }
    
    
    
};



#endif
