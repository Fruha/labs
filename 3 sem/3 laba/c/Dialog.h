#pragma once
#include "Deck.h"
#include "Card.h"

namespace laba3 
{
	void start_dialog(Deck&);
	void menu_add_card(Deck&);
	void menu_print_deck(Deck&);
	void menu_add_new_random_card(Deck&);
	void menu_get_card(Deck&);
	void menu_sort(Deck&);
	void menu_find_by_suit(Deck&);
	void menu_delete_card(Deck&);
	int input_choise(const char* msgs[], int N);
	void dialog(Deck&, int);
}




