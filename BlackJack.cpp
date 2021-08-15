#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Card
{
public:
   enum rank
   {
      ACE = 1,
      TWO,
      THREE,
      FOUR,
      FIVE,
      SIX,
      SEVEN,
      EIGHT,
      NINE,
      TEN,
      JECK,
      QUEEN,
      KING
   };
   enum suit
   {
      CLUBS,
      DIAMOND,
      HEARTS,
      SPADES
   };

   friend ostream &operator<<(ostream &os, const Card &aCard);
   Card(rank r = ACE, suit s = SPADES, bool ifu = true);

   int GetValue() const;

   void Flip();

private:
   rank m_Rank;
   suit m_Suit;
   bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{
}
int Card::GetValue() const
{
   int value = 0;
   if (m_IsFaceUp)
   {
      value = m_Rank;
      if (value > 10)
      {
         value = 10;
      }
   }
   return value;
}

void Card::Flip()
{
   m_IsFaceUp = !(m_IsFaceUp);
}

class Hand
{
public:
   Hand();
   virtual ~Hand();
   void Add(Card *pCard); // добавляет карты в руку
   void Clear();          // очищает руку
   int GetTotal() const;  // получает сумму очков
protected:
   vector<Card *> m_Cards;
};

Hand::Hand()
{
   m_Cards.reserve(7);
}
Hand::~Hand()
{
   Clear();
}
void Hand::Add(Card *pCard)
{
   m_Cards.push_back(pCard);
}
void Hand::Clear()
{
   vector<Card *>::iterator iter = m_Cards.begin(); //освобождение всей памяти в куче!
   for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
   {
      delete *iter;
      *iter = 0;
   }
   m_Cards.clear(); //очистка указателей вектора
}
int Hand::GetTotal() const
{
   if (m_Cards.empty()) //если карт нет возвращаем 0
   {
      return 0;
   }
   if (m_Cards[0]->GetValue() == 0) //если карта имеет значение 0 она лежит рубашкой вверх!
   {
      return 0;
   }
   int total = 0;
   vector<Card *>::const_iterator iter;
   for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
   {
      total += (*iter)->GetValue();
   }
   bool containsAce = false; // определяем туза в руке
   for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
   {
      if ((*iter)->GetValue() == Card::ACE)
      {
         containsAce = true;
      }
   }
   if (containsAce && total <= 11) //если в руке туз но очков мало туз делается 11!
   {
      total += 10;
   }
   return total;
}

class GenericPlayer : public Hand
{
   friend ostream &operator<<(ostream &os, const GenericPlayer &GenericPlayer);

public:
   GenericPlayer(const string &hame = " "); //хочет ли игрок взять еще карту
   virtual ~GenericPlayer();
   virtual bool IsHitting() const = 0; //возврат значения при переборе
   bool IsBusted() const;              // обьявление перебора
   void Bust() const;

protected:
   string m_Name;
};
GenericPlayer::GenericPlayer(const string &name) : m_Name(name)
{
}
GenericPlayer::~GenericPlayer()
{
}
bool GenericPlayer::IsBusted() const
{
   return (GetTotal() > 21);
}
void GenericPlayer::Bust() const
{
   cout << m_Name << " busts.\n";
}

class Player : public GenericPlayer
{
public:
   Player(const string &name = " ");
   virtual ~Player();
   virtual bool IsHitting() const; // показывает хочет ли игрок брать еще карту
   void Win() const;
   void Lose() const;
   void Draw() const;
};

Player::Player(const string &name) : GenericPlayer(name)
{
}
Player::~Player()
{
}
bool Player::IsHitting() const
{
   cout << m_Name << " , do you want a hit? (y/n): ";
   char response;
   cin >> response;
   return (response == 'y' || response == 'Y');
}
void Player::Win() const
{
   cout << m_Name << " wins!\n";
}
void Player::Lose() const
{
   cout << m_Name << " lose!\n";
}
void Player::Draw() const
{
   cout << m_Name << " Draw!\n";
}

class House : public GenericPlayer
{
public:
   House(const string &name = "House");
   virtual ~House();
   virtual bool IsHitting() const;
   void FlipFirstCard();
};
House::~House()
{
}
bool House::IsHitting() const
{
   return (GetTotal() <= 16);
}
void House::FlipFirstCard()
{
   if (!(m_Cards.empty()))
   {
      m_Cards[0]->Flip();
   }
   else
   {
      cout << "No card to flip!\n";
   }
}

class Deck : public Hand
{
public:
   Deck();
   virtual ~Deck();
   void Populate();                                     //создание колоды
   void Shuffle();                                      //перетосовка
   void Deal(Hand &aHand);                              // раздача карт
   void AdditionalCards(GenericPlayer &aGenericPlayer); //доп карта
};

Deck::Deck()
{
   m_Cards.reserve(52);
   Populate();
}
Deck::~Deck()
{
}
void Deck::Populate()
{
   Clear(); //создание колоды
   for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
   {
      for (int r = Card::ACE; r <= Card::KING; ++r)
      {
         Add(new Card(static_cast<Card ::rank>(r), static_cast<Card::suit>(s)));
      }
   }
}
void Deck::Shuffle()
{
   random_shuffle(m_Cards.begin(), m_Cards.end());
}
void Deck::Deal(Hand &aHand)
{
   if (!m_Cards.empty())
   {
      aHand.Add(m_Cards.back());
      m_Cards.pop_back();
   }
   else
   {
      cout << "Out of cards. Unable to deal.";
   }
}
void Deck::AdditionalCards(GenericPlayer &aGenericPlayer)
{
   cout << endl;
   while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) //раздает карты пока не будет перебора
   {
      Deal(aGenericPlayer);
      cout << aGenericPlayer << endl;
      if (aGenericPlayer.IsBusted())
      {
         aGenericPlayer.Bust();
      }
   }
}
class Game
{
public:
   Game(const vector<string> &names);
   ~Game();
   void Play(); // приводит в игру
private:
   Deck m_Dack;
   House m_House;
   vector<Player> m_Players;
};

Game::Game(const vector<string> &names)
{
   vector<string>::const_iterator pName; // создает вектор игроков из вектора с именами
   for (pName = names.begin(); pName != names.end(); ++pName)
   {
      m_Players.push_back(Player(*pName));
   }
   srand(static_cast<unsigned int>(time(0))); // ген случайных чисел
   m_Dack.Populate();
   m_Dack.Shuffle();
}
Game::~Game()
{
}
void Game::Play()
{
   vector<Player>::iterator pPlayer; //раздача по 2 карты каждому
   for (int i = 0; i < 2; ++i)
   {
      for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
      {
         m_Dack.Deal(*pPlayer);
      }
      m_Dack.Deal(m_House);
   }
   m_House.FlipFirstCard();                                                 //прячем первую карту дилера
   for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) //открываем руки всех игроков
   {
      cout << *pPlayer << endl;
   }
   cout << m_House << endl;
   for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) //раздача доп карт
   {
      m_Dack.AdditionalCards(*pPlayer);
   }
   m_House.FlipFirstCard(); //показываем первую карту дилера
   cout << endl
        << m_House;
   m_Dack.AdditionalCards(m_House); // раздача доп карты дилеру
   if (m_House.IsBusted())
   {
      for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) //все кто остался в игре побеждают
      {
         if (!(pPlayer->IsBusted()))
         {
            pPlayer->Win();
         }
      }
   }
   else
   {
      for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) // сравнение суммы всех очков игрока и диллера
      {
         if (!(pPlayer->IsBusted()))
         {
            if (pPlayer->GetTotal() > m_House.GetTotal())
            {
               pPlayer->Win();
            }
            else if (pPlayer->GetTotal() < m_House.GetTotal())
            {
               pPlayer->Lose();
            }
            else
            {
               pPlayer->Draw();
            }
         }
      }
   }
   for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) // очистка рук всех игроков
   {
      pPlayer->Clear();
   }
   m_House.Clear();
}
//ostream &operator<<(ostream &os, const Card &aCard); prototip

ostream &operator<<(ostream &os, const Card &aCard)
{
   const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
   const string SUITS[] = {"c", "d", "h", "s"};
   if (aCard.m_IsFaceUp)
   {
      os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
   }
   else
   {
      os << "XX";
   }
   return os;
}

//ostream &operator<<(ostream &os, const GenericPlayer &aGenericPlayer);  proyotip
ostream &operator<<(ostream &os, const GenericPlayer &aGenericPlayer)
{
   os << aGenericPlayer.m_Name << ":\t";
   vector<Card *>::const_iterator pCard;
   if (!aGenericPlayer.m_Cards.empty())
   {
      for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard)
      {
         os << *(*pCard) << "\t";
      }
      if (aGenericPlayer.GetTotal() != 0)
      {
         cout << "(" << aGenericPlayer.GetTotal() << ")";
      }
   }
   else
   {
      os << "<empty>";
   }
   return os;
}

int main()
{
   cout << "Welcome to BlackJack!" << endl;
   int numPlayers = 0;
   while (numPlayers < 1 || numPlayers > 7)
   {
      cout << "How many players to play? (1-7): ";
      cin >> numPlayers;
   }
   vector<string> names;
   string name;
   for (int i = 0; numPlayers; ++i)
   {
      cout << "Enter player name: ";
      cin >> name;
      names.push_back(name);
   }
   cout << endl;

   Game aGame(names);
   char again = 'y';
   while (again != 'n' && again != 'N')
   {
      aGame.Play();
      cout << "\nDo you want to play again? (Y/N): ";
      cin >> again;
   }
   return 0;
}
