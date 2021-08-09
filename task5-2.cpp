// Create by Roman Baranov
// On VSCode

#include <iostream>
#include <string>

using namespace std;

//============================================ 2 задание ====================================================

template <class T, class S>
class Pair
{
private:
   T m_a;
   S m_b;

public:
   Pair(const T &a, const S &b) : m_a(a), m_b(b)
   {
   }

   T &first() { return m_a; }
   const T &first() const { return m_a; }
   S &second() { return m_b; }
   const S &second() const { return m_b; }
};

int main()
{
   cout << "Выполнение второго задания: \n"
        << endl;

   Pair<int, double> p1(6, 7.8);
   cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

   const Pair<double, int> p2(3.4, 5);
   cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

   return 0;
}