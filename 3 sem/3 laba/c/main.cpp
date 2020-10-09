#include "gtest/gtest.h"
#include "Card.h"
#include "Deck.h"
#include "Dialog.h"

using namespace laba3;

int main(int argc, char* argv[])
{	
	Deck a1 = Deck(1);         //конст перемещения
	Deck a2 = a1;       //конст копирование
	a2 = Deck(1);       //опер  перемещающий
	a2 = a1;            //опер  перемещения
	Deck deck(0);
	start_dialog(deck);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}