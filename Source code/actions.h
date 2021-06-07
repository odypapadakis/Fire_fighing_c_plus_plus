#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "area.h"
#include "timer.h"


using namespace::std;


void new_fire(area *a[26][25])
{
    int i=rand()%25;
    int j=rand()%25;
    a[i][j]->set_fire_level(1); 
    vehicle *tmp= dynamic_cast < vehicle *>(a[i][j]);
    if(tmp!=0)
    tmp->set_status(FIRED);
}

void new_fire(int i,int j, area *a[26][25])
{
   if(a[i][j]->get_fire_level()==0)  
   a[i][j]->set_fire_level(1); 
   vehicle *tmp= dynamic_cast < vehicle *>(a[i][j]);
   if(tmp!=0)
     tmp->set_status(FIRED);
}    

void expand_fires(area *a[26][25])
{
     int dx=rand()%3-1;
     int dy=rand()%3-1;
     for(int i=0;i<25;i++)
      for(int j=0;j<25;j++)
      {
       if(a[i][j]->get_fire_level()>2)
       {
         while(i+dx<0 || i+dx>24) dx=rand()%3-1;
         while(j+dy<0 || j+dy>24) dy=rand()%3-1;
         point *tmp1= dynamic_cast < point *>(a[i+dx][j+dy]);
         if(tmp1!=0)
         {
                    if(!((dx==dy) && (dx==0)) &&  (a[i+dx][j+dy]->get_fire_level()==0))
                    {
                                            a[i+dx][j+dy]->set_fire_level(1);
                    }                      
         }  
         else if((rand()%5==1))
         {
               a[i+dx][j+dy]->set_fire_level(1);
               vehicle *temp2= dynamic_cast < vehicle *>(a[i+dx][j+dy]);
               if(temp2!=0)
               temp2->set_status(FIRED);
         }                                                               
      } 
      dx=rand()%3-1;     
      dy=rand()%3-1;
     }   
}


void increase_levels(area *a[26][25])
{
             for(int i=0;i<25;i++)
              for(int j=0;j<25;j++)
                if(a[i][j]->get_fire_level()>0 && a[i][j]->get_fire_level()<10)
                  a[i][j]->increase_level();
                   
}


void repair_burned(area *a[26][25])
{
      for(int i=0;i<25;i++)
             for(int j=0;j<25;j++)
             {
                  if(a[i][j]->get_fire_level()==10)
                  {
                     a[i][j]->set_fire_level(0);
                  }  
             }
}


//let's see it
bool burned_it_all(area *a[26][25])
{
      int burned_counter=0;
      for(int i=0;i<25;i++)
              for(int j=0;j<25;j++)
                if(a[i][j]->get_fire_level()>0)
                  burned_counter++;
      if(burned_counter>=450)
       return true;
      else
       return false;             
}

void move(area *a[26][25])
{
     for(int i=0;i<25;i++)
             for(int j=0;j<25;j++)
             {
               ground *tmp1= dynamic_cast < ground *>(a[i][j]);
               area *tmp_area; 
               if((tmp1!=0) && (tmp1->get_status()==PATROL))
               {                          
                         int dx=rand()%3-1;
                         int dy=rand()%3-1;
                         while(i+dx<0 || i+dx>24) dx=rand()%3-1;
                         while(j+dy<0 || j+dy>24) dy=rand()%3-1;
                         point *tmp2= dynamic_cast < point *>(a[i+dx][j+dy]);
                         if((tmp2!=0) && (tmp2->get_fire_level()==0))
                         {          
                             tmp_area=a[i][j];     
                             a[i][j]=a[i+dx][j+dy];
                             a[i+dx][j+dy]=tmp_area; 
                             ground *new_ground= dynamic_cast < ground *>(a[i+dx][j+dy]);
                             new_ground->set_status(MOVED);
                         }
                         else
                         {
                             if(j<24)
                             {
                              point *tmp3= dynamic_cast < point *>(a[i][j+1]);
                              if((tmp3!=0) && (tmp3->get_fire_level()==0))
                              {          
                                tmp_area=a[i][j];     
                                a[i][j]=a[i][j+1];
                                a[i][j+1]=tmp_area; 
                                ground *new_ground= dynamic_cast < ground *>(a[i][j+1]);
                                new_ground->set_status(MOVED);
                              }
                             }
                         }    
                          
                }
                else
                {
                 aerial *tmp4= dynamic_cast < aerial *>(a[i][j]);
                 if((tmp4!=0) && (tmp4->get_status()==PATROL))
                 {                          
                         int dx=rand()%4-2;
                         int dy=rand()%4-2;
                         while(i+dx<0 || i+dx>24) dx=rand()%3-2;
                         while(j+dy<0 || j+dy>24) dy=rand()%3-2;
                         point *tmp5= dynamic_cast < point *>(a[i+dx][j+dy]);
                         if((tmp5!=0) && (tmp5->get_fire_level()==0))
                         {          
                             tmp_area=a[i][j];     
                             a[i][j]=a[i+dx][j+dy];
                             a[i+dx][j+dy]=tmp_area; 
                             aerial *new_aerial= dynamic_cast < aerial *>(a[i+dx][j+dy]);
                             new_aerial->set_status(MOVED);
                         }
                        else
                         {
                             if((i+dx<24) && (j+dy<24))
                             {
                               point *tmp5= dynamic_cast < point *>(a[i+dx+1][j+dy+1]);
                               if((tmp5!=0) && (tmp5->get_fire_level()==0))
                               {          
                                 tmp_area=a[i][j];     
                                 a[i][j]=a[i+dx+1][j+dy+1];
                                 a[i+dx+1][j+dy+1]=tmp_area; 
                                 aerial *new_aerial= dynamic_cast < aerial *>(a[i+dx+1][j+dy+1]);
                                 new_aerial->set_status(MOVED);
                               }
                             }
                         } 
			    }
               }
    }            	
 	for(int i=0;i<25;i++)
             for(int j=0;j<25;j++)	
                {
				  vehicle *c2= dynamic_cast < vehicle *>(a[i][j]);
                  if((c2!=0) && (c2->get_status()==MOVED))
                   c2->set_status(PATROL);				  
                 }				
}


void vehicle_check(area *a[26][25],timer c)
{
 for(int i=0;i<25;i++)
     for(int j=0;j<25;j++)  
      {
             vehicle *temp= dynamic_cast < vehicle *>(a[i][j]);
             if(temp!=0)
             {       
                temp->check();
                if(c.get_week()==52)
                temp->increase_age(); 
                if(temp->get_status()==FIRED)
                {
                  temp->increase_level();
                  if(temp->get_fire_level()==4)
                  {                        
                     delete(temp);
                     a[ i ][ j ] = ( area *) new point();
                  }                 
                }
             }
       } 
}


void fuel_consume(area *a[26][25])
{
   for(int i=0;i<25;i++)
    for(int j=0;j<25;j++)
     {
            vehicle *tmp= dynamic_cast < vehicle *>(a[i][j]);
            if((tmp!=0) && (tmp->get_status()==PATROL))
            {
                      tmp->set_fuel(tmp->get_fuel()- tmp->get_fuel_rate());
                      tmp->set_fuel_cons(tmp->get_fuel_cons()+tmp->get_fuel_rate());
            }  
     }
}              
            
void return_to_base(area *a[26][25])    
{
   int flag=0;
   for(int i=0;i<25;i++)
   {
    if(flag==1)
    {
      i++;
      flag=0;
    }  
    for(int j=0;j<25;j++)
    {	  
       aerial *tmp1= dynamic_cast < aerial *>(a[i][j]);
       area *tmp_area;
       if((tmp1!=0)  && (tmp1->get_status()==BROKENDOWN))
       {
                                             if(j<24) 
                                             {
                                                         point *tmp2= dynamic_cast < point *>(a[i][j+1]);
                                                         if((tmp2!=0) && (tmp2->get_fire_level()==0))
                                                         {          
                                                           tmp_area=a[i][j];     
                                                           a[i][j]=a[i][j+1];
                                                           a[i][j+1]=tmp_area; 
                                                           break;
                                                         }
                                                         else  
                                                         {
                                                           int dx=rand()%3-1;
                                                           int dy=rand()%3-1;
                                                           while(i+dx<0 || i+dx>24) dx=rand()%3-1;
                                                           while(j+dy<0 || j+dy>24) dy=rand()%3-1;
                                                           point *tmp3= dynamic_cast < point *>(a[i+dx][j+dy]);
                                                           if((tmp3!=0) && (tmp3->get_fire_level()==0))
                                                           {          
                                                             tmp_area=a[i][j];     
                                                             a[i][j]=a[i+dx][j+dy];
                                                             a[i+dx][j+dy]=tmp_area; 
                                                           }  
                                                         }
                                             }
                                             else
                                             {
                                                 int k=0;
                                                 point *tmp4= dynamic_cast < point *>(a[25][k]);
                                                 while(tmp4==0)
                                                 {
                                                               k++;
                                                               tmp4=dynamic_cast < point *>(a[25][k]);
                                                               
                                                 }
                                                 tmp_area=a[i][j];
                                                 a[i][j]=a[25][k];
                                                 a[25][k]=tmp_area;
                                             }     
       }
       else
       {
           ground *tmp5= dynamic_cast < ground *>(a[i][j]);
           if((tmp5!=0) && (tmp5->get_status()==BROKENDOWN))
           {
             if((i>=22) && (j<=2))
             {
                               int k=0;
                               point *tmp5= dynamic_cast < point *>(a[25][k]);
                               while(tmp5==0)
                               {
                                  k++;
                                  tmp5=dynamic_cast < point *>(a[25][k]);                        
                               }
                               tmp_area=a[i][j];
                               a[i][j]=a[25][k];
                               a[25][k]=tmp_area;      
             }
             else
             {
              if(j!=0)
	          {
	                              point *tmp6= dynamic_cast < point *>(a[i][j-1]);
                                  if((tmp6!=0) && (tmp6->get_fire_level()==0))
                                  {          
                                   tmp_area=a[i][j];     
                                   a[i][j]=a[i][j-1];
                                   a[i][j-1]=tmp_area;
                                  }
								  else
								  {
								   int dx=rand()%2-1;
                                   int dy=rand()%2-1;
                                   while(i+dx<0 || i+dx>24) dx=rand()%2-1;
                                   while(j+dy<0 || j+dy>24) dy=rand()%2-1;
                                   tmp6= dynamic_cast < point *>(a[i+dx][j+dy]);
                                   if((tmp6!=0) && (tmp6->get_fire_level()==0))
                                   {          
                                    tmp_area=a[i][j];     
                                    a[i][j]=a[i+dx][j+dy];
                                    a[i+dx][j+dy]=tmp_area; 
                                   }
								  }
              }
              else
              {
	                             point *tmp8= dynamic_cast < point *>(a[i+1][j]);
                                 if((tmp8!=0) && (tmp8->get_fire_level()==0))
                                 {          
                                   tmp_area=a[i][j];     
                                   a[i][j]=a[i+1][j];
                                   a[i+1][j]=tmp_area;
                                 }
                                 else
                                 {             
                                  int dx=rand()%2-1;
                                  int dy=rand()%2-1;
                                  while(i+dx<0 || i+dx>24) dx=rand()%2-1;
                                  while(j+dy<0 || j+dy>24) dy=rand()%2-1;
                                  tmp8= dynamic_cast < point *>(a[i+dx][j+dy]);
                                  if((tmp8!=0) && (tmp8->get_fire_level()==0))
                                  {          
                                   tmp_area=a[i][j];     
                                   a[i][j]=a[i+dx][j+dy];
                                   a[i+dx][j+dy]=tmp_area; 
                                  }
                                 }
                                 flag=1;	
	          }
            }	
          }                                                   
       }                                                 
}
} 
}
 
void repair_brokendown(area *a[26][25])
{
     area *t;
     for(int j=0;j<25;j++)
     {
      vehicle *temp= dynamic_cast < vehicle *>(a[25][j]);
      if(temp!=0 && temp->get_status()==BROKENDOWN)
      {
                if(temp->get_age()<=temp->get_retired_age())
                { 
                 point *t1= dynamic_cast < point *>(a[22][0]);
                 if(t1!=0 && t1->get_fire_level()==0)
                 {
                   temp->repair();       
                   t=a[25][j];
                   a[25][j]=a[22][0];
                   a[22][0]=t;  
                 }
                 else if((t1= dynamic_cast < point *>(a[22][1]))!=0 && t1->get_fire_level()==0)     
                 {
                   temp->repair();       
                   t=a[25][j];
                   a[25][j]=a[22][1];
                   a[22][1]=t;  
                 }
                 else if((t1= dynamic_cast < point *>(a[22][2]))!=0 && t1->get_fire_level()==0)     
                 {
                   temp->repair();       
                   t=a[25][j];
                   a[25][j]=a[22][2];
                   a[22][2]=t;  
                 }
                 else if((t1= dynamic_cast < point *>(a[23][2]))!=0 && t1->get_fire_level()==0)     
                 {
                   temp->repair();       
                   t=a[25][j];
                   a[25][j]=a[23][2];
                   a[23][2]=t;  
                 }
                 else if((t1= dynamic_cast < point *>(a[24][2]))!=0 && t1->get_fire_level()==0)     
                 {
                   temp->repair();       
                   t=a[25][j];
                   a[25][j]=a[24][2];
                   a[24][2]=t;  
                 }
                }
     }
    }
}  

void new_vehicle(int type,int i,int j,area *a[26][25])
{
    point *temp= dynamic_cast < point *>(a[i][j]);
    if(temp!=0)
    {
     delete(a[i][j]);
     if(type==0)
            a[ i ][ j ] = ( area *) new g_small();
       else if(type==1)
            a[ i ][ j ] = ( area *) new g_medium();
       else if(type==2)
            a[ i ][ j ] = ( area *) new g_large();    
       else if(type==3)
            a[ i ][ j ] = ( area *) new airplane();
       else if(type==4)
            a[ i ][ j ] = ( area *) new helicopter();   
    }                        
}                                                                                  
   

void call_backup(area *a[26][25])
{
      point *temp= dynamic_cast < point *>(a[22][0]);
      if(temp!=0 && temp->get_fire_level()==0)
      {
        delete(a[22][0]);
        a[22][0] = ( area *) new g_small();
      }  
      temp= dynamic_cast < point *>(a[22][1]);
      if(temp!=0 && temp->get_fire_level()==0)
      {
        delete(a[22][1]);
        a[22][1] = ( area *) new g_medium();
      }
      temp= dynamic_cast < point *>(a[22][2]);
      if(temp!=0 && temp->get_fire_level()==0)
      {
        delete(a[22][2]);
        a[22][2] = ( area *) new g_large();
      }
      temp= dynamic_cast < point *>(a[23][2]);
      if(temp!=0 && temp->get_fire_level()==0)
      {
        delete(a[23][2]);
        a[23][2] = ( area *) new airplane();
      }
      temp= dynamic_cast < point *>(a[24][2]);
      if(temp!=0 && temp->get_fire_level()==0)
      {
        delete(a[24][2]);
        a[24][2] = ( area *) new helicopter();
      }
}
                                                                                                    
#endif
