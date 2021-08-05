// Create by Roman Baranov
// On VSCode

#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#include <cmath>

using namespace std;

//========================================= 1 Задание ======================================================

class Figure
{
public:
   Figure()
   {
      //cout << "Figure ctr" << endl;
   }

   virtual void area() = 0;

   virtual ~Figure()
   {
      //cout << "Figure dtr" << endl;
   }
};

class Parallelogram : public Figure
{
protected:
   int base;   //основание
   int height; //высота
public:
   Parallelogram(int value_base, int value_height) : base(value_base), height(value_height) {}
   void area() override
   {
      cout << "The parallelogram area is " << base * height << endl;
   }
};
class Circle : public Figure
{
   double radius;
   double P;

public:
   Circle(double value_radius) : radius(value_radius) {}
   void area() override
   {
      cout << "The area of the circle is " << 3.1415 * (radius * radius) << endl;
   }
};

class Rectangle : public Parallelogram
{
public:
   Rectangle(int value_base, int value_height) : Parallelogram(value_base, value_height) {}
   void area() override
   {
      cout << "The area of the triangle is " << base * height << endl;
   }
};

class Square : public Parallelogram
{
public:
   Square(int value_base, int value_height) : Parallelogram(value_base, value_height) {}

   void area() override
   {
      cout << "The square area is " << base * height << endl;
   }
};

class Rhombus : public Parallelogram
{
public:
   Rhombus(int value_base, int value_height) : Parallelogram(value_base, value_height) {}
   void area() override
   {
      cout << "The area of the rhombus is " << base * height << endl;
   }
};

//=========================================== 2 задание =======================================================

class Car
{
protected:
   string m_company;
   string m_model;

public:
   Car()
   {
      //cout << "Car ctr" << endl;
   }

   Car(string company, string model) : m_company(company), m_model(model)
   {
   }
};

// Наследники
class PassangerCar : virtual public Car
{
public:
   PassangerCar()
   {
      //cout << "PassangerCar ctr" << endl;
   }

   PassangerCar(string company, string model) : Car(company, model)
   {
   }
   void print()
   {
      cout << "Passenger car info: \n Company: " << m_company << "\n Model: " << m_model << endl;
   }
};

class Bus : public virtual Car
{
public:
   Bus()
   {
      //cout << "Bus ctr" << endl;
   }

   Bus(string company, string model) : Car(company, model)
   {
   }
   void print()
   {
      cout << "Bus info: \n Company: " << m_company << "\n Model: " << m_model << endl;
   }
};

class Minivan : public PassangerCar, public Bus
{
public:
   Minivan()
   {
      //cout << "Minivan ctr" << endl;
   }

   Minivan(string company, string model) : Car(company, model)
   {
   }
   void print()
   {
      cout << "Minivan info: \n Company: " << m_company << "\n Model: " << m_model << endl;
   }
};

//============================================= 3 Задание =====================================================

class Fraction
{
   int m_num;
   int m_denom;

public:
   Fraction(int num, int denom)
   {
      if (m_denom == 0)
      {
         throw std::runtime_error("The denominator cannot be 0");
         this->m_num = num;
         this->m_denom = denom;
      };
   }

   int getNum(int num) const
   {
      return m_num;
   }

   int getDenom(int denom) const
   {
      return m_denom;
   }

   bool operator==(const Fraction &other)
   {
      return this->m_num == other.m_num && this->m_denom == other.m_denom;
   }

   bool operator!=(const Fraction &other)
   {
      return this->m_num != other.m_num && this->m_denom != other.m_denom;
   }

   bool operator<(const Fraction &other)
   {
      if (this->m_num >= other.m_num && this->m_denom >= other.m_denom)
      {
         return false;
      }
      else
      {
         return true;
      }
   }

   bool operator>(const Fraction &other)
   {
      if (this->m_num <= other.m_num && this->m_denom <= other.m_denom)
      {
         return false;
      }
      else
      {
         return true;
      }
   }

   friend Fraction operator+(const Fraction &f1, const Fraction &f2)
   {
      return Fraction(f1.m_num * f2.m_denom + f2.m_num * f1.m_denom, f1.m_num * f2.m_num);
   }

   friend Fraction operator-(const Fraction &f1, const Fraction &f2)
   {
      return Fraction(f1.m_num * f2.m_denom - f2.m_num * f1.m_denom, f1.m_num * f2.m_num);
   }

   friend Fraction operator*(const Fraction &f1, const Fraction &f2)
   {
      return Fraction(f1.m_num * f2.m_num, f1.m_denom * f2.m_denom);
   }

   friend Fraction operator/(const Fraction &f1, const Fraction &f2)
   {
      return Fraction(f1.m_num / f2.m_num, f1.m_denom * f2.m_denom);
   }
};

//============================================= 4 Задание ============================================================

class Card
{
protected:
   enum CardsValue
   {
      two = 2,
      three = 3,
      four = 4,
      five = 5,
      six = 6,
      seven = 7,
      eight = 8,
      nine = 9,
      ten = 10,
      Jack = 11,
      Queen = 12,
      King = 13,
      Ace = 1
   };

   enum Suits
   {
      Heart,
      Diamond,
      Club,
      Spade
   };
   bool cardPosition = true;

public:
   Card()
   {
   }

   bool Flip()
   {
      if (cardPosition)
      {
         return false;
      }
      else
      {
         return true;
      }
   }

   int GetValue()
   {
      return CardsValue();
   }
};

int main()
{
   cout << "Первое задание: \n";

   Parallelogram p(3, 5);
   p.area();

   Circle c(4);
   c.area();

   Rectangle r(5, 8);
   r.area();

   Square s(4, 4);
   s.area();

   Rhombus rom(4, 6);
   rom.area();

   cout << "\nВторое задание: \n";

   PassangerCar pas("Mercedes-Banz", "CLA 200 AMG");

   Bus bus("Volvo", "9500");

   Minivan mini("Mercedes-Banz", "V-Class");

   pas.print();

   bus.print();

   mini.print();

   cout << "\nТретье задание: \n";

   Fraction f1(3, 7);

   Fraction f2(5, 12);

   bool result_1 = f1 == f2;

   bool result_2 = f1 != f2;

   bool result_3 = f1 < f2;

   bool result_4 = f1 > f2;

   Fraction f_sum = f1 + f2;

   Fraction f_sub = f1 - f2;

   Fraction f_pro = f1 * f2;

   Fraction f_res = f1 / f2;

   cout << "\nBlackJack baby: \n";

   return 0;
}