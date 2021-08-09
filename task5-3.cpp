// Create by Roman Baranov
// On VSCode

#include <iostream>
#include <string>

using namespace std;

//================================================ 3 задание ===================================================

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

template <class S>
class StringValuePair : public Pair<string, S>
{
public:
   StringValuePair(const string &key, const S &value) : Pair<string, S>(key, value)
   {
   }
};

int main()
{
   cout << "Выполнение третьего задания: \n"
        << endl;

   StringValuePair<int> svp("Amazing", 7);
   cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
   return 0;
}