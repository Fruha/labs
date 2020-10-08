#pragma once
#include "util.h"
#include "card.h"

namespace laba3 
{
	class Deck 
	{
	private:
		int len;
		Card data[52];
	public:
		// init
		Deck(int = 0);
		Deck(Card);
		//get
		int get_len() const { return len; };
		Card* get_data() { return data; };
		Card get_card(const int i) const { return data[i]; };
		int find_card(const Card&) const;
		// set
		void set_card(const Card, const int i);
		// another
		int delete_card(const Card&);
		int delete_card(const int);
		//int add_new_random_card(); // 0 ok, 1 max cards
		Deck& operator++();
		int operator()(const int);
		int operator[](const int);
		int add_new_card(const Card); // 0 ok, 1 max cards, 2 already exists
		void swap(Card&, Card&);
		void sort(int = 0, int = 51);
		friend std::ostream& operator<<(std::ostream&, const Deck&);
		//void print() const;

	};
}