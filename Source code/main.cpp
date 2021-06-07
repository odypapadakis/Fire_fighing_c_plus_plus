#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "area.h"
#include <windows.h>
#include <string>
#include "actions.h"
#include <conio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "graphics.h"
#include "timer.h"

using namespace::std;

const int n=20;


void SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask);

int main( int argc, char* args[] )
{


SDL_Event event; 
 
   timer clock;



   SDL_Surface* pics[36];   
   SDL_Surface* buttons[20];     
   SDL_Surface* background = NULL; 
   SDL_Surface* screen = NULL;   
   SDL_Surface *message = NULL;
  
   SDL_Color textColor = { 0, 0, 0 };  
   SDL_Color bgcolor={0xff,0xff,0xff}; 
   SDL_Color bgcolor2={0xff,0xff,0xa}; 
   SDL_Init( SDL_INIT_EVERYTHING ); 
   
   
   
   TTF_Init();
   
   SDL_WM_SetCaption("Fire Simulator", NULL );
   
   TTF_Font *font = NULL;
   font = TTF_OpenFont("data/LCD.ttf", 20);
   
   
   screen = SDL_SetVideoMode(1160, 735, 32, SDL_SWSURFACE ); // Set window size
   SDL_FreeSurface(message);
   
   

   bool quit = false;  //boolean variable used to decide termination or not  of the program 
   bool pausesim = false; // pause variable
   
   
   
    // Buttons and pictures initialisation
   buttons[0]= load_image("data/buttons/BACK_BUTTON.bmp");
   buttons[1]= load_image("data/buttons/VEHICLE_BUTTON.bmp");
   buttons[2]= load_image("data/buttons/FIRE_BUTTON.bmp");
   buttons[3]= load_image("data/buttons/INFO_BUTTON.bmp");
   buttons[4]= load_image("data/buttons/SMALL_BUTTON.bmp");
   buttons[5]= load_image("data/buttons/MEDIUM_BUTTON.bmp");
   buttons[6]= load_image("data/buttons/LARGE_BUTTON.bmp");
   buttons[7]= load_image("data/buttons/AIR_BUTTON.bmp");
   buttons[8]= load_image("data/buttons/HELL_BUTTON.bmp");
   buttons[9]= load_image("data/buttons/pause.bmp");
   buttons[10]= load_image("data/buttons/play.bmp");
   buttons[11]= load_image("data/buttons/BACK_BUTTON_P.bmp");
   buttons[12]= load_image("data/buttons/VEHICLE_BUTTON_P.bmp");
   buttons[13]= load_image("data/buttons/FIRE_BUTTON_P.bmp");
   buttons[14]= load_image("data/buttons/INFO_BUTTON_P.bmp");
   buttons[15]= load_image("data/buttons/SMALL_BUTTON_P.bmp");
   buttons[16]= load_image("data/buttons/MEDIUM_BUTTON_P.bmp");
   buttons[17]= load_image("data/buttons/LARGE_BUTTON_P.bmp");
   buttons[18]= load_image("data/buttons/AIR_BUTTON_P.bmp");
   buttons[19]= load_image("data/buttons/HELL_BUTTON_P.bmp");
   pics[0]= load_image("data/models/g_small(1).bmp");
   pics[1]= load_image("data/models/g_small(2).bmp");
   pics[2]= load_image("data/models/g_small(3).bmp");
   pics[3]= load_image("data/models/g_medium(1).bmp");
   pics[4]= load_image("data/models/g_medium(2).bmp");
   pics[5]= load_image("data/models/g_medium(3).bmp");
   pics[6]= load_image("data/models/g_large(1).bmp");
   pics[7]= load_image("data/models/g_large(2).bmp");
   pics[8]= load_image("data/models/g_large(3).bmp");
   pics[9]= load_image("data/models/airplane(1).bmp");
   pics[10]= load_image("data/models/airplane(2).bmp");
   pics[11]= load_image("data/models/airplane(3).bmp");
   pics[12]= load_image("data/models/helicopter(1).bmp");
   pics[13]= load_image("data/models/helicopter(2).bmp");
   pics[14]= load_image("data/models/helicopter(3).bmp");
   pics[15]= load_image("data/fire/level1.bmp"); //---------------  1
   pics[16]= load_image("data/fire/level2.bmp");  //                2
   pics[17]= load_image("data/fire/level3.bmp");   //               3
   pics[18]= load_image("data/fire/level8.bmp");  //                8
   pics[19]= load_image("data/fire/level9.bmp");//------------------9
   pics[20] = load_image("data/base/1.bmp");
   pics[21] = load_image("data/base/2.bmp");
   pics[22] = load_image("data/base/3.bmp");
   pics[23] = load_image("data/base/4.bmp");
   pics[24] = load_image("data/area.bmp");
   pics[25] = load_image("data/screen.bmp"); 
   pics[26] = load_image("data/screen2.bmp"); 
   pics[27] = load_image("data/models/small_tanker.bmp");
   pics[28] = load_image("data/models/medium_tanker.bmp");
   pics[29] = load_image("data/models/large_tanker.bmp");
   pics[30] = load_image("data/models/air.bmp");
   pics[31] = load_image("data/models/helicopter.bmp");
   pics[32]= load_image("data/fire/level5.bmp");   //           4
   pics[33]= load_image("data/fire/level5.bmp");   //           5 
   pics[34]= load_image("data/fire/level6.bmp");    //          6 
   pics[35]= load_image("data/fire/level7.bmp");    //          7
   background = load_image("data/background.bmp");
   
   apply_surface(0,0,background,screen);
   apply_surface(0,0,message,screen);
   apply_surface(481,3,buttons[0],screen);
   apply_surface(531,3,buttons[1],screen);
   apply_surface(581,3,buttons[2],screen);
   apply_surface(631,3,buttons[3],screen); 
   apply_surface(731,198,buttons[4],screen);
   apply_surface(912,198,buttons[5],screen);
   apply_surface(1081,198,buttons[6],screen);
   apply_surface(731,311,buttons[7],screen);
   apply_surface(912,311,buttons[8],screen); 
   SDL_WM_SetIcon(SDL_LoadBMP("data/favicon.bmp"), NULL);   // FAVICON
      




   srand(time(0));
 area *a[26][25];  //  map creation
 a[23][0]=( area *) new Base();  // base placement 
 a[23][1]=( area *) new Base();  
 a[24][0]=( area *) new Base();
 a[24][1]=( area *) new Base();    
 
 

 
//  Placing random items on the map.
 for (int i = 0; i < 23; i++)
  {
   for (int j = 0; j < 25; j++) 
    {
       int ch=rand()%301;
       if(ch<=292)
            a[ i ][ j ] = ( area *) new point();
       else if(ch<295) 
            a[ i ][ j ] = ( area *) new g_small();
       else if(ch<297)
            a[ i ][ j ] = ( area *) new g_medium();
       else if(ch<299)
            a[ i ][ j ] = ( area *) new g_large();  
       else if(ch==299)
            a[ i ][ j ] = ( area *) new airplane();  
       else if(ch==300)
            a[ i ][ j ] = ( area *) new helicopter();  
		
			
      }       
    } 
  // Placing random items on the map step2 
  for (int i = 23; i < 25; i++)
   {
   for (int j = 2; j < 25; j++) 
    {
       int ch=rand()%201;
       if(ch<=193)
            a[ i ][ j ] = ( area *) new point();
       else if(ch<195) 
            a[ i ][ j ] = ( area *) new g_small();
       else if(ch<197)
            a[ i ][ j ] = ( area *) new g_medium();
       else if(ch<199)
            a[ i ][ j ] = ( area *) new g_large();     
	   else if(ch==199)
            a[ i ][ j ] = ( area *) new airplane();
       else if(ch==200)
            a[ i ][ j ] = ( area *) new helicopter(); 
		
			
      }       
    } 
    
	// Placing point items on the map ( step3)
	for(int j=0;j<25;j++)
     a[ 25 ][ j ] = ( area *) new point();
 

 //gameplay//
      
 
 //let's play  
 
  

int cs=0; 
int pressed=0;
int nx,ny;
int type,key=0;

while( quit == false )
{
               

//show 
if(cs==0)
{
         message = TTF_RenderText_Solid( font,"Simulating ",bgcolor);
         cs++;
}         
else if (cs==1)
{
         message = TTF_RenderText_Solid( font,"Simulating. ",bgcolor);
         cs++;
}
else if (cs==2)
{
         message = TTF_RenderText_Solid( font,"Simulating.. ",bgcolor);
         cs++;
}
else 
{
         message = TTF_RenderText_Solid( font,"Simulating... ",bgcolor);
         cs=0;
}


apply_surface( 209,4, pics[26], screen );


if(pressed==0)
  {
                apply_surface( 735, 405-n, pics[25], screen );
                apply_surface( 870, 535-n, message, screen );
  }               
char buffer [5];
message = TTF_RenderText_Solid( font,"YEAR ",bgcolor);
apply_surface( 248,37-n, message, screen ); 
itoa (clock.get_year(),buffer,10);
message = TTF_RenderText_Solid( font, buffer,bgcolor);
apply_surface( 298,37-n, message, screen ); 
message = TTF_RenderText_Solid( font,"WEEK ",bgcolor);
apply_surface( 328,37-n, message, screen ); 
itoa (clock.get_week(),buffer,10);
message = TTF_RenderText_Solid( font, buffer,bgcolor);
apply_surface( 378,37-n, message, screen ); //735,405


int x,y; //mouse 



	
 
      
	//new fire random
	if(rand()%5==0)
		new_fire(a);          
  
	// fires controls
    if(clock.get_week()%4==0)     
	{
     expand_fires(a);
	 increase_levels(a);
    } 
	if(clock.get_week()==0 || clock.get_week()==25 || clock.get_week()==50) 
	 repair_burned(a);
	//extignuish
	for(int i=0;i<25;i++)
		for(int j=0;j<25;j++)
			{
             vehicle *temp5= dynamic_cast < vehicle *>(a[i][j]);
             if((temp5!=0) && ((temp5->get_status()==PATROL) || (temp5->get_status()==ONDUTY)))
              temp5->ext(a,i,j);       
			}
// vehicles controls     
move(a);
fuel_consume(a);
vehicle_check(a,clock);
repair_brokendown(a);             
return_to_base(a);  
show(pics,a,screen);

if(burned_it_all(a))
  {
    message = TTF_RenderText_Solid( font,"YOU LOST,FIRE IS ALMOST EVERYWHERE",bgcolor);
    apply_surface( 735, 405-n, pics[25], screen );
    apply_surface( 750, 535-n, message, screen );
	message = TTF_RenderText_Solid( font,"PRESS SPACE TO QUIT",bgcolor);
	apply_surface( 750, 550-n, message, screen );
	
    SDL_Flip(screen);
    SDL_Delay(4000);
    quit=true;
	pausesim=true;

  }
  
  
clock ++; /// changed 
  
  
  Uint8 SDL_GetMouseState(int* x,int* y);


 //TIME DELAY
int delayer=0;
 
 
for(delayer=0;delayer<=850;delayer++)
{
 int enable=0;
if ( SDL_PollEvent( &event ) ) //checking for an event
        {
            //Close the program by pressing the X
            if( event.type == SDL_QUIT        )
            { 
                quit = true;
            }
            
			//Close the program by pressing the ESCAPE key 
            if( event.type == SDL_KEYDOWN ) 
            {
            if      (event.key.keysym.sym == SDLK_ESCAPE) 
            quit = true;
            
			//Pause the program by pressing space
            if(event.key.keysym.sym == SDLK_SPACE)
                 {
                                 pausesim = true;
                                 apply_surface( 735, 405-n, pics[25], screen );
                                 SDL_Flip(screen);
                                 
								 
                   
                 }
            }  
            
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
              //If the left mouse button was pressed
              if( event.button.button == SDL_BUTTON_LEFT )
              {
                  
              //Get the mouse offsets
               x = event.button.x;
               y = event.button.y;

                //If the mouse is over the button
                
                if( ( x >=481 ) && ( x <481+60) && ( y >=3) && ( y <53) ) // BACKUP BUTTON
                {
            	 apply_surface(481,3,buttons[11],screen);
            	 SDL_Flip(screen);
            	 call_backup(a);
            	 show(pics,a,screen);
            	 apply_surface(481,3,buttons[0],screen);
                }
                if( ( x >=631 ) && ( x <631+50) && ( y >=3) && ( y <53) ) // HELP BUTTON
                {
                 apply_surface( 735, 405-n, pics[25], screen );
            	 apply_surface(631,3,buttons[14],screen);
            	 SDL_Flip(screen);
                 message = TTF_RenderText_Solid( font, "PRESS THE FIRST BUTTON TO CALL BACK UP",bgcolor);
	             apply_surface( 735, 410-n, message, screen );
                 message = TTF_RenderText_Solid( font, "PRESS THE SECOND BUTTON TO INSERT VEHICLE",bgcolor);
	             apply_surface( 735, 440-n, message, screen ); 
                 message = TTF_RenderText_Solid( font, "PRESS THE THIRD BUTTON TO INSERT NEW FIRE",bgcolor);
	             apply_surface( 735, 470-n, message, screen ); 
	             message = TTF_RenderText_Solid( font, "PRESS ANY VEHICLE'S BUTTON FOR ITS INFO",bgcolor);
	             apply_surface( 735, 500-n, message, screen ); 
	             message = TTF_RenderText_Solid( font, "PRESS <SPACE> TO PAUSE THE SIMULATION",bgcolor);
	             apply_surface( 735, 530-n, message, screen ); 
	             message = TTF_RenderText_Solid( font, "PRESS <ESCAPE> TO EXIT",bgcolor);
	             apply_surface( 735, 560-n, message, screen ); 	             
	             message = TTF_RenderText_Solid( font, "PRESS <SPACE> TO EXIT THE HELP",bgcolor);
	             apply_surface( 735, 620-n, message, screen );   
                              
                 pausesim = true;
                }
                if( ( x >=731 ) && ( x <731+26) && ( y >=218-n) && ( y <218+26-n) ) // G_SMALL CLASS BUTTON
                {
                 pressed++;
                 if(pressed==1)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
            	  apply_surface(731, 218-n,buttons[15],screen);
                  message = TTF_RenderText_Solid( font, "SMALL TANKER",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 80 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 220 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 5000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 4 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	             
	              message = TTF_RenderText_Solid( font, "WATER CONSUMATION: 100 LITRES/MIN",bgcolor);
	              apply_surface( 735, 560-n, message, screen );   
	              apply_surface(842,620-n,pics[27],screen);
	              SDL_Flip(screen);
                 }
                 else
                 {
                     apply_surface(731,218-n,buttons[4],screen);
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
               } 
                 if( ( x >=912 ) && ( x <912+26) && ( y >=218-n) && ( y <218+26-n) )  // G_MEDIUM BUTTON
                {
                 pressed++;
                 if(pressed==1)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
            	  apply_surface(912, 218-n,buttons[16],screen);
                  message = TTF_RenderText_Solid( font, "MEDIUM TANKER",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 80 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 220 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 5000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 4 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	             
	              message = TTF_RenderText_Solid( font, "WATER CONSUMATION: 100 LITRES/MIN",bgcolor);
	              apply_surface( 735, 560-n, message, screen );   
	              apply_surface(842,620-n,pics[28],screen);
	              SDL_Flip(screen);
                 }
                 else
                 {
                     apply_surface(912,218-n,buttons[5],screen);
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
                
               } 
                if( ( x >=1081) && ( x <1081+26) && ( y >=218-n) && ( y <218+26-n) )  // G_LARGE BUTTON
                {
                 pressed++;
                 if(pressed==1)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
            	  apply_surface(1081, 218-n,buttons[17],screen);
                  message = TTF_RenderText_Solid( font, "LARGE TANKER",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 70 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 260 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 6000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 5 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	             
	              message = TTF_RenderText_Solid( font, "WATER CONSUMATION: 100 LITRES/MIN",bgcolor);
	              apply_surface( 735, 560-n, message, screen );   
	              apply_surface(842,620-n,pics[29],screen);
	              SDL_Flip(screen);
                 }
                 else
                 {
                     apply_surface(1081,218-n,buttons[6],screen);
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
                
               }
               if( ( x >=731) && ( x <731+26) && ( y >=331-n) && ( y <331+26-n) ) // AIRPLANE BUTTON
                {
                 pressed++;
                 if(pressed==1)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
            	  apply_surface(731, 331-n,buttons[18],screen);
                  message = TTF_RenderText_Solid( font, "CANADAIR",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 200 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 1000 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 6000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 20 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	               
	              apply_surface(842,620-n,pics[30],screen);
	              SDL_Flip(screen);
                 }
                 else
                 {
                     apply_surface(731, 331-n,buttons[7],screen);
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
                
               }  
               if( ( x >=912) && ( x <912+26) && ( y >=331-n) && ( y <331+26-n) ) // HELICOPTER BUTTON
                {
                 pressed++;
                 if(pressed==1)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
            	  apply_surface(912, 331-n,buttons[19],screen);
                  message = TTF_RenderText_Solid( font, "ERICCSON AIR-CRANE",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 180 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 800 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 4500 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 16 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	               
	              apply_surface(842,620-n,pics[31],screen);
	              SDL_Flip(screen);
                 }
                 else
                 {
                     apply_surface(912, 331-n,buttons[8],screen);
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
                
               }
              
        }  // if button = left click closes
  } // if event = mousebutton down closes
} // SDL if  EVENT SEARCH CLOSES

		
  // In Pause state 
 while( pausesim == true)
 {

 
   if( SDL_PollEvent( &event ) )   
{   


           if( event.type == SDL_QUIT        )
            { 
                quit = true;
				pausesim = false;
            }
   
           if( event.type == SDL_KEYDOWN ) 
            {
               if(event.key.keysym.sym == SDLK_ESCAPE) 
				{
				quit = true;  
				pausesim=false; 
				}
            }
      
             if( event.type == SDL_KEYDOWN )
               {
                 if(event.key.keysym.sym == SDLK_SPACE)
                  {
                    pausesim = false;
                    apply_surface(631,3,buttons[3],screen);  
				  }			
               }  
 if( event.type == SDL_MOUSEBUTTONDOWN )
            {
              //If the left mouse button was pressed
              if( event.button.button == SDL_BUTTON_LEFT )
              {
                
              //Get the mouse offsets
               x = event.button.x;
               y = event.button.y;
               
               
                   
                  
                   if(enable==1)
                   if( ( x >=26 ) && ( x <731+26) && ( y >=80) && ( y <718+26) )
                   {                             
                    nx=(x-26)/26;
                    ny=(y-80)/26;
                    new_fire(ny,nx,a);
                    show(pics,a,screen);
                    apply_surface(581,3,buttons[2],screen);
                    SDL_Flip(screen);
                    enable=4;
                   }
                 
                   
                   if( ( x >=581 ) && ( x <581+50) && ( y >=3) && ( y <3+50) )
                   { 
                     apply_surface(581,3,buttons[13],screen); 
                      enable=1;
                      
                   }
                   
                    
                   if(enable==3)
                   if( ( x >=26 ) && ( x <731+26) && ( y >=80) && ( y <718+26) )
                   {               
                    nx=(x-26)/26;
                    ny=(y-80)/26;
                    new_vehicle(type,ny,nx,a);
                    show(pics,a,screen);
                    apply_surface(531,3,buttons[1],screen);
                    SDL_Flip(screen);
                    enable=4;
                   } 
                   
                   if(enable==2)
                   {
                                if( ( x >=731 ) && ( x <731+26) && ( y >=218-n) && ( y <218+26-n) )
                                {
                                  type=0; 
                                  enable=3; 
                                }
                                if( ( x >=912 ) && ( x <912+26) && ( y >=218-n) && ( y <218+26-n) )
                                {
                                  type=1; 
                                  enable=3; 
                                }
                                if( ( x >=1081) && ( x <1081+26) && ( y >=218-n) && ( y <218+26-n) )
                                {
                                  type=2; 
                                  enable=3; 
                                }
                                if( ( x >=731) && ( x <731+26) && ( y >=331-n) && ( y <331+26-n) )
                                {
                                  type=3; 
                                  enable=3; 
                                }
                                if( ( x >=912) && ( x <912+26) && ( y >=331-n) && ( y <331+26-n) )
                                {
                                  type=4; 
                                  enable=3; 
                                }
                   }                 
                  
                   if( ( x >=531 ) && ( x <531+50) && ( y >=3) && ( y <3+50) )
                   { 
                     apply_surface(531,3,buttons[12],screen); 
                      enable=2;
                      
                   }     
 
                   if( ( x >=731 ) && ( x <731+26) && ( y >=218-n) && ( y <218+26-n) )
                   {
                        pressed++;
                 if(pressed==1 && enable==0)   
                 {
                  
                  apply_surface(735,405-n , pics[25], screen );
                  message = TTF_RenderText_Solid( font, "SMALL TANKER",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 80 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 220 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 5000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 4 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	             
	              message = TTF_RenderText_Solid( font, "WATER CONSUMATION: 100 LITRES/MIN",bgcolor);
	              apply_surface( 735, 560-n, message, screen );   
	              apply_surface(842,620-n,pics[27],screen);
	              SDL_Flip(screen);
	              } 
	               else if(pressed!=0)
                 {
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
                
               } 
               
                if( (enable==0) && ( x >=26 ) && ( x <731+26) && ( y >=80) && ( y <718+26) )
                   {               
                    nx=(x-26)/26;
                    ny=(y-80)/26;
                    char buffer[50];
                    for(int i=0;i<50;i++) buffer[i]=0;          
                    vehicle *temp5= dynamic_cast < vehicle *>(a[ny][nx]);
                    if(temp5!=0)
                    {
                      apply_surface(735,405-n , pics[25], screen );
                      message = TTF_RenderText_Solid( font,"TYPE: ",bgcolor);  
                      apply_surface( 735, 410-n, message, screen );        
                      memcpy(buffer,temp5->get_name().c_str(),temp5->get_name().size()); 
                      message = TTF_RenderText_Solid( font, buffer,bgcolor);
                      apply_surface( 805, 410-n, message, screen );              
                      message = TTF_RenderText_Solid( font, "AGE: ",bgcolor);
	                  apply_surface( 735, 450-n, message, screen ); 
	                  itoa (temp5->get_age(),buffer,10);
                      message = TTF_RenderText_Solid( font,buffer,bgcolor);
                      apply_surface( 805, 450-n, message, screen ); 
                      message = TTF_RenderText_Solid( font, "FUEL: ",bgcolor);
	                  apply_surface( 735, 480-n, message, screen ); 
	                  itoa (temp5->get_fuel(),buffer,10);
                      message = TTF_RenderText_Solid( font,buffer ,bgcolor);
	                  apply_surface( 805, 480-n, message, screen ); 
                      message = TTF_RenderText_Solid( font, "WATER: ",bgcolor);
	                  apply_surface( 735, 510-n, message, screen ); 
	                  itoa (temp5->get_water(),buffer,10);
                      message = TTF_RenderText_Solid( font,buffer ,bgcolor);
	                  apply_surface( 805, 510-n, message, screen ); 	             
	                  message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: ",bgcolor);
	                  apply_surface( 735, 540-n, message, screen );  
                      itoa (temp5->get_fuel_cons(),buffer,10);
                      message = TTF_RenderText_Solid( font,buffer ,bgcolor);
	                  apply_surface( 915, 540-n, message, screen );  
                      message = TTF_RenderText_Solid( font, "WATER CONSUMATION: ",bgcolor);
	                  apply_surface( 735, 570-n, message, screen );
                      itoa (temp5->get_water_cons(),buffer,10);
                      message = TTF_RenderText_Solid( font,buffer ,bgcolor);
	                  apply_surface( 915, 570-n, message, screen ); 
	                  message = TTF_RenderText_Solid( font, "STATUS: ",bgcolor);
	                  apply_surface( 735, 610-n, message, screen );
	                  int t=temp5->get_status();
	                  if(t==0)
	                   message = TTF_RenderText_Solid( font, "ON DUTY",bgcolor);
	                  else if(t==1)
	                   message = TTF_RenderText_Solid( font, "PATROL",bgcolor);
	                  else if(t==2) 
                       message = TTF_RenderText_Solid( font, "BROKENDOWN",bgcolor);
                      else
                       message = TTF_RenderText_Solid( font, "BURNED",bgcolor); 
                      apply_surface( 805, 610-n, message, screen );  
                       
                       }
                           
                    

               }
                    
                    
                    
                    
                    
                 if( ( x >=912 ) && ( x <912+26) && ( y >=218-n) && ( y <218+26-n) )
                {
                 pressed++;
                 if(pressed==1 && enable==0)   
                 {
                   apply_surface(735,405-n , pics[25], screen );
                  message = TTF_RenderText_Solid( font, "MEDIUM TANKER",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 80 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 220 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 5000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 4 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	             
	              message = TTF_RenderText_Solid( font, "WATER CONSUMATION: 100 LITRES/MIN",bgcolor);
	              apply_surface( 735, 560-n, message, screen );    
	              apply_surface(842,620-n,pics[28],screen);
	              SDL_Flip(screen);
	              } 
	               else if(pressed!=0)
                 {
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  

               } 
                if( ( x >=1081) && ( x <1081+26) && ( y >=218-n) && ( y <218+26-n) )
                {
                  pressed++;
                 if(pressed==1 && enable==0)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
                  message = TTF_RenderText_Solid( font, "LARGE TANKER",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 70 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 260 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 6000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 5 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	             
	              message = TTF_RenderText_Solid( font, "WATER CONSUMATION: 100 LITRES/MIN",bgcolor);
	              apply_surface( 735, 560-n, message, screen );   
	              apply_surface(842,620-n,pics[29],screen);
	              SDL_Flip(screen);
               }
	               else if(pressed!=0)
                 {
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
        
       
               }
               if( ( x >=731) && ( x <731+26) && ( y >=331-n) && ( y <331+26-n) )
                {
                 pressed++;
                 if(pressed==1 && enable==0)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
                  message = TTF_RenderText_Solid( font, "CANADAIR",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 200 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 1000 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 6000 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 20 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	               
	              apply_surface(842,620-n,pics[30],screen);
	              SDL_Flip(screen);
                } 
	               else if(pressed!=0)
                 {
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
        
               }
               
               if( ( x >=631 ) && ( x <631+50) && ( y >=3) && ( y <53) )
                {
                 if(key==0) 
                 {  
                  apply_surface( 735, 405-n, pics[25], screen );
            	  apply_surface(631,3,buttons[14],screen);
            	  SDL_Flip(screen);
                  message = TTF_RenderText_Solid( font, "PRESS THE FIRST BUTTON TO CALL BACK UP",bgcolor);
	             apply_surface( 735, 410-n, message, screen );
                 message = TTF_RenderText_Solid( font, "PRESS THE SECOND BUTTON TO INSERT VEHICLE",bgcolor);
	             apply_surface( 735, 440-n, message, screen ); 
                 message = TTF_RenderText_Solid( font, "PRESS THE THIRD BUTTON TO INSERT NEW FIRE",bgcolor);
	             apply_surface( 735, 470-n, message, screen ); 
	             message = TTF_RenderText_Solid( font, "PRESS ANY VEHICLE'S BUTTON FOR ITS INFO",bgcolor);
	             apply_surface( 735, 500-n, message, screen ); 
	             message = TTF_RenderText_Solid( font, "PRESS <SPACE> TO PAUSE THE SIMULATION",bgcolor);
	             apply_surface( 735, 530-n, message, screen ); 
	             message = TTF_RenderText_Solid( font, "PRESS <ESCAPE> TO EXIT",bgcolor);
	             apply_surface( 735, 560-n, message, screen ); 	             
	             message = TTF_RenderText_Solid( font, "PRESS <SPACE> TO EXIT THE HELP",bgcolor);
	             apply_surface( 735, 620-n, message, screen );                      
                  key=1;
                 }
                 else
                 {
                     key=0;
                     apply_surface(631,3,buttons[3],screen);
                     apply_surface( 735, 405-n, pics[25], screen );
                 }  
                    
                }
               
               if(enable==4)
               enable=0;
               
               if( ( x >=912) && ( x <912+26) && ( y >=331-n) && ( y <331+26-n) )
                {
                 pressed++;
                 if(pressed==1 && enable==0)   
                 {
                  apply_surface(735,405-n , pics[25], screen );
            	  apply_surface(912, 331-n,buttons[19],screen);
                  message = TTF_RenderText_Solid( font, "ERICCSON AIR-CRANE",bgcolor);
	              apply_surface( 845, 410-n, message, screen );
                  message = TTF_RenderText_Solid( font, "SPEED: 180 KM/H",bgcolor);
	              apply_surface( 735, 440-n, message, screen ); 
                  message = TTF_RenderText_Solid( font, "FUEL CAPACITY: 800 LITRES",bgcolor);
	              apply_surface( 735, 470-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "WATER CAPACITY: 4500 LITRES",bgcolor);
	              apply_surface( 735, 500-n, message, screen ); 
	              message = TTF_RenderText_Solid( font, "FUEL CONSUMATION: 16 LITRES/KM",bgcolor);
	              apply_surface( 735, 530-n, message, screen ); 	               
	              apply_surface(842,620-n,pics[31],screen);
	              SDL_Flip(screen);
                 }
                 else if(pressed!=0)
                 {
                     apply_surface(735,405-n,pics[25],screen);
                     SDL_Flip(screen);
                     pressed=0;
                 }  
                
           
                 }
				 }
				 }			   
} 
        
SDL_Flip(screen);
              
 }   //Pause while Closes                                               


 SDL_Delay(1); // delay (runs as many times as the delayer for does)


 if(quit == true)  // time to exit the simulation
 {
for(int i=0;i<32;i++)
SDL_FreeSurface(pics[i]);

for(int i=0;i<20;i++)
SDL_FreeSurface(buttons[i]);
   
   
 SDL_FreeSurface(background);
 SDL_FreeSurface( message ); 
    TTF_CloseFont( font );
TTF_Quit();
 
 SDL_Quit();
 return 0;   
}







} //Delayer for  Closes


 }  // Big while closes
 
 }  // Main closes




