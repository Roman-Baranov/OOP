// Create by Roman Baranov
// On VSCode

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Pair1
{
private:
   T m_a;
   T m_b;

public:
   Pair1(const T &a, const T &b) : m_a(a), m_b(b) {}

   T &first() { return m_a; }
   const T &first() const { return m_a; }
   T &second() { return m_b; }
   const T &second() const { return m_b; }
};

int main()
{
   cout << "Выполнение первого задание: \n"
        << endl;
   Pair1<int> p1(6, 9);
   cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

   const Pair1<double> p2(3.4, 7.8);
   cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

      return 0;
}