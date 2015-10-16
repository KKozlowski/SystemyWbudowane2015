#include <VGAX.h>

class Margins
{
  private:
  int a=0;
  int b=-3;
  public:
  void Lines(){
   for(int i=b; i<60; i=i+4){
    //lewa
   VGAX::fillrect(1, i, 2, 2, 2);
   VGAX::fillrect(1, i+2, 2, 2, 0);
    //prawa
   VGAX::fillrect(117, i, 2, 2, 2);
   VGAX::fillrect(117, i+2, 2, 2, 0);
   }
   b++;
   if(b>0){b=-3;}
  }
  void Draw ()
  {
   if(a%10==0){
    Lines();
   }
   //lewa
   VGAX::fillrect(0, 0, 1, 60, 2);//zielone ?filary
   VGAX::fillrect(3, 0, 1, 60, 2);//zielone ?filary
   //prawa
   VGAX::fillrect(116, 0, 1, 60, 2);//zielone ?filary
   VGAX::fillrect(119, 0, 1, 60, 2);//zielone ?filary
   a++;
  }
};
