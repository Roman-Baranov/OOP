// Выполнил Роман Баранов
// VSCode

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

class Person
{

public:
   string m_name;
   int m_age;
   string m_gender;
   int m_weight;

   Person(string name = "", int age = 0, string gender = "", int weight = 0) : m_name(name), m_age(age), m_gender(gender), m_weight(weight)
   {
   }

   string getName() const { return m_name; }
   int getAge() const { return m_age; }
   string getGender() const { return m_gender; }
   int getWeight() const { return m_weight; }
};

class Student : public Person
{
public:
   int m_year;

   Student(int year = 0) : m_year(year) {}
   int getYear() { return m_year; }
};

//========================================= 2 задание =======================================

class Fruit
{

public:
   string m_name;
   string m_color;

   Fruit() : m_name(""), m_color()
   {
   }

   Fruit(string name, string color)
   {
      m_name = name;
      m_color = color;
   }
};

class Apple : public Fruit
{
public:
   Apple()
   {
   }

   string getName()
   {
      return "apple";
   }

   Apple(string color)
   {
      m_color = color;
   }

   string getColor()
   {
      return m_color;
   }
};

class Banana : public Fruit
{
public:
   string getName()
   {
      return "banana";
   }

   string getColor()
   {
      return "yellow";
   }
};

class GrannySmith : public Apple
{
public:
   GrannySmith()
   {
   }

   string getName()
   {
      return "Granny Smith apple";
   }

   string getColor()
   {
      return "green";
   }
};

int main()
{

   setlocale(LC_CTYPE, "rus");

   cout << "Список студентов: \n"
        << endl;

   Student roman;
   // Присваиваем данные
   roman.m_name = "Roman";
   roman.m_age = 35;
   roman.m_gender = "Male";
   roman.m_weight = 80;
   roman.m_year = 2021;
   // Выводим данные студента
   cout << "Name: " << roman.getName() << '\n';
   cout << "Age: " << roman.getAge() << '\n';
   cout << "Gender: " << roman.getGender() << '\n';
   cout << "Weight: " << roman.getWeight() << '\n';
   cout << "Year on studing: " << roman.getYear() << "\n\n";

   Student daria;
   daria.m_name = "Daria";
   daria.m_age = 30;
   daria.m_gender = "Female";
   daria.m_weight = 55;
   daria.m_year = 2018;
   // Выводим данные студента
   cout << "Name: " << daria.getName() << '\n';
   cout << "Age: " << daria.getAge() << '\n';
   cout << "Gender: " << daria.getGender() << '\n';
   cout << "Weight: " << daria.getWeight() << '\n';
   cout << "Year on studing: " << daria.getYear() << "\n\n";

      cout << "Фрукты и их цвета: \n"
        << endl;

   Apple a("red");
   Banana b;
   GrannySmith c;

   cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
   cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
   cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

   return 0;
}