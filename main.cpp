#include <stdio.h>
#include <zlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void charlie(SDL_Surface* screen, SDL_Window* window);
void menuPersonaje(SDL_Surface* screen,SDL_Window* window);

int main ( int argc, char** argv ){
    SDL_Window* window=NULL;//Ventana
    SDL_Surface* screen=NULL;//Pantalla

    if(SDL_Init(SDL_INIT_VIDEO)>-1){//Iniciando soporte de video
        window=SDL_CreateWindow("MS",SDL_WINDOWPOS_CENTERED
        ,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);//Creando ventana
        if(window){//Manejo de error
            screen=SDL_GetWindowSurface(window);//Creando pantalla

            //menuPersonaje(screen,window);//Seleccion de personaje
            charlie(screen,window);

        }else{
            printf("Error SDL_CreateWindow %s",SDL_GetError());
        }
    }else{
        printf("Error SDL_Init %s",SDL_GetError());
    }
    SDL_DestroyWindow(window);//Cerrando ventana
    IMG_Quit();
    SDL_Quit();//Cerrando SDL
    return 0;
}//main()

void charlie(SDL_Surface* screen, SDL_Window* window){
    SDL_Surface* image;
    SDL_Surface* background;
    //SDL_Event tecla;
    int flag=IMG_INIT_PNG;//Iniciando soporte PNG
    IMG_Init(flag);//Iniciando soporte IMG

    if((IMG_Init(flag)&flag)){//Manejo de error
        image=IMG_Load("charlie.png");//Cargando sprite jugador
        background=IMG_Load("fondo.png");//Cargando fondo
        int h=500;//Altura de jugador
        int x=10;
        int iL=0,iB=0;

        SDL_Rect body[2],lion[4];//Recortes
        SDL_Rect coorLion,coorBody;//Coordenadas

        body[0].x=515; body[0].y=180;//Charlie montado--------------------------
        body[0].w=54; body[0].h=85;

        body[1].x=567; body[1].y=180;//Salto montado
        body[1].w=58; body[1].h=85;

        coorBody.x=x+27; coorBody.y=h-65;//-------------------------------------

        lion[0].x=745; lion[0].y=260;//Leon parado------------------------------
        lion[0].w=100; lion[0].h=70;

        lion[1].x=515; lion[1].y=260;//Leon corriendo/saltando
        lion[1].w=115; lion[1].h=70;

        lion[2].x=630; lion[2].y=260;//Leon corriendo 1
        lion[2].w=100; lion[2].h=70;

        lion[3].x=850; lion[3].y=260;//Leon quemado
        lion[3].w=100; lion[3].h=70;

        coorLion.x=x; coorLion.y=h;//-------------------------------------------

        if(image) {//Manejo de error
            while(true){
                SDL_BlitSurface(background,NULL,screen,NULL);//Mostrando fondo
                SDL_BlitSurface(image,&lion[iL],screen,&coorLion);//Mostrando leon
                SDL_BlitSurface(image,&body[iB],screen,&coorBody);//Mostrando charlie
                SDL_UpdateWindowSurface(window);//Refrescando pantalla
                SDL_Delay(300);
                iL++;
                iB++;
                coorLion.x+=20;
                coorBody.x+=20;
                if(iL==3)
                    iL=1;
                if(iB==2)
                    iB=0;
            }
        }else{printf("IMG_Load: %s\n", IMG_GetError());}
    }else{
        printf("Error IMG_Init %s",IMG_GetError());
    }
}
