#include "gtest/gtest.h"
#include "Card.h"
#include "Deck.h"

using namespace laba3;

TEST(CardConstructor, DefaultConstructor)
{
	Card a1;
	ASSERT_EQ("0", a1.get_rang_str());
	ASSERT_EQ(0, a1.get_rang_int());
	ASSERT_EQ('0', a1.get_suit_ch());
	ASSERT_EQ(0, a1.get_suit_int());
}
TEST(CardConstructor, InitConstructors)
{
	Card a1('S', "10");
	ASSERT_EQ("10", a1.get_rang_str());
	ASSERT_EQ(10, a1.get_rang_int());
	ASSERT_EQ('S', a1.get_suit_ch());
	ASSERT_EQ(1, a1.get_suit_int());
	Card a2('H', 3);
	ASSERT_EQ("3", a2.get_rang_str());
	ASSERT_EQ(3, a2.get_rang_int());
	ASSERT_EQ('H', a2.get_suit_ch());
	ASSERT_EQ(2, a2.get_suit_int());
	Card a3(3, "K");
	ASSERT_EQ("K", a3.get_rang_str());
	ASSERT_EQ(13, a3.get_rang_int());
	ASSERT_EQ('C', a3.get_suit_ch());
	ASSERT_EQ(3, a3.get_suit_int());
	Card a4(4, 14);
	ASSERT_EQ("A", a4.get_rang_str());
	ASSERT_EQ(14, a4.get_rang_int());
	ASSERT_EQ('D', a4.get_suit_ch());
	ASSERT_EQ(4, a4.get_suit_int());
}
TEST(CardConstructor, TestException)
{
	ASSERT_ANY_THROW(Card('E', "10"));
	ASSERT_ANY_THROW(Card('H', 15));
	ASSERT_ANY_THROW(Card(-1, "10"));
	ASSERT_ANY_THROW(Card(5, 11));
}
TEST(CardMethods, Setters)
{
	Card a1;
	a1.set_suit_int(1);
	ASSERT_EQ('S', a1.get_suit_ch());
	ASSERT_EQ(1, a1.get_suit_int());
	a1.set_rang_str("10");
	ASSERT_EQ("10", a1.get_rang_str());
	ASSERT_EQ(10, a1.get_rang_int());
	Card a2;
	a2.set_suit_ch('D');
	ASSERT_EQ('D', a2.get_suit_ch());
	ASSERT_EQ(4, a2.get_suit_int());
	a2.set_rang_int(14);
	ASSERT_EQ("A", a2.get_rang_str());
	ASSERT_EQ(14, a2.get_rang_int());
	Card a3(4, 14);
	ASSERT_ANY_THROW(a3.set_rang_int(-1));
	ASSERT_ANY_THROW(a3.set_rang_str("E"));
	ASSERT_ANY_THROW(a3.set_suit_int(-1));
	ASSERT_ANY_THROW(a3.set_suit_ch('R'));
}
TEST(CardMethods, Parameters)
{
	Card a1(1, 3);
	Card a2(1, 3);
	Card a3(3, 4);
	Card a4(2, 13);
	Card a5(1, 2);
	ASSERT_EQ(0, a1.compare(a2, 0));
	ASSERT_EQ(2, a1.compare(a3, 0));
	ASSERT_EQ(1, a1.compare(a3, 1));
	ASSERT_EQ(1, a1.compare(a4, 1));
	ASSERT_EQ(-1, a1.compare(a5, 1));
	ASSERT_EQ(14, a1.rang_str_to_int("A"));
	ASSERT_EQ("10", a1.rang_int_to_str(10));
	ASSERT_EQ(1, a1.suit_ch_to_int('S'));
	ASSERT_EQ('S', a1.suit_int_to_ch(1));
}
////////////////////////////////////////////////////
TEST(DeckConstructor, DefaultConstructor)
{
	Deck a1;
	ASSERT_EQ(0, a1.get_len());
}
TEST(DeckConstructor, InitConstructors)
{
	Deck a1(Card(1,2));
	ASSERT_EQ(1, a1.get_card(0).get_suit_int());
	ASSERT_EQ(2, a1.get_card(0).get_rang_int());
	Deck a2(a1);
	ASSERT_EQ(1, a2.get_card(0).get_suit_int());
	ASSERT_EQ(2, a2.get_card(0).get_rang_int());
}
TEST(DeckConstructor, TestException)
{
	ASSERT_ANY_THROW(Deck(-1));
	ASSERT_ANY_THROW(Deck(53));
}
TEST(DeckMethods, Setters)
{
	Deck a1;
	Card temp(2, 2);
	a1.set_card(temp, 0);
	ASSERT_EQ(2, a1.get_card(0).get_suit_int());
	ASSERT_EQ(2, a1.get_card(0).get_rang_int());
	Deck a2;
	ASSERT_ANY_THROW(a2.set_card(temp, 2));
}
TEST(DeckMethods, Parameters)
{
	Deck a1(1);
	a1.delete_card(0);
	ASSERT_EQ(0, a1.get_card(0).get_suit_int());
	ASSERT_EQ(0, a1.get_card(0).get_rang_int());
	Deck a2;
	a2.add_new_card(Card(2, 2));
	ASSERT_EQ(2, a2.get_card(0).get_suit_int());
	ASSERT_EQ(2, a2.get_card(0).get_rang_int());
	ASSERT_EQ(0, a2.find_card(Card(2, 2)));
	a2.delete_card(Card(2, 2));
	ASSERT_EQ(0, a2.get_card(0).get_suit_int());
	ASSERT_EQ(0, a2.get_card(0).get_rang_int());
	a1.add_new_card(Card(2, 3));
	a2 = a1;
	ASSERT_EQ(2, a1.get_card(0).get_suit_int());
	ASSERT_EQ(3, a1.get_card(0).get_rang_int());
	ASSERT_EQ(3, a1[0]);
	ASSERT_EQ(3, a2[0]);
	ASSERT_EQ(2, a1(0));
	ASSERT_EQ(2, a2(0));
	Deck a3;
	++a3;
	ASSERT_FALSE(0 == a3[1]);
	ASSERT_FALSE(0 == a3(1));
}
