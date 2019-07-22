#include <gb/gb.h>
#include <stdio.h>
#include "SplashScreen_data.c"
#include "SplashScreen_map.c"
#include "Background.c"
#include "BackgroundTiles.c"
#include "GameSprites.c"
#include "GameCharacter.c"

//Creates Strrctures for each of the sprites
struct GameCharacter dino;
struct GameCharacter dino1;
struct GameCharacter catcus;
struct GameCharacter bird;

//The size of each sprite is 8
UBYTE spritesize = 8;

//Jumping variables
BYTE jumping;
UINT8 gravity = -2;
UINT8 currentspeedY;
UINT8 floorYposition = 105;

//Misc variables
UINT8 i;

UBYTE checksollisions(struct GameCharacter* one, struct GameCharacter* two, struct GameCharacter* three){
    //One is Dino. Two is catus. Three is bird
    return
    (one->x >= two->x && one->x <= two->x + two->width-3) && (one->y >= two->y && one->y <= two->y + two->height-4) ||
    (two->x >= one->x && two->x <= one->x + one->width-3) && (two->y >= one->y && two->y <= one->y + one->height-3) ||
    (one->x >= three->x && one->x <= three->x + three->width) && (one->y >= three->y && one->y <= three->y + three->height) ||
    (three->x >= one->x && three->x <= one->x + one->width) && (three->y >= one->y && three->y <= one->y + one->height);

}

//Performance delay instead of delay because delay locks up the cpu
void performancedelay(UINT8 numloops){
    UINT8 ii;
    for(ii = 0; ii < numloops; ii++){
        wait_vbl_done();
    } 
}

//Creates a fadeout effect
void fadeout(){
    for(i = 0; i < 4; i++){
        switch(i){
            case 0:
            BGP_REG = 0xE4;
            break;
            case 1:
            BGP_REG = 0xF9;
            break;
            case 2:
            BGP_REG = 0xFE;
            break;
            case 3:
            BGP_REG = 0xFF;
            break;
        }
        performancedelay(2);
    }
}

//Creates a fadein effect to reverse the fadeout effect
void fadein(){
    for(i = 0; i < 3; i++){
        switch(i){
            case 0:
            BGP_REG = 0xFE;
            break;
            case 1:
            BGP_REG = 0xF9;
            break;
            case 2:
            BGP_REG = 0xE4;
            break;
        }
        performancedelay(2);
    }
}

//Allows to move the sprites with only one line
void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteids[0], x, y);
    move_sprite(character->spriteids[1], x + spritesize, y);
    move_sprite(character->spriteids[2], x, y + spritesize);
    move_sprite(character->spriteids[3], x + spritesize, y + spritesize);
}

//Setting up sprites with their x and y cords
void setupdino(){
    dino.x = 16;
    dino.y = 105;
    dino.width = 16;
    dino.height = 16;

    set_sprite_tile(0, 0);
    dino.spriteids[0] = 0;
    set_sprite_tile(1, 1);
    dino.spriteids[1] = 1;
    set_sprite_tile(2, 2);
    dino.spriteids[2] = 2;
    set_sprite_tile(3, 3);
    dino.spriteids[3] = 3;

    movegamecharacter(&dino, dino.x, dino.y); 
}

void setupdino1(){
    dino1.x = 16;
    dino1.y = 105;
    dino1.width = 16;
    dino1.height = 16;

    set_sprite_tile(4, 4);
    dino1.spriteids[0] = 4;
    set_sprite_tile(5, 5);
    dino1.spriteids[1] = 5;
    set_sprite_tile(6, 6);
    dino1.spriteids[2] = 6;
    set_sprite_tile(7, 7);
    dino1.spriteids[3] = 7;

    movegamecharacter(&dino1, dino1.x, dino1.y); 
}

void setupcatcus(){
    catcus.x = 120;
    catcus.y = 106;
    catcus.width = 10;
    catcus.height = 10;

    set_sprite_tile(8, 8);
    catcus.spriteids[0] = 8;
    set_sprite_tile(9, 9);
    catcus.spriteids[1] = 9;
    set_sprite_tile(10, 10);
    catcus.spriteids[2] = 10;
    set_sprite_tile(11, 11);
    catcus.spriteids[3] = 11;

    movegamecharacter(&catcus, catcus.x, catcus.y);
}

void setupbird(){
    bird.x = 80;
    bird.y = 80;
    bird.width = 10;
    bird.height = 10;

    set_sprite_tile(12, 12);
    bird.spriteids[0] = 12;
    set_sprite_tile(13, 13);
    bird.spriteids[1] = 13;
    set_sprite_tile(14, 14);
    bird.spriteids[2] = 14;
    set_sprite_tile(15, 15);
    bird.spriteids[3] = 15;

    movegamecharacter(&bird, bird.x, bird.y);
}

//Jumping Methods
//Checks if the sprite will touch the floor
INT8 wouldhitsurface(UINT8 projectedYPosition){
    if(projectedYPosition >= floorYposition){
        return floorYposition;
    }
    return -1;
}

void jump(){
    INT8 possiblesurfaceY;

    //Checks if the sprite is jumping
    if(jumping==0){
        jumping = 1;
        currentspeedY = 10;
    }

    //Starts the deceleration process
    currentspeedY = currentspeedY + gravity;
    dino.y -= currentspeedY;
    possiblesurfaceY = wouldhitsurface(dino.y);

    if(possiblesurfaceY > -1){
        jumping = 0;
        dino.y = possiblesurfaceY;
        movegamecharacter(&dino, dino.x, dino.y);
    }else{
        movegamecharacter(&dino, dino.x, dino.y);
    }
    movegamecharacter(&dino, dino.x, dino.y);

    //Sound
    NR10_REG = 0x50;
    NR11_REG = 0x80;
    NR12_REG = 0x43;
    NR13_REG = 0x77;
    NR14_REG = 0x86;

}

void gameover(){
    //Music
    NR10_REG = 0x7D; //or 1E or 1D for louder sound / 2E / 3E / 4E... for more "vibe"
    NR11_REG = 0xBF;
    NR12_REG = 0xF6; //B7, C7, D7...F7 for longer sound
    NR13_REG = 0x7C;
    NR14_REG = 0x86;
}

//Main Method
void main(){
    UINT8 currentspriteindex = 0;
    
    DISPLAY_ON;
    
    //Sound
    //Theses registers turn on sound; they have to be in a specfic order
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
    
    //SplashScreen
    set_bkg_data(0, 166, SplashScreen_data);
    set_bkg_tiles(0, 0, 20, 18, SplashScreen_map);

    SHOW_BKG;

    //Waits until the start button is pressed
    waitpad(J_START);
    fadeout();
    fadein();

    //True Background
    set_bkg_data(0, 15, BackgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, Background);
    
    SHOW_BKG;
    
    //Sprites
    set_sprite_data(0, 16, GameSprites);
    setupdino();
    //setupdino1();
    setupcatcus();
    setupbird();
    
    SHOW_SPRITES;

    //BYTE data
    jumping = 0; 

    while(!checksollisions(&dino, &catcus, &bird)){
        scroll_bkg(4, 0);

        //Flips the feet to make it look like its running
        if(currentspriteindex == 0){
            currentspriteindex = 1;
            set_sprite_tile(2,6);
            set_sprite_tile(3,7);
        }else if(currentspriteindex == 1){
            currentspriteindex = 0;
            set_sprite_tile(2,2);
            set_sprite_tile(3,3);
        }
        

        catcus.x -= 5;
        movegamecharacter(&catcus, catcus.x, catcus.y);

        bird.x -= 12;
        movegamecharacter(&bird, bird.x, bird.y);

        if((joypad() & J_UP) || jumping == 1){
            jump();
        }

        performancedelay(2);
    }
    //Plays the gameover music
    fadeout();
    fadein();
    gameover();    
}

/* TODO:
    Reset the game
*/