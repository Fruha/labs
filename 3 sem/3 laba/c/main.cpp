#include "gtest/gtest.h"
#include "Card.h"
#include "Deck.h"
#include "Dialog.h"

using namespace laba3;

int main(int argc, char* argv[])
{	
	Deck a1 = Deck(1);         //����� �����������
	Deck a2 = a1;       //����� �����������
	a2 = Deck(1);       //����  ������������
	a2 = a1;            //����  �����������
	Deck deck(0);
	start_dialog(deck);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}