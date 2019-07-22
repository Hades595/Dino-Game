#include <gb/gb.h>
#include <stdio.h>
#include "Background.c"
#include "BackgroundTiles.c"

void performancedelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    } 
}

void main(){
    DISPLAY_ON;

    set_bkg_data(0, 15, BackgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, Background);
    
    SHOW_BKG;

    while(1){
        scroll_bkg(4, 0);
        performancedelay(4);
    }
}