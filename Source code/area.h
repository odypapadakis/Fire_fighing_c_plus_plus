#ifndef AREA_H
#define AREA_H

#include <string>

using namespace::std;

enum Stat {ONDUTY,PATROL,BROKENDOWN,MOVED,FIRED};

class area
{
      public:
      area();
      ~area();
      int get_fire_level();
      void set_fire_level(int);
      void increase_level();
      virtual void print()=0;
     
      private:
      int fire_level;
};


// area's subclasses

class vehicle : public area
{
      public:   
      vehicle( string , int, int, int, int, int); 
      string get_name() const;
      int get_age();
      int get_retired_age();     
      int get_speed() const ;  
      Stat get_status();            
      int get_fuel_max() const ;    
      int get_fuel_rate() const ;     
      int get_fuel();        
      int get_fuel_cons();     
      int get_water_max() const ;        
      int get_water();    
      int get_water_cons();
      int static get_counter();             
      void increase_age();   
      void set_status(Stat); 
      void set_fuel(int);
      void set_fuel_cons(int);	  
      void set_age(int);
      void set_water(int);
	  void set_water_cons(int);
      void repair();
      void check();
      virtual void print()=0;
      virtual void ext(area *[26][25],int,int)=0;
     
      private:
      const string name;
      int age;
      const int retired_age;
      int speed;
      Stat status;
      const int fuel_max;
      const int fuel_rate;
      int fuel;
      int fuel_cons;
      const int water_max;   
      int water;
      int water_cons;
      static int counter;
      
};  

class point : public area
{
      public:
      point();  
      ~point();
      void print();  
      
};    

class Base : public area
{
      public:
      Base();
      ~Base();
      void print();

};


//vehicle's subclasses

class ground : public vehicle 
{ 
  public:
  ground( string , int, int, int, int, int, int);
  ~ground();
  int static get_counter();
  int get_water_rate() const ;
  void print();
  void ext(area *[26][25],int,int)=0;
    
  private: 
  const int water_rate;
  static int counter;
};

class aerial : public vehicle 
{ 
      
  public:
  aerial( string , int, int, int, int, int); 
  ~aerial();
  int static get_counter();
  void print();
  void ext(area *[26][25],int,int)=0;
  
  private:
  static int counter;
};


//ground's subclasses

class g_small : public ground
{
      public:
      g_small();
      ~g_small();
      int static get_counter();
      void static refresh_counter();
      void print();
	  void ext(area *[26][25],int,int);
      
      private:
      static int counter;
};

class g_medium : public ground
{
      public:
      g_medium();
      ~g_medium();
      int static get_counter();
      void static refresh_counter();
      void print();
      void ext(area *[26][25],int,int);
      
      private:
      static int counter;
};

class g_large : public ground
{
      public:
      g_large();
      ~g_large();
      void static refresh_counter();
      int static get_counter();
      void print();
      void ext(area *[26][25],int,int);
            
      private:
      static int counter;
};


//aerial's subclasses

class airplane : public aerial
{
      public:
      airplane();
      ~airplane();
      int static get_counter();
      void static refresh_counter();
      void print();
      void ext(area *[26][25],int,int);
      
      private:
      static int counter;
};

class helicopter : public aerial
{
      public:
      helicopter();
      ~helicopter();
      int static get_counter();
      void static refresh_counter();
      void print();
      void ext(area *[26][25],int,int);
      
      private:
      static int counter;
};

#endif 
