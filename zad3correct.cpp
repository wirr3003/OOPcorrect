#include <iostream>
#include "graphics.h"
#include <math.h>

#define M_PI 3.141592

using namespace std;

class Figure{
  int c; //цвет
  bool visible; // видимость
protected:
  int x, y; //базова€ точка
  virtual void draw() = 0; // нарисовать
public:
  Figure(int c, int x, int y):c(c), visible(0), x(x), y(y) {}//конструктор
  virtual ~Figure() {}//деструктор
  void move(int x, int y); //сместить фигуру в (x, y)
  void setcolor(int c); //установить цвет фигуры, видима€ рисуетс€, у невидимой мен€етс€ цвет
  int getcolor() const { return c; } //получить цвет
  void hide(); //спр€тать
  void show(); //показать
  bool isvisible() const { return visible; } //видима?
  virtual void area(int &x1, int &y1, int &m) const = 0; //размеры //области, содержащей фигуру
};
class Triangle: public Figure {
protected:
   int a, b, ang; //длины катетов, угол поворота
   void draw();//рисование
public:
   Triangle(int c, int x, int y, int a, int b, int ang): Figure(c, x, y), a(a), b(b), ang(ang) {}//конструктор
   ~Triangle() { hide(); }//деструктор
   void setsizes(int a, int b); //изменение длин сторон треугольника
   void area(int &x1, int &y1, int &R) const; //область, где нарисована фигура
   void calccoord(int &x_1, int &y_1, int &x_2, int &y_2)const;
};
class FillTriangle: public Triangle {
protected:
   int fc; //÷вет фигуры
   void draw();//рисование
public:
   FillTriangle(int c, int x, int y, int a, int b, int ang, int fc):Triangle(c, x, y, a, b, ang), fc(fc) {}
   void setfillcolor(int);//изменить цвет
};
void Figure::setcolor(int c) {
   this->c=c;
   if (visible) draw();
}
void Figure::move(int x, int y) {
   ::setcolor(getcolor());
   bool f=visible;
   if (f) hide();
   this->x=x;
   this->y=y;
   if (f) show();
}
void Figure::hide() {
   if (!visible) return;
   int x1, y1, R;
   area(x1, y1, R);
   ::setcolor(BLACK);
   setfillstyle(SOLID_FILL, BLACK);
   void rectangle(x1,  y1, R);//Ќјƒќ ѕќѕ–ј¬»“№
   visible=0;
}
void Figure::show() {
   if (visible) return;
   visible=1;
   draw();
}
void Triangle::setsizes(int a, int b) {
   bool f=isvisible();
   if (f) hide();
   this->a=a;
   this->b=b;
   if (f) show();
}

void Triangle::calccoord(int &x_1, int &y_1, int &x_2, int &y_2)const
{
   double cs = cos(ang * M_PI /180);
   double sn = sin(ang * M_PI /180);
   x_1 = x + a*cs - sn;
   y_1 = y + a*sn + cs;
   x_2 = x + cs - b*sn;
   y_2 = y + sn + b*cs;
}

void Triangle::area(int &x1, int &y1, int &R)const {
   int x_1, y_1, x_2, y_2, x_3, y_3;
   calccoord(x_1, y_1, x_2, y_2);
   double c = sqrt(pow(x_2-x_1,2)+pow(y_2-y_1,2));
   double cs = cos(ang*M_PI/180);
   double sn = sin(ang*M_PI/180);
   x_3 = (x +(a/2)*cs - (b/2)*sn);
   y_3 = (y + (a/2)*sn + (b/2)*cs);
   x1=x_3;
   y1=y_3;
   R = (c/2) + 20;
}

void Triangle::draw() {
   ::setcolor(getcolor());
   int x_1, y_1, x_2, y_2;
   calccoord(x_1, y_1, x_2, y_2);
   line(x, y, x_1, y_1);
   line(x_1, y_1, x_2, y_2);
   line(x_2, y_2, x, y);
}

void FillTriangle::draw() {
   int x_1, y_1, x_2, y_2;
   calccoord(x_1, y_1, x_2, y_2);
   int p[6]={x, y, x_1,y_1, x_2, y_2};
   setfillstyle(SOLID_FILL, fc);
   fillpoly(3, p);
   Triangle::draw();
}
void FillTriangle::setfillcolor(int a) {
   fc=a;
   if (isvisible()) draw();
}
int main() {//ќ“–≈ƒј„»“№ 
   initwindow(640, 480);
   Figure *a=new Triangle(GREEN, 110, 110, 157, 112, 20);
   Figure *b=new FillTriangle(YELLOW, 200, 300, 100, 175, 15, BROWN);
   a->show();
   b->show();
   getch();
   a->move(90, 90);
   b->move(75, 115);
   a->show();
   b->show();
   getch();
   a->setcolor(WHITE);
   b->setcolor(RED);
   getch();
   if(Triangle *R=dynamic_cast<Triangle*>(a)) R->setsizes(100,130);
   if(Triangle *R=dynamic_cast<Triangle*>(b)) R->setsizes(80,150);
   getch();
   if(FillTriangle *R=dynamic_cast<FillTriangle*>(a)) R->setfillcolor(GREEN);
   if(FillTriangle *R=dynamic_cast<FillTriangle*>(b)) R->setfillcolor(GREEN);
   getch();
   delete a;
   delete b;
   getch();
   return 0;
}