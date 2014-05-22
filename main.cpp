//
//  main.cpp
//  ExamenLabprogra
//
//  Created by Edwin Herrera on 5/15/14.
//  Copyright (c) 2014 Edwin Herrera. All rights reserved.
//

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h" //cambiar los sdl
#include "SDL/SDL_mixer.h"  //cambiar los sdl
#include "SDL/SDL_ttf.h"    //cambiar los sdl
#include "Burbuja.h"
#include <list>
#include <stdlib.h>
#include <time.h>
#include "Normal.h"
#include "Malvada.h"
#include "Hielo.h"
#include "TNT.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>


//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 28;

int burbujax = 0;
int burbujay = 0;
int velburbuja = 3;
int score = 0;
bool won = false;




//The surfaces
SDL_Surface *background = NULL;

SDL_Surface *screen = NULL;

SDL_Surface *puntos = NULL;

Mix_Music *music = NULL;

SDL_Surface *victory = NULL;

SDL_Surface *tuto = NULL;

Mix_Music *menuMusic = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
  
    
    //Return the optimized surface
    return IMG_Load(filename.c_str());
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool wayToSort(int i, int j){ return i>j;}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }
    
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)== 1){
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );
    
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "Sources/background.png" ); //agregar "Sources/" antes de los elementos a utilizar
    victory = load_image("Sources/hazganado.png");
    
    //Open the font
    font = TTF_OpenFont( "Sources/stocky.ttf", 60 );
    
    music = Mix_LoadMUS("Sources/bubbl.ogg"); //THIS
    
    menuMusic = Mix_LoadMUS("Sources/menu.ogg");
    tuto = load_image("Sources/tuto.png");
    
    
    
    if(music == NULL){
        return false;
    }
    
    if (menuMusic == NULL) {
        return false;
    }
    
    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }
    
    if(victory == NULL){
        return false;
    }
    
    if(tuto == NULL){
        return false;
    }
    
    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }
    
    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    
    //Close the font
    TTF_CloseFont( font );
    
    Mix_FreeMusic(music);
    Mix_FreeMusic(menuMusic);
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
}



void victoryScreen(){
    bool quit = false;
    
    
    while (quit == false) {
        apply_surface(0, 0, background, screen);
        apply_surface(0, 0, victory, screen);
        
        if(SDL_Flip(screen) == -1){
            return;
        }
        
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
            
            if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_RETURN) ) {
                return;
            }
            
            
        }

    }
    
}

void scoreScreen(){
    bool quit = false;
    std::ifstream read("puntos_max.txt");
    int mayor;
    read >> mayor;
    std::stringstream SCORE;
    SCORE << "RECORD: " << mayor;
    puntos = TTF_RenderText_Solid(font, SCORE.str().c_str(), textColor);
    
    while(quit == false){
        
        
         /////
        
        apply_surface(0, 0, background, screen);
        apply_surface(0, 0, puntos, screen);
        
        
        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }
        
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
                return;
            
        }
    }
    

}

void tutorial(){
    
    bool quit = false;
    while(quit == false){
        
        
        /////
        
        apply_surface(0, 0, background, screen);
        apply_surface(0, 0, tuto, screen);
        
        
        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }
        
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
                return;
            
        }
    }

}

void elJuego(){
    srand(time(NULL));
    bool quit = false;
    std::list<Burbuja*> burbujas;
    std::vector<int> puntaje;
    
    score = 0;
    int click_x = -1;
    int click_y = -1;
    int frame = 0;
    int tipo;
    int vel = 3;
    int tmp = 0;
    
    
    //While the user hasn't quit
    while( quit == false )
    {
        
        if(score== 50){
            Mix_HaltMusic();
            int tmp;
            std::ifstream in("puntos_max.txt");
            while(in>>tmp){
                puntaje.push_back(tmp);
            }
            puntaje.push_back(score);
            
            in.close();
            
            std::sort(puntaje.begin(), puntaje.end(), wayToSort);
            
            std::ofstream out("puntos_max.txt");
            
            for (int i=0; i<puntaje.size(); i++) {
                out << puntaje[i];
                out << "\n";
            }
            
            
            out.close();
            
            victoryScreen();
            return;
        }
        
               if(Mix_PlayingMusic()==0){
            if(Mix_PlayMusic(music, -1) == -1){
                return;
            }
            
            Mix_VolumeMusic(30);
        }
        
        click_x = NULL;
        click_y = NULL;
        frame++;
        if(frame%100 == 0){
             tipo = rand() % 4 +1;
            
            //Instruido en sprites de burbujas por oscar
            switch (tipo) {
                case 1:
                    burbujas.push_back(new Normal(load_image("Sources/burbuja.png"), 0, rand() % 300+110, screen));
                    break;
                case 2:
                    burbujas.push_back(new Malvada(load_image("Sources/mala.png"), 0, rand() % 300+110, screen));
                    break;
                case 3:
                    burbujas.push_back(new Hielo(load_image("Sources/hielo.png"), 0, rand() % 300+110, screen));
                    break;
                case 4:
                    burbujas.push_back(new TNT(load_image("Sources/explosiva.png"), 0, rand() % 300+110, screen));
                    break;
                    
                default:
                    break;
            }
            
        }
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                Mix_HaltMusic();
                quit = true;
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE){
                
                Mix_HaltMusic();
                int tmp;
                std::ifstream in("puntos_max.txt");
                while(in>>tmp){
                    puntaje.push_back(tmp);
                }
                puntaje.push_back(score);
                
                in.close();
                
                std::sort(puntaje.begin(), puntaje.end(), wayToSort);
                
                std::ofstream out("puntos_max.txt");
                
                for (int i=0; i<puntaje.size(); i++) {
                    out << puntaje[i];
                    out << "\n";
                }
                
                
                    out.close();
                
                return;
            }
            
            
            
            
            if(event.type == SDL_MOUSEBUTTONDOWN){
                
                click_x = event.button.x;
                click_y = event.button.y;
                
            }
            
        }
        
        //Apply the background
        apply_surface( 0, 0, background, screen );
        
        
        std:: list<Burbuja*> :: iterator i = burbujas.begin();
        while (i!=burbujas.end()) {
            
            if ((*i)->x > SCREEN_WIDTH) {
                Burbuja* b = (*i);
                i = burbujas.erase(i);
                delete b;
            }
            else if((*i)->clicked){
                
                 if ((*i)->tipo == "hielo"){
                     vel = 0;
                }
                else if ((*i)->tipo == "tnt"){
                    std:: list<Burbuja*> :: iterator it = burbujas.begin();
                    while(it!=burbujas.end()){
                        (*it)->clicked = true;
                        it++;
                    }
                    

                }
                
                Burbuja* b = (*i);
//                if(b->tipo == "malo"){
//                    if(score>0){
//                        score+=b->puntos;
//                    }
//                }
//                else{
                    score+=b->puntos;
                
                i = burbujas.erase(i);
                delete b;
                
                
                
                
            } else{
                
                (*i) -> imprimir();
                (*i) -> logica(click_x, click_y, vel);
                
            }
            
            i++;
            if(vel == 0){
                tmp++;
                if(tmp == 100){
                    vel = 3;
                    tmp = 0;
                }
                
            }
            
            
        }
        
        std::stringstream SCORE;
        
        SCORE << "SCORE: " << score;
        puntos = TTF_RenderText_Solid(font, SCORE.str().c_str(), textColor); /////
        
        apply_surface(0, 0, puntos, screen);
        
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }
        
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
            return;
        }
    }

    
    
}

void menu(){
    SDL_Surface* menu = load_image("Sources/Menu.png");
    bool quit = false;
    while (quit == false) {
        
        if (Mix_PlayingMusic() == 0) {
            if (Mix_PlayMusic(menuMusic, -1) == -1) {
                return;
            }
            Mix_VolumeMusic(30);
            
        }
        
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                quit = true;
                
            }
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
                Mix_HaltMusic();
                elJuego();
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s){
                scoreScreen();
            }
            
            apply_surface(0, 0, menu, screen);
            
            if(SDL_Flip(screen) == -1){
                return;
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
                tutorial();
            }

            
        }
    }
}





int main( int argc, char* args[] )
{
    
    //Initialize
    if( init() == false )
    {
        return 1;
    }
    
    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
    
    //Render the text

    menu();
    
    
    //Clean up
    clean_up();
    
    return 0;
}
