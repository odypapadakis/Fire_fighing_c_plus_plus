#ifndef TIMER_H
#define TIMER_H

class timer
{
      public:
             timer();
             int get_year();
             int get_week();
             void operator++ (int);
             
      private:
              int week;
              int year;
};

timer::timer()
{
            week=0;
            year=0;
}

int timer::get_year()
    {
       return year;
    }                                     
          
int timer::get_week()
    {
       return week;
    }                  
      
void  timer::operator++ (int){
        if(week<52)
           week+=2;
        else
        {
            week=0;
            year++;      
        }
  }
#endif
