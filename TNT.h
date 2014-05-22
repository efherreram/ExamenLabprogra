//
//  TNT.h
//  ExamenLabprogra
//
//  Created by Edwin Herrera on 5/19/14.
//  Copyright (c) 2014 Edwin Herrera. All rights reserved.
//

#ifndef ExamenLabprogra_TNT_h
#define ExamenLabprogra_TNT_h

#include "Burbuja.h"

class TNT : public Burbuja{
public:
    
    TNT(){
        
    }
    TNT(SDL_Surface* surface, int x, int y, SDL_Surface* screen){
        this->surface = surface;
        this->x = x;
        this->y = y;
        this->screen = screen;
        this->clicked = false;
        this->puntos = 1;
        this->tipo = "tnt";
        
    }
    
    
    virtual ~TNT(){
        
    }
    
    
    
};


#endif
