# Tic-Tac-Toe AI

## Opis
Implementacja gry w kółko i krzyżyk z wykorzystaniem sztucznej inteligencji (AI) napisana w C++. AI korzysta z algorytmu minimax z przycinaniem alfa-beta, aby wybierać optymalne ruchy i zapewnić wyzwanie dla gracza.

## Zasady gry
Gra toczy się na planszy o określonym rozmiarze, a celem jest ułożenie określonej liczby znaków gracza w rzędzie, kolumnie lub przekątnej. Gracz oznaczony jako 'X' rywalizuje z AI, które jest oznaczone jako 'O'. Gracz rozpoczyna, a następnie gracze wykonują ruchy na przemian, aż zostaną spełnione jedne z trzech warunków końca gry: wygrana, remis lub zapełniona plansza.

## Instrukcje
1. Uruchom program, a następnie podaj rozmiar planszy (np. 3 dla planszy 3x3) i liczbę znaków potrzebną do wygranej (np. 3 dla wygranej w 3 znaki w rzędzie).

2. Gracz 'X' rozpoczyna grę i podaje ruch, wpisując numer wiersza i kolumny (indeksowane od 0), gdzie chce umieścić swój znak.

3. AI ('O') wykonuje ruch, a następnie gracze kontynuują na przemian.

4. Gra kończy się, gdy jeden z graczy wygra, plansza zostanie zapełniona, lub zostanie osiągnięta inna zdefiniowana sytuacja końcowa.

## Przykład użycia

Enter the size of the board: 3
Enter the length to win: 3

Podając powyższe wartości, rozpoczniesz grę na planszy 3x3, gdzie celem jest ułożenie 3 znaków w rzędzie, kolumnie lub przekątnej.
