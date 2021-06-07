#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL/SDL.h"
#include "area.h"
#include <stdio.h>
#include <stdlib.h>
int modelsize = 26;      // size of items on the map is    26x26

//Image loading function
SDL_Surface *load_image( std::string filename ) 
{ 
  SDL_Surface* loadedImage = NULL; 
  SDL_Surface* optimizedImage = NULL;
  loadedImage =SDL_LoadBMP( filename.c_str() );
  if( loadedImage != NULL ) 
  {
   optimizedImage = SDL_DisplayFormat( loadedImage );
   SDL_FreeSurface( loadedImage ); 
}

 return optimizedImage;
} 

//Surface applying function
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) 
{ 
  SDL_Rect offset;
  offset.x = x; 
  offset.y = y;
  SDL_BlitSurface( source, NULL, destination, &offset ); 
}

// Update the map function
void show(SDL_Surface *p[25],area *a[26][25],SDL_Surface* dest) // show
{

         
  int c=0;  // vehicles on map  counter 
  
  for(int x=0;x<25;x++) 
  { 
   for(int y=0;y<25;y++)
   { 
   
   
   // Creating the temporary items
   
   
     point      *t1= dynamic_cast < point *>(a[x][y]);
     Base       *t2= dynamic_cast < Base *>(a[x][y]);
	 
     g_small    *t3= dynamic_cast < g_small *>(a[x][y]);   
	 g_medium   *t4= dynamic_cast < g_medium *>(a[x][y]);
	 g_large    *t5= dynamic_cast < g_large *>(a[x][y]);
	 airplane   *t6= dynamic_cast < airplane *>(a[x][y]);
	 helicopter *t7= dynamic_cast < helicopter *>(a[x][y]);
	 
	 
	 
	 
	 //Check if the item is a POINT  
     
     if(t1!=0) // POINT --------------------------------------------------
     {
      if(a[x][y]->get_fire_level()==0)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[24],dest);
     if(a[x][y]->get_fire_level()==1)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[15],dest);
     if(a[x][y]->get_fire_level()==2)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[16],dest);
     if(a[x][y]->get_fire_level()==3)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[17],dest);
     if(a[x][y]->get_fire_level()==4)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[32],dest);
     if(a[x][y]->get_fire_level()==5)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[33],dest);
     if(a[x][y]->get_fire_level()==6)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[34],dest);
     if(a[x][y]->get_fire_level()==7)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[35],dest);
     if(a[x][y]->get_fire_level()==8)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[18],dest);
     if(a[x][y]->get_fire_level()==9)
       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[19],dest);
     }
     else  //If the item is not point   (scan the rest of the types)
     {  
      

    	if(t2!=0)  // BASE  -----------------------------------------
        {
                if(t2->get_fire_level()!=0)
                {
					if(a[x][y]->get_fire_level()==0)  // ?????  line 79 to apokleiei
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[24],dest);
					if(a[x][y]->get_fire_level()==1)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[15],dest);
					if(a[x][y]->get_fire_level()==2)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[16],dest);
					if(a[x][y]->get_fire_level()==3)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[17],dest);
					if(a[x][y]->get_fire_level()==4)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[32],dest);
					if(a[x][y]->get_fire_level()==5)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[33],dest);
					if(a[x][y]->get_fire_level()==6)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[34],dest);
					if(a[x][y]->get_fire_level()==7)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[35],dest);
					if(a[x][y]->get_fire_level()==8)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[18],dest);
					if(a[x][y]->get_fire_level()==9)
					apply_surface(modelsize+modelsize*y,80+modelsize*x,p[19],dest);
				}
                  else
                  if(x==23)
                    if(y==0)   apply_surface(modelsize+modelsize*y,80+modelsize*x,p[20],dest);
                    else       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[21],dest); 
                  else
                    if(y==0)   apply_surface(modelsize+modelsize*y,80+modelsize*x,p[22],dest);
                    else       apply_surface(modelsize+modelsize*y,80+modelsize*x,p[23],dest);
        }
        else if(t3!=0)  // Ground small -------------------------------------------
        {
		c++;
			if(t3->get_fire_level()!=0) // if vehicle is on fire
				{
				apply_surface(modelsize+modelsize*y,80+modelsize*x,p[2],dest);
				}
            else if(t3->get_status()==PATROL)  // if vehcile is patrolling 
				{
				apply_surface(modelsize+modelsize*y,80+modelsize*x,p[0],dest);
				}   
            else if(t3->get_status()==BROKENDOWN) // if vehicle has broken down
				{
				apply_surface(modelsize+modelsize*y,80+modelsize*x,p[1],dest);
				}     
        }  
		else if(t4!=0)   // Ground medium ------------------------------------------
        {  
        c++;      
            if(t4->get_fire_level()!=0)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[5],dest);
			}
			else if(t4->get_status()==PATROL)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[3],dest);
			}
			else if(t4->get_status()==BROKENDOWN)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[4],dest);
			}     
        } 
		else if(t5!=0)  //  Groung Large ------------------------------------------
        {   
        c++;                
            if(t5->get_fire_level()!=0) 
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[8],dest);
			}	
			else if(t5->get_status()==PATROL)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[6],dest);
            } 
			else if(t5->get_status()==BROKENDOWN)
            {
            apply_surface(modelsize+modelsize*y,80+modelsize*x,p[7],dest);
            } 
        }        
		else if(t6!=0)  //airplane -------------------------------------------------
		{              
        c++;             
			if(t6->get_fire_level()!=0)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[11],dest);
            }        
			else if(t6->get_status()==PATROL)
			{
            apply_surface(modelsize+modelsize*y,80+modelsize*x,p[9],dest);
            }           
			else if(t6->get_status()==BROKENDOWN)
            {
            apply_surface(modelsize+modelsize*y,80+modelsize*x,p[10],dest);
            } 
		}				
        else if (t7!=0)  //Helicopter-------------------------------------------- 
        {                   
        c++;                  
			if(t7->get_fire_level()!=0)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[14],dest);
			}                  
			else if(t7->get_status()==PATROL)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[12],dest);                    
			}                       
			else if(t7->get_status()==BROKENDOWN)
			{
			apply_surface(modelsize+modelsize*y,80+modelsize*x,p[13],dest);
			} 
        }
                 

 }  // If Item is not Point   closes
 
}   //y for closes
}   // x for closes

        SDL_Flip( dest );
}                                
          
#endif
