#include<iostream> 
#include<string> 
#include<ctime> 
#include<vector> 
#include<math.h>
#include<conio.h>
# include<windows.h>
//#include<> 

using namespace std;

class Game
{
	int NumberS = 5;
	int Difficult = 0;
	long int Number = 0;
public:
	Game()
	{
		srand(time(NULL));
	}
	void SetNumberS(int N)
	{
		NumberS = N;
	}
	void SetDifficult(int H)
	{
		Difficult = H;
	}
	void AddNumber()
	{
		int Mass[10];
		int n = NumberS;
		for (int i = 0; i < 10; i++)
			Mass[i] = i;

		for (int i = 0; i < NumberS; i++)
		{
			int Num = rand() % (10 - i);
			if (i == 0) while (!Num)Num = rand() % (10 - i);
			Number += Mass[Num] * pow(10, n - 1);
			n--;
			Mass[Num] = Mass[9 - i];
		}
		//Number = (rand()*rand()) % NumberS * 10; 
	}



	long int GetNumber()
	{
		return Number;
	}
	int GetNumberS()
	{
		return NumberS;
	}
	int CheckBull(long int a)
	{
		int Bull = 0;
		long int b = Number;
		for (int i = 1; i < NumberS + 1; i++)
		{
			if (a % 10 == b % 10) Bull++;
			a = a / 10;
			b = b / 10;
		}
		return Bull;
	}
	int CheckCow(long int a)
	{
		int Cow = 0;
		long int b = Number;
		for (int i = 1; i < NumberS + 1; i++)
			for (int j = 1; j < NumberS + 1; j++)
			{
				int b10 = pow(10, i);
				int a10 = pow(10, j);
				int b1 = pow(10, i - 1);
				int a1 = pow(10, j - 1);
				if (b % b10 / b1 == a % a10 / a1) Cow++;
			}
		return Cow - CheckBull(a);
	}
	void YouWin()
	{
		do
		{
			system("color 04");
			cout << "You win!";
			system("color 06");
			cout << "You win!";
			system("color 02");
			cout << "You win!";
			system("color 01");
			cout << "You win!";
			system("color 05");
			cout << "You win!";
			if (_kbhit()) break;
		} while (1);
		system("color 0A");
		Number = 0;
	}
	int GetDifficult()
	{
		return Difficult;
	}
	bool CheckUnic(long int a)
	{
		int Mass[10];
		long int n = a;
		for (int i = 0; i < 10; i++)
			Mass[i] = i;

		
		for (int i = 0; i < GetNumberS(); i++)
		{
			int j = 0;
			for (;j<10-i;j++)
				if (Mass[j] == n % 10)
				{
					Mass[j] = Mass[9 - i];
					n /= 10;
					j = 0;
					break;
				}
			if (j == 10 - i) return 0;
		}

		return 1;




	}

};

int main()
{
	char menu;
	Game a;
	bool GameOver = 0;
	system("color 0A");
Ula:cout << "HI!" << endl << endl;


	while (!GameOver)
	{
		int i = 0;
		while (i < 1 || i>10)
		{
			system("cls");
			cout << "Enter number numeral(max 9):";
			cin >> i;
		}
		a.SetNumberS(i);
		a.AddNumber();
		system("cls");
		cout << "  *correct: " << a.GetNumber() << '*' << endl;
		system("pause");
		system("cls");
		while (!GameOver)
		{
			cout << "Enter Number:" << endl;
			long int Num = -1, Hum, Ran;
			cin >> Num;
			Hum = Num;
			Ran = a.GetNumber();
			if (i == 1) cout << "Cow:" << a.CheckCow(Num) << "   " << "Bull:" << a.CheckBull(Num) << endl;
			else
			{
				for (int k = 0; Hum != 0; k++)
				{
					Hum /= 10;
					Ran /= 10;
				}
				Hum = Num;
				for (int k = 0; k < a.GetNumberS(); k++)
				{
					Hum /= 10;
				}

				if (Ran > 0 || Hum) cout << "You didn't Enter " << a.GetNumberS() << " numeral!" << endl;
				else
				{
					if (!a.CheckUnic(Num))cout << "You  Entered repetitive numeral!" << endl;
					else
						cout << "Cow:" << a.CheckCow(Num) << "   " << "Bull:" << a.CheckBull(Num) << endl;

				}
			}
			if (a.CheckBull(Num) == a.GetNumberS())
			{
				a.YouWin();
				GameOver = 1;
			}
		}
	}
	system("cls");
	cout << "Restart?:" << endl
		<< "1.Yes" << endl
		<< "2.No" << endl;

	cin >> menu;

	switch (menu)
	{
	case '1': GameOver = 0;
		goto Ula;
		break;
	case '2': exit(0);
	}

	return 1;
}