#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{

	cout << "Welcome to UNO!" << endl;

	int i, dummyvariable, timer; //index
	string player_name;

	bool win = false;

	bool draw_two_cards_bool = false;
	bool draw_WILD_FOUR_PLUS_bool = false;
	bool draw_WILD_bool = false;
	bool SKIP_bool = false;
	bool REVERSE_bool = false;







	Deck UNOdeck;
	vector<Player> player(getNumOfPlayers());  //array of players to play

	system("CLS");

	UNOdeck.shuffleDeck();

	for (i = 0; i < player.size(); i++) //set player id and draw cards
	{

		cout << "Please enter a name" << endl;
		cin >> player_name;

		player[i].setPlayerID(player_name); //array indexing starts from zero
		player[i].drawStartingHand(UNOdeck); //7 cards at start of game
	} i = 0; //reference to the first player upon incrementation

	shufflePlayers(player); //de2cide which player will go first
	cout << player[0].getPlayerID() << " will go first" << endl << endl;
	this_thread::sleep_for(chrono::seconds(1));


	system("CLS");


	setInitialCardToPile(UNOdeck); // set first card to pile to start

	FirstPileCardEffect(player, UNOdeck, i);

	//begin index

	while (win == false)
	{
		if (i >= player.size())
		{
			i = 0;
		}

		
		for (timer = 3; timer > -1; timer--)
		{
			cout << timer << " seconds...\r"; 
			this_thread::sleep_for(chrono::seconds(1));
			
		}

		drawTwoCards(player, UNOdeck, i, draw_two_cards_bool);
		drawWildFourPlus(player, UNOdeck, i, draw_WILD_FOUR_PLUS_bool);
		reversePlayers(player, UNOdeck, i, REVERSE_bool);
		skipPlayer(player, UNOdeck, i, SKIP_bool);

		cout << "Please pass the display to " << player[i].getPlayerID() << " game will resume in" << endl;


		if (i >= player.size())
		{
			i = 0;
		}

		displayPlayerMenu(player, UNOdeck, i); //fix bug issue with when player draws a card but has no option
		runTurn(player, UNOdeck, i);

		checkforWild(UNOdeck);
		draw_WILD_FOUR_PLUS_bool = checkforWildFour(player, UNOdeck, i); //possible issue 
		REVERSE_bool = checkforReverse(player, UNOdeck);
		SKIP_bool = checkforSkip(player, UNOdeck, i);
		draw_two_cards_bool = checkforDrawTwo(player, UNOdeck, i);

		win = checkWin(player);

		i++;
		system("CLS");
	}
}


int Game::getNumOfPlayers() 
{

	int num_players = 0; //initalize
	bool flag = false;

	while (flag == false)
	{
		cout << "Choose between 2-10 players" << endl;
		cin >> num_players;
		switch (num_players) {
		case 2:
			flag = true;
			break;
		case 3:
			flag = true;
			break;
		case 4:
			flag = true;
			break;
		case 5:
			flag = true;
			break;
		case 6:
			flag = true;
			break;
		case 7:
			flag = true;
			break;
		case 8:
			flag = true;
			break;
		case 9:
			flag = true;
			break;
		case 10:
			flag = true;
			break;
		default: cout << "Enter a valid number" << endl;
		}
	}
	return num_players;
}

void Game::shufflePlayers(vector<Player> &playerlist)
{
	srand(time(0));
	random_shuffle(playerlist.begin(), playerlist.end());
}

void Game::setInitialCardToPile(Deck &deckptr) //begin game
{
	deckptr.setFirstCardToPile();
	cout << "The top deck card has been added to the pile to start the game" << endl;
}

void Game::deletePlayer(vector<Player> &player, int i)
{
	player.erase(player.begin() + i);
}

void Game::runTurn(vector<Player> &playerptr, Deck &deckptr, int i)
{
	int user_choice;
	bool flag = false;

	cout << "Its  " << playerptr[i].getPlayerID() << " 's turn" << endl;

	while (flag == false) 
	{
		cout << "What would you like to do? " << endl;
		cout << "0. Choose Card to drop to discard pile" << endl;
		cout << "1. Do Nothing and Draw a Card" << endl;
		//cout << "2. Surrender" << endl;

		cin >> user_choice;

		switch (user_choice)
		{
		case 0:
			playerptr[i].dropCardIntoPile(deckptr, flag);
			break;

		case 1:

			playerptr[i].drawCard(deckptr);
			displayPlayerMenu(playerptr, deckptr, i);
			playerptr[i].dropCardIntoPile(deckptr, flag);
			flag = true;
			break;

		//case 2:
		//	cout << "Player " << playerptr[i].getPlayerID() << "has left the game" << endl;
		//	deletePlayer(playerptr, i);
		//	flag = true;
		//break;

		default:
			cout << "Please enter a valid selection" << endl;
			break;
		}
	}

}

void Game::FirstPileCardEffect(vector<Player> &player, Deck &deckptr, int &iptr) 
{

	while(deckptr.getPile().back().getCardType() == "WILD_DRAW_FOUR")
	{
		cout << "The First Pile card was a wild draw four so the deck has to be reshuffled and a new card placed in the pile" << endl;
		deckptr.restackDeck();
	}

	if (deckptr.getPile().back().getCardType() == "WILD") //wild
	{
		string choosecolor;
		bool flag = false;

		cout << "The First Pile card was a wild card, Select a color to pick" << endl;

		while (flag == false)
		{
			cin >> choosecolor;
			transform(choosecolor.begin(), choosecolor.end(), choosecolor.begin(), ::toupper);

			if (choosecolor == "BLUE") { deckptr.setWildCardColor("BLUE"); flag = true; }
			else if (choosecolor == "RED") { deckptr.setWildCardColor("RED"); flag = true; }
			else if (choosecolor == "GREEN") { deckptr.setWildCardColor("GREEN"); flag = true; }
			else if (choosecolor == "YELLOW") { deckptr.setWildCardColor("YELLOW"); flag = true; }
			else
			{
				cout << "Please enter a valid color" << endl;
			}


			//reset display

		}

		cout << "You have chosen " << choosecolor << ". Please wait...." << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	else if (deckptr.getPile().back().getCardType() == "DRAW_TWO")
	{
		cout << "The Pile was a draw two so " << player[0].getPlayerID() << " has to draw two cards" << endl;

		player[0].drawCard(deckptr);
		player[0].drawCard(deckptr);

		this_thread::sleep_for(chrono::milliseconds(500));
	}

	else if (deckptr.getPile().back().getCardType() == "REVERSE")
	{
		cout << "The player sequence has been reversed" << endl;

		reverse(player.begin(), player.end());

		this_thread::sleep_for(chrono::milliseconds(500));
	}

	else if (deckptr.getPile().back().getCardType() == "SKIP")
	{
		cout << player[iptr].getPlayerID() << " has been skipped" << endl;
		iptr = ++iptr;

		this_thread::sleep_for(chrono::milliseconds(500));
	}

	else { ; }

}

bool Game::checkWin(vector<Player> player)
{
	int x;
	for (x = 0; x < player.size(); x++)
	{
		switch (player[x].getHand().size()) {

		case 0:
			cout << "Winner winner chicken dinner, "<< player[x].getPlayerID() << " is the winner";

			this_thread::sleep_for(chrono::seconds(3));


			return true;

		default:
			break;
		}
	}

	return false; //no winner

}

void Game::checkforWild(Deck &deckptr)
{

	if (deckptr.getPile().back().getCardType() == "WILD")
	{
		string choosecolor;
		bool flag = false;

		cout << "Select a color to pick" << endl;

		while (flag == false)
		{
			cin >> choosecolor;
			transform(choosecolor.begin(), choosecolor.end(), choosecolor.begin(), ::toupper);

			if (choosecolor == "BLUE") { deckptr.setWildCardColor("BLUE"); flag = true; }
			else if (choosecolor == "RED") { deckptr.setWildCardColor("RED"); flag = true; }
			else if (choosecolor == "GREEN") { deckptr.setWildCardColor("GREEN"); flag = true; }
			else if (choosecolor == "YELLOW") { deckptr.setWildCardColor("YELLOW"); flag = true; }
			else
			{
				cout << "Please enter a valid color" << endl;
			}

		}

		cout << "You have chosen " << choosecolor << ". Please wait...." << endl ;
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	else { ; }
}

bool Game::checkforWildFour(vector<Player> &player, Deck &deckptr, int &iptr) {


	if (deckptr.getPile().back().getCardType() == "WILD_DRAW_FOUR")
	{
		string choosecolor;
		bool flag = false;

		cout << "Select a color to pick" << endl;

		while (flag == false)
		{
			cin >> choosecolor;
			transform(choosecolor.begin(), choosecolor.end(), choosecolor.begin(), ::toupper);

			if (choosecolor == "BLUE") { deckptr.setWildCardColor("BLUE"); flag = true; }
			else if (choosecolor == "RED") { deckptr.setWildCardColor("RED"); flag = true; }
			else if (choosecolor == "GREEN") { deckptr.setWildCardColor("GREEN"); flag = true; }
			else if (choosecolor == "YELLOW") { deckptr.setWildCardColor("YELLOW"); flag = true; }
			else
			{
				cout << "Please enter a valid color" << endl;
			}

		}

		cout << "You have chosen " << choosecolor << ". Please wait...." << endl;
		this_thread::sleep_for(chrono::milliseconds(500));


		return true;
	}

	else { return false; }
}

bool Game::checkforDrawTwo(vector<Player> &player, Deck &deckptr, int &iptr)
{

	if (deckptr.getPile().back().getCardType() == "DRAW_TWO")
	{
		return true;
	}

	else { return false; }

}

bool Game::checkforReverse(vector<Player> &player, Deck &deckptr) {


	if (deckptr.getPile().back().getCardType() == "REVERSE")
	{
		return true;
	}

	else { return false; }
}

bool Game::checkforSkip(vector<Player> &player, Deck &deckptr, int &iptr) {

	if (deckptr.getPile().back().getCardType() == "SKIP")
	{
		return true;
	}

	else { return false; }
}



void Game::drawWildFourPlus(vector<Player> &player, Deck &deckptr, int &iptr, bool flag) 
{

	if (flag == true)
	{
		cout << player[iptr].getPlayerID() << "draws 4 cards" << endl;

		player[iptr].drawCard(deckptr);  
		player[iptr].drawCard(deckptr);
		player[iptr].drawCard(deckptr);
		player[iptr].drawCard(deckptr);
		
		this_thread::sleep_for(chrono::milliseconds(500));

	}

	else {;}

}





void Game::drawTwoCards(vector<Player> &player, Deck &deckptr, int &iptr, bool flag)
{
	if (flag == true)
	{
		cout << player[iptr].getPlayerID() << "draws 2 cards" << endl;


		player[iptr].drawCard(deckptr);
		player[iptr].drawCard(deckptr);

		this_thread::sleep_for(chrono::milliseconds(500));

	}

	else { ; }


}

void Game::reversePlayers(vector<Player> &player, Deck &deckptr, int &iptr, bool flag) 
{
	if (flag == true)
	{
		cout << "Players have been reversed" << endl;
		reverse(player.begin(), player.end());
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	else { ; }
}

void Game::skipPlayer(vector<Player> &player, Deck &deckptr, int &iptr, bool flag)
{

	if (flag == true)
	{
		cout << player[iptr].getPlayerID() << " has been skipped" << endl;
		iptr = ++iptr;
		this_thread::sleep_for(chrono::milliseconds(500));

	}
	else { ; }
	
}		

void Game::displayOtherPlayersHands(vector<Player> player, Deck deckptr, int iptr) {

	int x, y;

	cout << "These are other player's hands" << endl;

	for (y = 0; y < player.size(); y++)
	{
		cout << player[y].getPlayerID() << " 's hand";

		for (x = 0; x < player[y].getHand().size(); x++)
		{
			if (y == iptr)
			{
				break;
			}
			cout << "X";
		}

		cout << endl;
	}
	cout << endl;
}

void Game::displayPlayerMenu(vector<Player> player, Deck deckptr, int iptr) 
{
	system("CLS");
	displayOtherPlayersHands(player, deckptr, iptr);
	deckptr.showPile();
	player[iptr].showHand();
}