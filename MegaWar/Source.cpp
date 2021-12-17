#include<iostream>
#include<vector>
#include<algorithm>
#include <Windows.h>
#include<string>
#include<iomanip>
using namespace std;

enum class Suits {club, diamond, heart, spade };
enum class Rank {
	Ace = 1,
	Two = 2, 
	Three = 3, 
	Four = 4,
	Five = 5,
	Six = 6, 
	Seven = 7, 
	Eight = 8, 
	Nine = 9, 
	Ten = 10,
	Jack = 11,
	Queen = 12,
	King = 13
};
class Cards {
	Rank rank;
	Suits suit;
public:
	Cards()
	{

	}
	Cards(Rank r, Suits s)
	{
		rank = r;
		suit = s;
	}
	int getrank()
	{
		int i = static_cast<int>(rank);
		return i;
	}
	Suits getsuit()
	{
		return suit;
	}
	void displaycard()
	{
		if (static_cast<int>(rank) >= 1 && static_cast<int>(rank) <= 10)
		{
			cout << static_cast<int>(rank);
		}
		if (static_cast<int>(rank) == 11)
		{
			cout << " Jack ";
		}
		if (static_cast<int>(rank) == 12)
		{
			cout << " Queen ";
		}
		if (static_cast<int>(rank) == 13)
		{
			cout << " King ";
		}
		if (suit == Suits::club)
		{
			cout << " of Clubs" ;
		}
		if (suit == Suits::diamond)
		{
			cout << " of Diamonds"  ;
		}
		if (suit == Suits::heart)
		{
			cout << " of Hearts"  ;
		}
		if (suit == Suits::spade)
		{
			cout << " of Spades" ;
		}
	}
};
class Deck {
protected:
	vector<Cards> deck;
public:
	void addcard(Cards c)
	{
		deck.push_back(c);
	}
	Cards removecard()
	{
		Cards card = deck.front();
		deck.erase(deck.begin());
		return card;
	}
	void shuffle(){
		random_shuffle(deck.begin(), deck.end());
	}
	int getNumberOfCards()
	{
		return deck.size();
	}
	void display()
	{
		int a = deck.size();
		for (int i = 0; i <a; i++)
		{
			deck[i].displaycard();
			cout << endl;
		}
	}
};
class MegaDeck {
	vector<Deck> megadeck;
	//vector<Player> players;
public:
	void adddecks(Deck d)
	{
		megadeck.push_back(d);
	}
	Deck removedeck()
	{
		Deck deck = megadeck[megadeck.size() - 1];
		megadeck.pop_back();
		return deck;
	}
	void displaydeck()
	{
		for (int i = 0; i < megadeck.size(); i++)
		{
			cout << "-----------Deck "<<i+1<<"--------------" << endl;
			megadeck[i].display();
		}
	}
};
class Player : public Deck {
	int no,battles, won;
public:
	Cards placeCard()
	{
		Cards card = removecard();
		return card;
	}
	double Fierceness()
	{
		double sum = 0,average;
		if (deck.size() == 0)
		{
			return 0.0;
		}
		for (int i = 0; i < deck.size(); i++)
		{
			sum += deck[i].getrank();
		}
		return (average = sum / deck.size());
	}
	void setno(int n)
	{
		no = n;
	}
	void setBattles()
	{
		battles++;
	}
	void setWon()
	{
		won++;
	}
	int getno()
	{
		return no;
	}
	int getBattles()
	{
		return battles;
	}
	int getWon()
	{
		return won;
	}
	int getdecksize()
	{
		return deck.size();
	}
};
class LostandFound : public Deck {

};
class Wardeck : public Deck {
	vector<Cards> cardthatmatter;
	vector<Player*> war;
public:
	/*vector<Cards> getdeck()
	{
		return deck;
	}
	vector<Cards> getcardthatmatter()
	{
		return cardthatmatter;
	}
	vector<Player*> getwar()
	{
		return war;
	}*/
	int getcardsize()
	{
		return cardthatmatter.size();
	}
	int getwarsize()
	{
		return war.size();
	}
	void eraseelement(int a)
	{
		war.erase(war.begin() + a);
	}
	void clearwar()
	{
		war.clear();
	}
	void addcardthatmatter(Cards c)
	{
		cardthatmatter.push_back(c);
	}
	Cards removecardthatmatter()
	{
		Cards card = cardthatmatter.front();
		cardthatmatter.erase(cardthatmatter.begin());
		return card;
	}
	void addplayer(Player* p)
	{
		war.push_back(p);
	}
	Player* removeplayer()
	{
		Player* p = war[war.size() - 1];
		war.pop_back();
		return p;
	}
	bool determineWarsWinner(LostandFound lf)
	{
		int max = cardthatmatter[0].getrank(), index = 0, count = 0;
		for (int i = 0; i < cardthatmatter.size(); i++)
		{
			if (max < cardthatmatter[i].getrank())
			{
				max = cardthatmatter[i].getrank();
			}
		}
		for (int j = 0; j < cardthatmatter.size(); j++)
		{
			if (max == cardthatmatter[j].getrank())
			{
				index = j;
				count++;
			}
		}
		if (count == 1)
		{
			cout << "Winner of the war is Player " << war[index]->getno() << endl;
			war[index]->setWon();
			setWinnerCards(war[index],lf);
			return true;
		}
		else
		{
			cout << "War Tied between ";
			return false;
		}
	}
	bool determineWarWinner(LostandFound lf)
	{
		int max = deck[0].getrank(),index=0,count=0;
		for (int i = 0; i < deck.size(); i++)
		{
			if (max < deck[i].getrank())
			{
				max = deck[i].getrank();
			}
		}
		for (int j = 0; j < deck.size(); j++)
		{
			if (max == deck[j].getrank())
			{
				index = j;
				count++;
			}
		}
		if (count == 1)
		{
			cout << "Winner of the war is Player " << war[index]->getno() << endl;
			war[index]->setWon();
			setWinnerCards(war[index],lf);
			return true;
		}
		else
		{
			cout << "War Tied between ";
			return false;
		}
	}
	void setWinnerCards(Player*& p, LostandFound lf)
	{
		for (int i = 0; i < deck.size(); i++)
		{
			p->addcard(deck[i]);
		}
		if (cardthatmatter.size() > 0)
		{
			for (int i = 0; i < cardthatmatter.size(); i++)
			{
				p->addcard(cardthatmatter[i]);
			}
		}
		if (lf.getNumberOfCards() > 0)
		{
			cout << "You also get all the cards in the lost and find pile" << endl;
			for (int m = 0; m < lf.getNumberOfCards(); m++)
			{
				p->addcard(lf.removecard());
			}
		}
		deck.resize(0);
		cardthatmatter.resize(0);
	}
	vector<int> getTiedPlayers()
	{
		int max = deck[0].getrank();
		vector<int> players;
		for (int i = 0; i < deck.size(); i++)
		{
			if (max < deck[i].getrank())
			{
				max = deck[i].getrank();
			}
		}
		for (int j = 0; j < deck.size(); j++)
		{
			if (max == deck[j].getrank())
			{
				players.push_back(war[j]->getno());
			}
		}
		return players;
	}
};
void Creating_Decks(MegaDeck &md, int number_of_decks, int number_of_players)
{
	int index = 0, count = 0;
	Deck* d;
	Cards* c;
	Suits s[4] = { Suits::club, Suits::diamond, Suits::heart, Suits::spade };
	for (int i = 0; i < number_of_decks; i++)
	{
		index = 0, count = 0;
		d = new Deck();
		for (int j = 1; j <= 14; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 13 == 1 && j != 1)
				{
					count++;
					index++;
					j = 1;
				}
				if (count == 4)
				{
					break;
				}
				c = new Cards(static_cast<Rank>(j), s[index]);
				d->addcard(*c);
			}
			else
			{

				if (j % 13 == 1 && j != 1)
				{
					count++;
					index += 2;
					j = 1;
				}
				if (count == 2)
				{
					index = 1;
				}
				if (count == 4)
				{
					break;
				}
				c = new Cards(static_cast<Rank>(j), s[index]);
				d->addcard(*c);
			}
		}
		d->shuffle();
		md.adddecks(*d);
	}
	//md.displaydeck();
}
void AssigningDecks(MegaDeck &md,vector<Player> &players,int number_of_decks, int number_of_players)
{
	int total_cards = 52 * number_of_decks;
	int equal = total_cards / number_of_players;
	int counter = 0, remaining = total_cards - (equal*number_of_players), p_index = 0, cards = 0;
	Deck d;
	while (remaining % number_of_players > 0)
	{
		if (remaining < number_of_players)
		{
			break;
		}
		remaining--;
	}
	equal += remaining / number_of_players;
	for (int y = 0; y < number_of_decks; y++)
	{
		if (cards == (equal * number_of_players))
		{
			break;
		}
		d = md.removedeck();
		for (int j = 0; j < 52; j++)
		{
			if (cards == (equal * number_of_players))
			{
				break;
			}
			if (counter == equal)
			{
				counter = 0;
				p_index++;
			}
			players[p_index].addcard(d.removecard());
			cards++;
			counter++;
		}
	}
	/*for (int i = 0; i < players.size(); i++)
	{
		cout << "Player " << players[i].getno() <<":: "<< endl;
		players[i].display();
	}*/
}
void PlayGame(vector<Player>& players)
{
	Wardeck war;
	LostandFound lf;
	vector<int> tiedplayers,index2;
	int no_of_players = players.size() - 1, choice, index, no_of_wars = 0,count=0,nooo;
	char s;
	bool flag =true,is_war=false;
	Suits suits = Suits::club;
	Cards cc;
	while (no_of_players > 0)
	{
		war.clearwar();
		no_of_wars = 0;
			for (int i = 0; i < players.size(); i++) // for simple battle
			{
				cout << "-------------------Player " << players[i].getno() << " turn your Cards are--------------------- " << endl;
				if (players[i].getNumberOfCards() == 0) // if player run out of cards
				{
					cout << "Looks like you ran out of cards!!!! OOPS u lost" << endl;
					no_of_players--;
					players.erase(players.begin() + i);
					if (i != players.size())
					{
						i--;
					}
					getchar();
					continue;
				}
				players[i].display();
				cc = players[i].removecard();
				cout << endl <<"Placing the top card ";
				cc.displaycard();
				cout << endl << endl;
				war.addcard(cc);
				war.addplayer(&players[i]);
				players[i].setBattles();
				cin.ignore();
				getchar();
			}
	     do{ // for war
			 if (no_of_wars == 0)
			 {
				 if (war.determineWarWinner(lf)) // if no war occur
				 {
					
					cout << "War Ended" << endl;
					is_war = false;
					continue;
				 }
			 }
			 else
			 {
				 if (war.determineWarsWinner(lf)) // when war occur
				 {
					cout << "War Ended" << endl;
					is_war = false;
					continue;
				 }
			 }
			 // if war occur
			 no_of_wars = 1;
			 is_war = true;
				tiedplayers = war.getTiedPlayers(); // getting the players which will go to war
				for (int o = 0; o < tiedplayers.size(); o++)
				{
					cout << "Player " << tiedplayers[o]<<endl;
				}
				index = 0;
				for (int l = 0; l < players.size(); l++) // removing the players who are not in war 
				{
					if (index == tiedplayers.size())
					{
						break;
					}
					nooo = tiedplayers[index];
					if (nooo == players[l].getno())
					{
						index++;
					}
					else
					{
						
							war.eraseelement(l);
					}
				}
				for (int i = 0; i < tiedplayers.size(); i++) // comencing war
				{
					if (players[i].getdecksize() > 3) // if player can take part in the war
					{
						cout << "-------------------Player " << tiedplayers[i] << " turn your Cards are--------------------- " << endl;
						players[i].display();
						for (int co = 0; co < 4; co++)
						{
							
								cc = players[i].removecard();
								cout << endl << "Placing the " << co + 1 << " card ";
								cc.displaycard();
								cout << endl << endl;
								if (co == 3)
								{
									war.addcardthatmatter(cc);
									continue;
								}
								war.addcard(cc);
							
						}
						players[i].setBattles();
					}
					else // if cant take part in the war
					{
						cout << "You are not able to compete in the war as you have less than 4 cards left" << endl;
						index2.push_back(i);
					}
					getchar();
				}
				for (int e = 0; e < index2.size(); e++) // removing the ones that cant take part in the war
				{
					war.eraseelement(index2[e]);
					tiedplayers.erase(tiedplayers.begin() + index2[e]);
				}
				if (war.getwarsize() == 0 && tiedplayers.size() == 0)
				{
					for (int m = 0; m < war.getNumberOfCards(); m++)
					{
						lf.addcard(war.removecard());
					}
					for (int m = 0; m < war.getcardsize();m++)
					{
						lf.addcard(war.removecardthatmatter());
					}
				}
		 } while (is_war); // war continues
		 count++;
		 cout << "Battle " << count << " stats :: " << endl;
		 for (int a = 0; a < players.size(); a++)
		 {
			 cout << "Player " << players[a].getno() << ":: Fierceness = " <<left<< setw(10) << players[a].Fierceness() << " Cards = " << left << setw(3) << players[a].getNumberOfCards();
			 cout << " Battles = " << left << setw(3) << players[a].getBattles() << left << setw(3) << " Won = " << players[a].getWon() << endl;
		 }
		 getchar();
	}
	cout << "Congratulations Player " << players[0].getno() << "!!!!!!!! You won " << endl;
}
int main()
{
	int number_of_decks, number_of_players,total_cards;
	vector<Player> players;
	MegaDeck md;
	Player* p;
	cout << "Welcome to Mega war game please enter the number of decks and number of players respectively" << endl;
	cin>> number_of_decks >> number_of_players;
	for (int k = 0; k < number_of_players; k++)
	{
		p = new Player();
		p->setno(k + 1);
		players.push_back(*p);
	}
	Creating_Decks(md, number_of_decks, number_of_players);
	AssigningDecks(md, players, number_of_decks, number_of_players);
	PlayGame(players);
}