#pragma once
#include <functional>
#include "Utils/State.h"
#include "Utils/GameMode.h"

////////////////////////////////////////////////////////////
// Klasa odpowiedzialna za plansz�.
////////////////////////////////////////////////////////////
class Board {
public:
	Board(int, GameMode, Difficulty = Difficulty::HARD);

	////////////////////////////////////////////////////////////
	// Zwraca warto�� planszy na pozycji `x`, `y`.
	////////////////////////////////////////////////////////////
	State getAt(int x, int y);

	////////////////////////////////////////////////////////////
	// Ustawia warto�� planszy na pozycji `x`, `y` jako `state`.
	////////////////////////////////////////////////////////////
	void setAt(int x, int y, State state);

	////////////////////////////////////////////////////////////
	// Zwraca rozmiar planszy. Dla planszy 3x3 zostanie 
	// zwr�cona warto�� 3.
	////////////////////////////////////////////////////////////
	int getSize();

	////////////////////////////////////////////////////////////
	// Zwraca obecny tryb gry.
	////////////////////////////////////////////////////////////
	GameMode getGameMode();

	////////////////////////////////////////////////////////////
	// Zwraca `State::X` lub `State::O` w zale�no�ci od tego,
	// czyj ruch jest obecnie.
	////////////////////////////////////////////////////////////
	State getCurrentPlayer();

	////////////////////////////////////////////////////////////
	// Zwraca `true` jedynie, gdy gra zosta�a zako�czona 
	// wygran� lub remisem.
	////////////////////////////////////////////////////////////
	bool isComplete();

	////////////////////////////////////////////////////////////
	// Wykonuje ruch w zale�no�ci od wybranego poziomu 
	// trudno�ci.
	////////////////////////////////////////////////////////////
	void makeMove();

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� funkcj�, kt�ra zostanie wywo�ana, gdy
	// gra zostanie zako�czona.
	////////////////////////////////////////////////////////////
	void setOnCompleteListener(std::function<void(State)>);

	////////////////////////////////////////////////////////////
	// Pozwala zresetowa� plansz�.
	// Ustawia wszystkie pola na `State::NONE`.
	////////////////////////////////////////////////////////////
	void reset();

private:
	////////////////////////////////////////////////////////////
	// Sprawdza czy podana plansza jest kompletna. Je�eli jest
	// remis zwracana warto�� to `State::TIE`, je�eli wygra�
	// gracz z k�lkiem to - `State::O`, natomaist dla gracza
	// z iksem - `State::X`.
	////////////////////////////////////////////////////////////
	State checkComplete(std::vector<State>);

	////////////////////////////////////////////////////////////
	// Wykonuje ruch na podstawie wylosowanej pozycji z 
	// dost�pnych.
	////////////////////////////////////////////////////////////
	void makeEasyMove();

	////////////////////////////////////////////////////////////
	// Je�eli na planszy znajduje si� rz�d danego gracza, to
	// algorytm go zablokuje albo wykona ruch, kt�ry pozwoli
	// mu wygra�. Natomiast, gdy nie ma takiej mo�liwo�ci, 
	// wylosuje pozycj� z dost�pnych.
	////////////////////////////////////////////////////////////
	void makeMediumMove();

	////////////////////////////////////////////////////////////
	// Algorytm `minimax` do analizowania planszy i 
	// znaleznienia najlepszego ruchu.
	////////////////////////////////////////////////////////////
	void makeHardMove();

	////////////////////////////////////////////////////////////
	// Zwraca liczb� tych samych p�l w rz�dzie dla rz�du `y`.
	////////////////////////////////////////////////////////////
	int countHorizontally(std::vector<State>, int y, State, int&);

	////////////////////////////////////////////////////////////
	// Zwraca liczb� tych samych p�l w kolumnie dla kolumny `x`.
	////////////////////////////////////////////////////////////
	int countVertically(std::vector<State>, int x, State, int&);

	////////////////////////////////////////////////////////////
	// Zwraca liczb� tych samych p�l dla przek�tnej.
	// Je�eli `left` jest r�wne `true`, to sprawdzana b�dzie
	// przek�tna z lewego g�rnego rogu.
	////////////////////////////////////////////////////////////
	int countDiagonally(std::vector<State>, bool left, State, int&);

	////////////////////////////////////////////////////////////
	// Algorytm rekurencyjny do znajdowania najbardziej 
	// op�acalnego miejsca na kolejny ruch.
	////////////////////////////////////////////////////////////
	int minimax(std::vector<State>, bool, int, int);

private:
	int size;
	GameMode gameMode;
	Difficulty difficulty;
	std::vector<State> map;
	State currentPlayer;

	bool complete;

	std::function<void(State)> onCompleteListener;
};