#include "minimap.h"
#include "background.h"
#include "entite.h"
#include "tic.h"

int main()
{
    //SDL init 
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //Police Init 
    TTF_Font *police=NULL;
    SDL_Color Color={255,255,255};
    police=TTF_OpenFont("pol.ttf",50);

    // Init Fenetre 
    SDL_Surface *screen ;
    screen=SDL_SetVideoMode (1000,666,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    // Init personnage  
    Perso personnage ; 
    initPerso(&personnage);
    int start=0,end=0,dt; 
    
    // Init MINIMAP 
    minimap m;
    SDL_Rect camera,backgpos;
    int temps;
    init_map(&m);
    
    //Init Background
    Background B;
    initBackground(&B);

    //Init Entite 
    entite e;
	initialiser_entite (&e,"voiture_test.png") ;

    entite ennemie1;
    initialiser_entite_EnnemieRace(&ennemie1,"testcar(1).png");
    int nbEnnemie = 0 ; 



    SDL_Event event;
    int continuer=1;
    int time = 0 ;

    
    
	
    //SDL_EnableKeyRepeat(100,10);
    
    while(continuer)
    {   //printf("\ny= %f",personnage.distance);
        personnage.keystate = SDL_GetKeyState(NULL);
        start=SDL_GetTicks();
        dt=start-end;
        if(dt>60){
        //AFFICHAGE 
        afficherBack (B,screen);
        afficherminimap(m,screen , B.camera);
        annimerminimap (&m  );
        afficherPerso(personnage,screen);
        afficher_entite(&e ,screen);
        affichertemp(&temps,screen,police);
        
        
        SDL_PollEvent(&event);
        

        switch (event.type) 
        {
            
            case SDL_QUIT:
                continuer = 0;
                break;

           /* case SDL_KEYDOWN:
                if(event.key.keysym.sym==SDLK_RIGHT){
                        MajPerso(&personnage,1);
                        

                    }
                    else if(event.key.keysym.sym==SDLK_LEFT){
                        MajPerso(&personnage,2);
                        
                    }
                    else if(event.key.keysym.sym==SDLK_SPACE){
                        MajPerso(&personnage,3);
                        
                        //Mix_PlayChannel(0,jump,0);
                    }
                     else if(event.key.keysym.sym==SDLK_ESCAPE){
                        continuer = 0;
                     }
                    break;

                case SDL_KEYUP:
                    MajPerso(&personnage,4);
                    break;*/
                }
                MajPerso(&personnage,1);
                PersoRUN(&personnage,&B,&e);
            UpdatePerso(&personnage ) ; 
            end=start;
            if (start > 100000 ) 
            	start = end = 0 ; 
            
            update_entite(&e,&personnage);
            deplacerPerso(&personnage,5); 
            scrollingInt(&B,personnage);
            mvt_entiteInt(&e,&personnage);
            animerBackground(&B,personnage);
            EnnemieRace (&personnage,&ennemie1,&B,&nbEnnemie);

            if (detect_collision(&personnage,&ennemie1) && personnage.jumt ==0 ){
                    int x  = TicToeAll();
                        printf("\nx= %d",x);
                            screen=SDL_SetVideoMode (1000,666,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
                            ennemie1.pos_entite.x = 100 ; 

            }
            
                
            
            //
            //printf("\npos ennemie = %d",ennemie1.pos_entite.x);
        }
        

afficher_entite(&ennemie1 ,screen);
        animePerso(&personnage);

        MAJMinimap(personnage.img.pos1,  &m, B.camera, 20);

        if (collisionparfaite(screen,personnage) != 10)
        {

        }
            //printf("\nhello");
            
        //collision(screen,&personnage);
        
        //animation(&B,screen);
        
        SDL_Flip(screen);
        //printf("\ncontinuer= %d",continuer);
}

printf("\ncontinuer= %d",continuer);
liberer(&m);
libererperso(&personnage);
freeBackground(&B);
SDL_Quit();
TTF_Quit();
    return 0 ; 

}