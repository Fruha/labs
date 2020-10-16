#include "Dialog.h"
#include <iostream>
#include "util.h"

namespace laba3 {

	void start_dialog(Deck& deck) 
	{
		const char* msgs[] = {
			"0. Quit_and_google_tests",
			"1. Add_card",
			"2. Print_deck",
			"3. Add_new_random_card",
			"4. Get_card",
			"5. Sort",
			"6. find_by_suit",
			"7. delete_card",
		};
		int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
		int n;
		while (n = input_choise(msgs, NMsgs))
		{
			try
			{
				laba3::dialog(deck, n);
			}
			catch (...)
			{
				std::cout << "Error please repeat again" << std::endl;
			}
		}
	}

	void dialog(Deck& deck, int n) {
		std::cout << ("");
		switch (n) {
		case 1: menu_add_card(deck);
			break;
		case 2: menu_print_deck(deck);
			break;
		case 3: menu_add_new_random_card(deck);
			break;
		case 4: menu_get_card(deck);
			break;
		case 5: menu_sort(deck);
			break;
		case 6: menu_find_by_suit(deck);
			break;
		case 7: menu_delete_card(deck);
			break;
		}
	}

	void menu_add_card(Deck& deck) 
	{
		puts("S1 H2 C3 D4");
		char   suit = get_num<char>("Enter suit (char):");
		string rang = get_num<string>("Enter rang (str):");

		Card temp(suit, rang);
		int err = deck.add_new_card(temp);
		switch (err)
		{
		case 1:
			puts("Max cards");
		case 2:
			puts("Card already exists");
		}

		return;
	}

	void menu_print_deck(Deck& deck) 
	{
		cout << deck << endl;
	}

	void menu_add_new_random_card(Deck& deck) 
	{
		++deck;
		return;
	}

	void menu_get_card(Deck& deck) 
	{
		int i1 = get_num<int>("Enter number:");
		if (i1 < 0 || i1 > deck.get_len()) 
		{
			int i1 = get_num<int>("Error number (num < 0 or num > len):");
		}
		cout << deck.get_card(i1) << endl;
		return;
	}

	void menu_sort(Deck& deck) 
	{
		deck.sort();
		return;
	}

	void menu_find_by_suit(Deck& deck) 
	{
		puts("S1 H2 C3 D4");
		char suit = get_num<char>("Enter suit (char):");
		Card temp(0);
		for (int i = 0; i < deck.get_len(); i += 1)
		{
			if ((temp = deck.get_card(i)).get_suit_ch() == suit) 
			{
				cout << temp << endl;
			}
		}
	}

	void menu_delete_card(Deck& deck) 
	{
		puts("S1 H2 C3 D4");
		char   suit = get_num<char>("Enter suit (char):");
		string rang = get_num<string>("Enter rang (str):");
		Card temp(suit, rang);
		int err = deck.delete_card(temp);
		if (err) 
		{
			puts("Card not in deck");
			return;
		}
		puts("Card was deleted");
		return;
	}

	int input_choise(const char* msgs[], int N)
	{
		std::cout << std::endl << ("----------------------------------------------------------------------------------------------") << std::endl;
		char errmsg[40] = "";
		int rc = 1;
		int i;
		bool error;
		do {
			for (i = 0; i < N; ++i)
				puts(msgs[i]);
			rc = get_num<int>("Make your choice: --> ");
			error = (rc < 0 || rc >= N);
			if (error) {
				puts("You are wrong. Repeate, please!");
			}
		} while (error);
		return rc;
	}
}
