#include<iostream>
//#include<ctime>  //  time lib (not used)
#include<conio.h>  //  player input (as one char)
//#include<windows.h>  //  c version of std used for delay (*sleep()*) (not used)

using namespace std;

// shift values in an array one to the right
void shift_right(int arr[], int size) {
	for (int i = size - 2; i >= 0; i--)
		arr[i + 1] = arr[i];
}

//----------------properties-------------------//
//( Top = 1, Down, Right, Left )
enum direction { Top = 1, Down, Right, Left };

//( int widht, int height, int fruitx, int fruity )
struct Map { int widht, height, fruitx, fruity; };

//( int headx, headv, tailn, tailx[50], taily[50], direction dir )
struct snake { int headx, headv, tailn, tailx[50] = { 0 }, taily[50] = { 0 }; direction dir; };

//( int score, bool lose, )
struct player { int score; bool lose; };

//---------------------------------------------//

Map map1; snake snake1; player player1;

//  Generates a fruit
void Generate_fruit() {
	srand(time(NULL));

	map1.fruitx = rand() % (map1.widht - 2) + 1;
	map1.fruity = rand() % (map1.height - 2) + 1;

}


void setup() {
	map1.widht = 40;
	map1.height = 20; // half for difference in size between lines and spases

	Generate_fruit();

	// initialize snake at mid
	snake1.headx = map1.widht / 2;
	snake1.headv = map1.height / 2;
	snake1.tailn = 0;
	player1.score = 0;
	player1.lose = false;

}
void draw() {
	// runs cls from MS-DOS
	system("cls");

	//loop over height 
	for (int i = 0; i < map1.height; i++) {

		//loop over widht 
		for (int j = 0; j < map1.widht; j++) {

			//check for border
			if (i == 0 || i == map1.height - 1)cout << "*";
			else if (j == 0 || j == map1.widht - 1)cout << "*";

			//check for snake head 
			else if (i == snake1.headv && j == snake1.headx)cout << "O";

			//check for snake fruit 
			else if (i == map1.fruity && j == map1.fruitx)cout << "$";
			else {
				bool printed = false;
				for (int z = 0; z < snake1.tailn; z++) {
					if (snake1.tailx[z] == j && snake1.taily[z] == i) {
						cout << "o";
						printed = true;
						break;
					}
				}
				if (!printed)cout << " ";
			}
		}
		cout << endl;
	}
	
	cout << "player score : " << player1.score << endl;
	cout << "snake1.tailn is : " << snake1.tailn << endl;
}
void input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case'w':snake1.dir = Top; break;
		case's':snake1.dir = Down; break;
		case'd':snake1.dir = Right; break;
		case'a':snake1.dir = Left; break;
		case'x':exit(0);
		}

	}
}
void move() {
	shift_right(snake1.tailx, 50);
	shift_right(snake1.taily, 50);
	snake1.tailx[0] = snake1.headx;
	snake1.taily[0] = snake1.headv;
	switch (snake1.dir)
	{
	case Top:snake1.headv--; break;
	case Down:snake1.headv++; break;
	case Right:snake1.headx++; break;
	case Left:snake1.headx--; break;
	}

	if (snake1.headv >= map1.height || snake1.headv <= 0 || snake1.headx >= map1.widht || snake1.headx <= 0)
		player1.lose = true;

	if (snake1.headx == map1.fruitx && snake1.headv == map1.fruity) {
		Generate_fruit();
		player1.score += 1;
		snake1.tailn = player1.score;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
}
int main() {
	setup();
	while (!player1.lose)
	{

		draw();
		input();
		move();

		//Sleep(75);  //not used as alluded at line 4 
	}
	system("pause");
	return 0;

}