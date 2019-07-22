#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"

struct GameCharacter dino;

/*
struct GameCharacter dino1;
struct GameCharacter catcus;
struct GameCharacter bird;
*/

UBYTE spritesize = 8;

void performancedelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteids[0], x, y);
    move_sprite(character->spriteids[1], x + spritesize, y);
    move_sprite(character->spriteids[2], x, y + spritesize);
    move_sprite(character->spriteids[3], x + spritesize, y + spritesize);
}

/* Order of sprites
    DINO
    DINO1
    CATUS
    BIRD
 */

void setupdino(){
    dino.x = 16;
    dino.y = 109;
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

/*
void setupdino1(){
    dino1.x = 50;
    dino1.y = 109;
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
*/

/*
void setupcatcus(){
    catcus.x = 120;
    catcus.y = 110;
    catcus.width = 16;
    catcus.height = 16;

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
*/

/*
void setupbird(){
    bird.x = 80;
    bird.y = 80;
    bird.width = 16;
    bird.height = 16;

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
*/

void main(){
    SHOW_SPRITES;
    DISPLAY_ON;

    set_sprite_data(0, 16, GameSprites);

    setupdino();
    //setupdino1();
    //setupcatcus();
    //setupbird();

    if(joypad() & J_LEFT){
        dino.x += 50;
        movegamecharacter(&dino, dino.x, dino.y);

    }
    
    if(joypad() & J_RIGHT){
        dino.x -= 50;
        movegamecharacter(&dino, dino.x, dino.y);
    }
    performancedelay(5);
}