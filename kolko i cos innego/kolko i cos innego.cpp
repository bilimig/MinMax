#include <iostream>
#include <vector>

using namespace std;

class TicTacToe {
	int rozmiar;
	int to_win;
	string** board;
	string currentplayer = "kolko";
	bool is_game_ended = false;
	bool is_game_drowed = false;
	string winner = "Brak";
	int currentpossition = 0;
	void create_board() {
		is_game_ended = false;
		this->board = new string * [this->rozmiar];
		for (size_t x = 0; x < this->rozmiar; x++)
		{
			board[x] = new string[this->rozmiar];
			for (size_t y = 0; y < this->rozmiar; y++)
			{
				board[x][y] = "Puste";
			}
		}
	}

public:
	int ilepustych = rozmiar * rozmiar;
	TicTacToe() {

	}

	TicTacToe(int rozmiar, int to_win) {

		this->rozmiar = rozmiar;
		this->to_win = to_win;
		create_board();
		makemove();
	}

	TicTacToe(TicTacToe& gra)
	{
		this->rozmiar = gra.rozmiar;
		this->to_win = gra.to_win;
		this->currentplayer = gra.currentplayer;
		this->is_game_ended = gra.is_game_ended;
		this->is_game_drowed = gra.is_game_drowed;
		this->winner = gra.winner;
		this->currentpossition = gra.currentpossition;
		
		this->board = new string * [this->rozmiar];

		for (size_t x = 0; x < this->rozmiar; x++)
		{
			this->board[x] = new string[this->rozmiar];
			for (size_t y = 0; y < this->rozmiar; y++)
			{
				this->board[x][y] = gra.board[x][y];
			}
		}

	}

	void wyswietl_tablice()
	{
		// zrobic ladniejsza 
		for (size_t x = 0; x < rozmiar; x++)
		{
			for (size_t y = 0; y < rozmiar; y++)
			{
				cout << board[x][y] << " # ";

			}
			cout << "\n";

		}
	}

	void makemove()
	{
		bool ruch_udany = false;
		wyswietl_tablice();
		while (!ruch_udany)
		{
			int x;
			int y;
			cout << "Podaj wspolrzedne pola ktore chcesz wybrac\n";
			cin >> y;
			cin >> x;

			ruch_udany = move(x, y, currentplayer);
		}
		ilepustych--;

		if (!is_game_ended && !is_game_drowed)
		{
			if (currentplayer == "kolko")
			{
				currentplayer = "krzyz";
			}
			else if (currentplayer == "krzyz")
			{
				currentplayer = "kolko";
			}

			makemove();
		}

		else if (is_game_ended)
		{
			wyswietl_tablice();
			cout << "Wygrywa " << currentplayer << "\n";
			
			if (currentplayer == "kolko")
			{
				currentpossition = 1;
			}
			else if (currentplayer == "krzyz")
			{
				currentpossition = -1;
			}
			
		}

		else if (is_game_drowed)
		{
			wyswietl_tablice();
			cout << "REMIS \n";
		}

	}

	bool move(int x, int y, string gracz)
	{
		if (board[x][y] != "Puste")
		{
			return false;
		}
		board[x][y] = gracz;
		check_game_state();
		return true;
	}

	void check_game_state()
	{
		bool is_drawed = true;
		for (size_t x = 0; x < rozmiar; x++)
		{
			for (size_t y = 0; y < rozmiar; y++)
			{
				//jak beda bledy zobaczyc czy x z y sie nie jebnal albo rozmiar - x > to_win?

				if (check_column(x, y) || check_row(x, y) || check_diagonaldown(x, y) || check_diagonalup(x, y)) {
					this->is_game_ended = true;
				}
				if (board[x][y] == "Puste") {
					is_drawed = false;
				}

			}
		}
		this->is_game_drowed = is_drawed;
	}

	bool check_column(int x, int y)
	{
		if (board[x][y] == "Puste") {
			return false;
		}
		if (rozmiar - x < to_win)
		{
			return false;
		}

		for (size_t i = 1; i < to_win; i++)
		{
			if (board[x][y] != board[x + i][y] || board[x + i][y] == "Puste")
			{
				return false;
			}
		}
		return true;
	}

	bool check_row(int x, int y)
	{
		if (board[x][y] == "Puste") {
			return false;
		}
		if (rozmiar - y < to_win)
		{
			return false;
		}

		for (size_t i = 1; i < to_win; i++)
		{
			if (board[x][y] != board[x][y + i] || board[x][y + i] == "Puste")
			{
				return false;
			}
		}
		return true;

	}

	bool check_diagonaldown(int x, int y)
	{
		if (board[x][y] == "Puste") {
			return false;
		}
		if (rozmiar - x < to_win || rozmiar - y < to_win)
		{
			return false;
		}

		for (size_t i = 1; i < to_win; i++)
		{
			if (board[x][y] != board[x + i][y + i] || board[x + i][y + i] == "Puste")
			{
				return false;
			}
		}
		return true;

	}

	bool check_diagonalup(int x, int y)
	{
		if (board[x][y] == "Puste") {
			return false;
		}
		if (rozmiar - y < to_win || x < to_win - 1)
		{
			return false;
		}

		for (size_t i = 1; i < to_win; i++)
		{
			if (board[x][y] != board[x - i][y + i] || board[x - i][y + i] == "Puste")
			{
				return false;
			}
		}
		return true;

	}
	
};

struct coordinats {
	int x;
	int y;
	coordinats() {}
	coordinats(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class MinMax {
	
	int current_possition=0;
	string current_player;
	int alfa=0;
	int beta=0;
	int depth = 9;
	TicTacToe *gra_copy;
	coordinats current_coordinats;
	coordinats _coordinats;

public:	
	MinMax(TicTacToe& gra, int current_possition, string current_player)
	{
		gra_copy = new TicTacToe(gra);
		this ->current_possition = current_possition;
		this->current_player = current_player;
		
	}

	int min_max_algorithm() {
		if (current_possition != 0) {
			return current_possition;
		}

		if (current_player == "kolko")
		{
			current_possition = -INFINITY;
			for (size_t i = 0; i < gra_copy->ilepustych; i++)
			{
				


			}
		}

	}
};
	//alfa beta z cieciami (pozycja, gracz, alfa, beta)
	// glebokosc?
	// wykonanie kazdego mozliwego ruchu i dla niego rekurencja alfa beta....
	// ilosc ruchow? odwrotnie?  
	//


int main()
{


	TicTacToe gra(4, 4);





}

