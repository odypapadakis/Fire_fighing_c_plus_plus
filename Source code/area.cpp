#include "area.h"

#include <iostream>

using namespace::std;

//class area
  area::area()
  {
                    fire_level=0;
  }
  
  area::~area()
  {
  }              
 
  int area::get_fire_level() {return fire_level;}
    
  void area::set_fire_level(int a) {fire_level=a;}
  
  void area::increase_level() {fire_level++;}
  
  void area::print() {};
  
  
//class vehicle
 int vehicle::counter=0;

 vehicle::vehicle(string str,int a,int b,int c,int d, int e) //cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_ratio(=e),retired_age(=f) 
      : area(),name(str),speed(a),fuel_max(b),fuel_rate(c),water_max(d), retired_age(e)
      {           
        age=0;
        status=PATROL;
        fuel_cons=0;
        water_cons=0;
        fuel=b; // fuel kai water einai full otan ksekinane
        water=d;
        counter++;
      } 
     
      
 string vehicle::get_name() const  {return name;}     
      
 int vehicle::get_age()  {return age;}
      
 int vehicle::get_retired_age()  {return retired_age;}

 int vehicle::get_speed() const  {return speed;}
      
 Stat vehicle::get_status() {return status;}
            
 int vehicle::get_fuel_max() const   {return fuel_max;}
     
 int vehicle::get_fuel_rate() const   {return fuel_rate;}
      
 int vehicle::get_fuel()   {return fuel;}
      
 int vehicle::get_fuel_cons()   {return fuel_cons;}
     
 int vehicle::get_water_max() const  {return water_max;}
                 
 int vehicle::get_water()  {return water;}
    
 int vehicle::get_water_cons()  {return water_cons;}
      
 int vehicle::get_counter() {return counter;}
      
 void vehicle::increase_age()  {age++;}
      
 void vehicle::set_status(Stat a) {status=a;}
      
 void vehicle::set_fuel(int a) {fuel=a;}
      
 void vehicle::set_age(int a) {age=a;}
      
 void vehicle::set_water(int a) {water=a;}
	  
 void vehicle::set_water_cons(int a) {water_cons=a;}
	  
 void vehicle::set_fuel_cons(int a) {fuel_cons=a;}
      
 void vehicle::check()   
      {
                     int br=rand()%90+get_age();
                     if(get_status()!=FIRED)
                       if(get_fuel()==0 || get_water()==0 || br>=100 || (get_age()>=get_retired_age()))
                          set_status(BROKENDOWN);    
      }         
      
 void vehicle::repair()
      {
            set_fuel(get_fuel_max());
            set_water(get_water_max());
            set_status(PATROL);
      }  
	  
	  
 //class point
 point::point():area()//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_ratio(=e),retired_age(=f) 
      {}  
  
 point::~point() {}     
 
 void point::print()
     {cout<<"Point\n"<<"fire level: "<<get_fire_level()<<endl;} 
     
 	
	
//class base
Base::Base():area(){};

Base::~Base()
{ 
}
 
void Base::print()
    	{cout<<"Base Area\n"<<"fire level: "<<get_fire_level()<<endl;}
    	

	
//class ground
int ground::counter=0;

ground::ground(string str,int a,int b,int c,int d, int e,int f):vehicle(str,a,b,c,d,f),water_rate(e) //cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_rate(=e),retired_age(=f) 
      {
         counter++;           
      }  

ground::~ground()
{ 
                 counter--;
}

int ground::get_water_rate() const   {return water_rate;}

int  ground::get_counter()  {return ground::counter;}
void ground::print(){};


//class aerial
int aerial::counter=0;

 aerial::aerial(string str,int a,int b,int c,int d, int e):vehicle(str,a,b,c,d,e)//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_ratio(=e),retired_age(=f) 
      {
          counter++;          
      }  
      
aerial::~aerial()
{ 
                 counter--;
}
 int aerial::get_counter() {return aerial::counter;}
 
 void aerial::print(){};
 
 
//class g_small
int g_small::counter=0;

 g_small::g_small():ground("small tanker",80,200,4,4500,100,30)//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_ratio(=e),retired_age(=f) 
      {
          counter++;          
      }  
      
 g_small::~g_small()
{ 
                 counter--;
}

 int  g_small::get_counter() {return g_small::counter;}
 
 void g_small::refresh_counter() {g_small::counter--;}
 
 void g_small::print()
 {cout<<get_name()<<"\n"
      <<"age(actual/retired): "<<get_age()<<"/"<<get_retired_age()<<"\n"
      <<"speed: "<<get_speed()<<"\n"
      <<"fuel(actual/max   rate): "<<get_fuel()<<"/"<<get_fuel_max()<<"   "<<get_fuel_rate()<<"\n"
      <<"water(actual/max   rate): "<<get_water()<<"/"<<get_water_max()<<"   "<<get_water_rate()<<"\n"
      <<"fuel consume: "<<get_fuel_cons()<<"\n"
      <<"water consume: "<<get_water_cons()<<"\n"
      <<"status :";
  switch(get_status())
  {
   case ONDUTY:
       
              cout<<"ON DUTY"<<endl;
              break;
     
   case PATROL:
      
              cout<<"PATROL"<<endl;
              break;
         
   case BROKENDOWN:
       
              cout<<"BROKEN DOWN"<<endl;
              break;
           
   case FIRED:
       
              cout<<"FIRED"<<endl;
              break;
 }            
}   
 
 void g_small::ext(area *a[26][25],int x,int y)
{
  int flag=0;
  int cont=0;
  for(int i=1;i>=-1;i--)
  {
    for(int j=1;j>=-1;j--)
    {
	  if(((i+x>=0) && (i+x<24)) && ((j+y>=0) && (j+y<25)))
	   {
	    if ((a[i+x][j+y]->get_fire_level()>0) && (a[i+x][j+y]->get_fire_level()<9))
	    {
	     set_status(ONDUTY);
	     set_water(get_water()- get_water_rate());
	     set_water_cons(get_water_cons() + get_water_rate());
		 a[i+x][j+y]->set_fire_level(a[i+x][j+y]->get_fire_level()-1);
		 if(a[i+x][j+y]->get_fire_level()==0)
		 {
           for(int k=1;k>=-1;k--)
            for(int l=1;l>=-1;l--)
             if(((k+x>=0) && (k+x<24)) && ((l+y>=0) && (l+y<25)))
               if(a[k+x][l+y]->get_fire_level()>0)
                cont=1;
           if(cont==0)     
            set_status(PATROL);
          }   
		 flag=1;
	    }
	 	if(flag==1) break;	
    }
	if(flag==1) break;
  }	
 }
}


//class g_medium
int g_medium::counter=0;

 g_medium::g_medium():ground("medium tanker",80,220,4,5000,100,28)//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_ratio(=e),retired_age(=f) 
      {
          counter++;          
      }  

g_medium::~g_medium()
{ 
                 counter--;
}

 int g_medium::get_counter() {return g_medium::counter;}
 
 void g_medium::refresh_counter() {g_medium::counter--;}
 
 void g_medium::print()
 {cout<<get_name()<<"\n"
      <<"age(actual/retired): "<<get_age()<<"/"<<get_retired_age()<<"\n"
      <<"speed: "<<get_speed()<<"\n"
      <<"fuel(actual/max   rate): "<<get_fuel()<<"/"<<get_fuel_max()<<"   "<<get_fuel_rate()<<"\n"
      <<"water(actual/max   rate): "<<get_water()<<"/"<<get_water_max()<<"   "<<get_water_rate()<<"\n"
      <<"fuel consume: "<<get_fuel_cons()<<"\n"
      <<"water consume: "<<get_water_cons()<<"\n"
      <<"status :";
  switch(get_status())
  {
   case ONDUTY:
       
              cout<<"ON DUTY"<<endl;
              break;
     
   case PATROL:
      
              cout<<"PATROL"<<endl;
              break;
         
   case BROKENDOWN:
       
              cout<<"BROKEN DOWN"<<endl;
              break;
           
   case FIRED:
       
              cout<<"FIRED"<<endl;
              break;
 }         
}   
 
 void g_medium::ext(area *a[26][25],int x,int y)
 {
  int flag=0;
  int cont=0;
  for(int i=1;i>=-1;i--)
  {
    for(int j=1;j>=-1;j--)
    {
	  if(((i+x>=0) && (i+x<24)) && ((j+y>=0) && (j+y<25)))
	   {
	    if ((a[i+x][j+y]->get_fire_level()>0) && (a[i+x][j+y]->get_fire_level()<9))
	    {
	     set_status(ONDUTY);
	     set_water(get_water()- get_water_rate());
	     set_water_cons(get_water_cons() + get_water_rate());
		 a[i+x][j+y]->set_fire_level(a[i+x][j+y]->get_fire_level()-1);
		 if(a[i+x][j+y]->get_fire_level()==0)
		 {
           for(int k=1;k>=-1;k--)
            for(int l=1;l>=-1;l--)
             if(((k+x>=0) && (k+x<24)) && ((l+y>=0) && (l+y<25)))
               if(a[k+x][l+y]->get_fire_level()>0)
                cont=1;
           if(cont==0)     
            set_status(PATROL);
          }   
		 flag=1;
	    }
	 	if(flag==1) break;	
    }
	if(flag==1) break;
  }	
 }
}


//class g_large
int g_large::counter=0;

 g_large::g_large():ground("large tanker",70,260,5,6000,100,26)//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),water_ratio(=e),retired_age(=f) 
      {
          counter++;          
      }  
      
g_large::~g_large()
{ 
                 counter--;
}     

 int g_large::get_counter() {return g_large::counter;}
 
 void g_large::refresh_counter() {g_large::counter--;}
 
void g_large::print()
 {cout<<get_name()<<"\n"
      <<"age(actual/retired): "<<get_age()<<"/"<<get_retired_age()<<"\n"
      <<"speed: "<<get_speed()<<"\n"
      <<"fuel(actual/max   rate): "<<get_fuel()<<"/"<<get_fuel_max()<<"   "<<get_fuel_rate()<<"\n"
      <<"water(actual/max   rate): "<<get_water()<<"/"<<get_water_max()<<"   "<<get_water_rate()<<"\n"
      <<"fuel consume: "<<get_fuel_cons()<<"\n"
      <<"water consume: "<<get_water_cons()<<"\n"
      <<"status :";
  switch(get_status())
  {
   case ONDUTY:
       
              cout<<"ON DUTY"<<endl;
              break;
     
   case PATROL:
      
              cout<<"PATROL"<<endl;
              break;
         
   case BROKENDOWN:
       
              cout<<"BROKEN DOWN"<<endl;
              break;
           
   case FIRED:
       
              cout<<"FIRED"<<endl;
              break;
 }         
}   
           
  void g_large::ext(area *a[26][25],int x,int y)
 {
  int flag=0;
  int cont=0;
  for(int i=1;i>=-1;i--)
  {
    for(int j=1;j>=-1;j--)
    {
	  if(((i+x>=0) && (i+x<24)) && ((j+y>=0) && (j+y<25)))
	   {
	    if ((a[i+x][j+y]->get_fire_level()>0) && (a[i+x][j+y]->get_fire_level()<9))
	    {
	     set_status(ONDUTY);
	     set_water(get_water()- get_water_rate());
	     set_water_cons(get_water_cons() + get_water_rate());
		 a[i+x][j+y]->set_fire_level(a[i+x][j+y]->get_fire_level()-1);
		 if(a[i+x][j+y]->get_fire_level()==0)
		 {
           for(int k=1;k>=-1;k--)
            for(int l=1;l>=-1;l--)
             if(((k+x>=0) && (k+x<24)) && ((l+y>=0) && (l+y<25)))
               if(a[k+x][l+y]->get_fire_level()>0)
                cont=1;
           if(cont==0)     
            set_status(PATROL);
          }   
		 flag=1;
	    }
	 	if(flag==1) break;	
    }
	if(flag==1) break;
  }	
 }
}  


      

//class airplane
int airplane::counter=0;

 airplane::airplane():aerial("canadair",200,1000,20,6000,25)//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),retired_age(=f) 
      {
          counter++;          
      }  

airplane::~airplane()
{ 
                 counter--;
}

 int airplane::get_counter() {return airplane::counter;}
 
 void airplane::refresh_counter() {airplane::counter--;}
 
 void airplane::print()
 {cout<<get_name()<<"\n"
      <<"age(actual/retired): "<<get_age()<<"/"<<get_retired_age()<<"\n"
      <<"speed: "<<get_speed()<<"\n"
      <<"fuel(actual/max): "<<get_fuel()<<"/"<<get_fuel_max()<<"\n"
      <<"water(actual/max: "<<get_water()<<"/"<<get_water_max()<<"\n"
      <<"fuel consume: "<<get_fuel_cons()<<"\n"
      <<"water consume: "<<get_water_cons()<<"\n"
      <<"status :";
  switch(get_status())
  {
   case ONDUTY:
              cout<<"ON DUTY"<<endl;
              break;      
   case PATROL:
              cout<<"PATROL"<<endl;
              break;
   case BROKENDOWN:
              cout<<"BROKEN DOWN"<<endl;
              break;   
   case FIRED:
              cout<<"FIRED"<<endl;
              break;
  }
}     
                   
 
  void airplane::ext(area *a[26][25],int x,int y)
{
  int flag=0;
  for(int i=1;i>=-1;i--)
  {
    for(int j=1;j>=-1;j--)
    {
	  if(((i+x>=0) && (i+x<24)) && ((j+y>=0) && (j+y<25)))
	   {
	    if ((a[i+x][j+y]->get_fire_level()>0) && (a[i+x][j+y]->get_fire_level()<9))
	    {
	     set_water(0);
	     set_water_cons(get_water_cons() + get_water_max());
		 a[i+x][j+y]->set_fire_level(0);
		 flag=1;
	    }
	 	if(flag==1) break;	
    }
	if(flag==1) break;
  }	
 }
}  


      

//class helicopter
int helicopter::counter=0;

 helicopter::helicopter():aerial("Ericcson Air-crane",180,800,16,4500,26)//cosntructor given name(=str),speed(=a),fuel_max(=b),fuel_ratio(=c),water_max(=d),retired_age(=f) 
      {
          counter++;          
      }  
      
 helicopter::~helicopter()
{ 
                 counter--;
}     

 int helicopter::get_counter() {return helicopter::counter;}
 
 void helicopter::refresh_counter() {helicopter::counter--;}
 
void helicopter::print()
 {
 cout<<get_name()<<"\n"
      <<"age(actual/retired): "<<get_age()<<"/"<<get_retired_age()<<"\n"
      <<"speed: "<<get_speed()<<"\n"
      <<"fuel(actual/max   rate): "<<get_fuel()<<"/"<<get_fuel_max()<<"\n"
      <<"water(actual/max   rate): "<<get_water()<<"/"<<get_water_max()<<"\n"
      <<"fuel consume: "<<get_fuel_cons()<<"\n"
      <<"water consume: "<<get_water_cons()<<"\n"
      <<"status :";
  switch(get_status())
  {
   case ONDUTY:
              cout<<"ON DUTY"<<endl;
              break;      
   case PATROL:
              cout<<"PATROL"<<endl;
              break;
   case BROKENDOWN:
              cout<<"BROKEN DOWN"<<endl;
              break;   
   case FIRED:
              cout<<"FIRED"<<endl;
              break;
  }
}   
 
  void helicopter::ext(area *a[26][25],int x,int y)
{

  for(int i=1;i>=-1;i--)
  {
    for(int j=1;j>=-1;j--)
    {
	  if(((i+x>=0) && (i+x<24)) && ((j+y>=0) && (j+y<25)))
	   {
	    if ((a[i+x][j+y]->get_fire_level()>0) && (a[i+x][j+y]->get_fire_level()<9))
	    {
	     set_water(get_water()-2250);
	     set_water_cons(get_water_cons() + 2250);
		 a[i+x][j+y]->set_fire_level(0);
	    }
	 	if(get_water()==0) break;	
    }
	if(get_water()==0) break;
  }	
 }
}

     
