#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<locale>
#include<iomanip>
#include<string>
#include<vector>
#include<windows.h>
#include<stdio.h>
#define TIMEUP  Time = a.GetDateNow(); cout << "Текущее Время: "<< Time.Hour << ':' << Time.Minute << ' ' << Time.Day << '.' << Time.Month << '.' << Time.Year << endl << endl;

#include<fstream>
#include <thread>
#include<chrono>

#define NumberPlace 10

#define GREEN SetConsoleTextAttribute(handle, (WORD)((10 << 0) | 10))
#define WHITE SetConsoleTextAttribute(handle, (WORD)((15 << 0) | 15))
#define RED SetConsoleTextAttribute(handle, (WORD)((12 << 0) | 4))
#define YELLOW SetConsoleTextAttribute(handle, (WORD)((14 << 0) | 14))

using namespace std;

using namespace this_thread;

bool VIP[NumberPlace][NumberPlace];// VIP - 1, Не VIP - 0

void FillVIP1()
{
	for (int j = 5; j<NumberPlace; j++)
		for (int k = 3; k < 7; k++)
			VIP[j][k] = 1;
}

int Random(int max)
{
	return rand() % max;

}

struct FILM
{
	int NumberofFilm;
	string Name;//Название фильм
	string Director;//Режисер
	string Description;//описание
	int Rat;//возрастной рейтинг

	FILM& operator = (const FILM &s)
	{
		NumberofFilm = s.NumberofFilm;
		Name = s.Name;
		Director = s.Director;
		Description = s.Description;
		Rat = s.Rat;
		return *this;

	};
};

struct DAT
{
	int Year = 2018;
	int Month;
	int Day;
	int Hour;
	int Minute;

	DAT& operator = (const DAT &s)
	{
		Year = s.Year;
		Month = s.Month;
		Day = s.Day;
		Hour = s.Hour;
		Minute = s.Minute;
		return *this;

	};
};

//struct ROOM
//{
//
//	ROOM& operator = (const ROOM &s)
//		{
//			for(int i=0;i<NumberPlace;i++)
//				for(int j=0;j<NumberPlace;j++)
//			Place[i][j] = s.Place[i][j];
//		
//			for (int i = 0; i < NumberPlace; i++)
//				for (int j = 0; j < NumberPlace; j++)
//					VIP[i][j] = s.VIP[i][j];
//		};
//
//};

struct SEANCE
{
	int NumberOfSeance;
	int NumberRoom;//номер зала (для удобства доступа)
	DAT Date; // интовые значения 
	FILM Film; // Название Фильма без пробелов
	int Price; // цена зависит от номера зала(0,1 - 250, 2- 320)
	bool Place[NumberPlace][NumberPlace];//Занято - 1, не занято - 0
	int FreeVIPlace = 20;

	SEANCE& operator = (const SEANCE &s)
	{
		NumberOfSeance = s.NumberOfSeance;
		NumberRoom = s.NumberRoom;
		Date = s.Date;
		Film = s.Film;
		Price = s.Price;

		for (int i = 0; i<NumberPlace; i++)
			for(int j=0;j<NumberPlace;j++)
				Place[i][j] = s.Place[i][j];

		FreeVIPlace = s.FreeVIPlace;

		return *this;

	};

};

struct ORDER
{
	bool canceled = 0;
	int NumberOrder;
	int NumberSeanceInOrder;
	int Total=0;
	SEANCE BeforeOrder;
	SEANCE AfterOrder;
};

class Cinema
{
protected:
	vector<SEANCE> Seance;// информация о всех сеансах
	vector<SEANCE>::iterator NumberOfSeance = Seance.end();// зачем тебе это? Уже понял
	int NumberSeance = 0;// Количество всех сеансов на 30 дней
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<FILM> Biblioteka;
	int NumberFilm = 0;//Количество фильмов
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ORDER> Order;//Список заказов
	vector<ORDER>::iterator NumberOfOrder= Order.begin();
	int NumberOrder = 0;



	void AddFilm(string Name, string  Director, string Description, int Rat)
	{
		NumberFilm++;
		Biblioteka.resize(NumberFilm);
		Biblioteka[NumberFilm - 1].NumberofFilm = NumberFilm - 1;
		for (int i = 0; i < Name.size(); i++)
			if (Name[i] == '_')Biblioteka[NumberFilm - 1].Name = Biblioteka[NumberFilm - 1].Name + ' ';
			else Biblioteka[NumberFilm - 1].Name = Biblioteka[NumberFilm - 1].Name + Name[i];

		for (int i = 0; i < Director.size(); i++)
			if (Director[i] == '_')Biblioteka[NumberFilm - 1].Director = Biblioteka[NumberFilm - 1].Director + ' ';
			else Biblioteka[NumberFilm - 1].Director = Biblioteka[NumberFilm - 1].Director + Director[i];

		for (int i = 0; i < Description.size(); i++)
			if (Description[i] == '_')Biblioteka[NumberFilm - 1].Description = Biblioteka[NumberFilm - 1].Description + ' ';
			else Biblioteka[NumberFilm - 1].Description = Biblioteka[NumberFilm - 1].Description + Description[i];

			Biblioteka[NumberFilm - 1].Rat=Rat;
	}
public:

	
};

class Cash : protected Cinema
{
private:


public:

	void BuyTicket(int n, int PlaceH, int PlaceL)
	{
		Seance[n].Place[PlaceH][PlaceL] = 1;
	}

	void AddSeance(int Month, int Day, int Hour, int Minute)
	{
		NumberSeance++;
		SEANCE NewSeance;
		//Seance.resize(NumberSeance);
		NumberOfSeance = Seance.end();
		Seance.insert(NumberOfSeance, NewSeance);
		Seance[NumberSeance - 1].NumberOfSeance = NumberSeance - 1;
		SetNumberOfRoom(NumberSeance - 1, Random(3));
		SetDate(NumberSeance - 1, Month, Day, Hour, Minute);
		Seance[NumberSeance - 1].Film = Biblioteka[Random(NumberFilm)];
		//cout << Seance[NumberSeance - 1].Date.Month << " " << Seance[NumberSeance - 1].Date.Day << " " << Seance[NumberSeance - 1].Date.Hour << ' ' << Seance[NumberSeance - 1].Date.Minute << ' ' << Seance[NumberSeance - 1].NumberOfSeance << ' ' << Seance[NumberSeance - 1].NumberRoom << endl;
	};



	bool CheckVIP(int PlaceH, int PlaceL)
	{
		if (VIP[PlaceH][PlaceL] == 1) return 1;
		else return 0;
	}

	void AddOrder(int Number, vector<int> PlaceH, vector<int> PlaceL,int NumberTicket)
	{
		NumberOrder++;//увеличевает количество ордеров
		//Order.resize(NumberOrder);//добавляет в вектор
		//NumberOfOrder = NumberOfOrder + NumberOrder - 1;//перемещает итератор
		ORDER NewOrder;
		Order.push_back(NewOrder);
		Order[NumberOrder - 1].BeforeOrder = Seance[Number];
		Order[NumberOrder - 1].AfterOrder = Seance[Number];
		Order[NumberOrder - 1].NumberSeanceInOrder = Number;

		for (int i = 0; i < NumberTicket; i++)
			Order[NumberOrder - 1].AfterOrder.Place[PlaceH[i]][PlaceL[i]] = 1;

		for (int i = 0; i < NumberTicket; i++)
			if (CheckVIP(PlaceH[i], PlaceL[i]) == 1)
			{
				Order[NumberOrder - 1].Total +=Seance[Number].Price * 1.5 ;
				Order[NumberOrder - 1].AfterOrder.FreeVIPlace--;
			}
			else Order[NumberOrder - 1].Total += Seance[Number].Price;

			if(Order[NumberOrder - 1].AfterOrder.Date.Hour < 12) Order[NumberOrder - 1].Total *= 0.75;
			else if (Order[NumberOrder - 1].AfterOrder.Date.Hour > 18) Order[NumberOrder - 1].Total*= 1.5;

			Seance[Number] = Order[NumberOrder - 1].AfterOrder;

	}

	void CancerOrder(int Number)
	{
		int a = Order[Number].NumberSeanceInOrder;
		for (int i = 0; i < NumberPlace; i++)
			for (int j = 0; j < NumberPlace; j++)
				if (Order[Number].BeforeOrder.Place[i][j] != Order[Number].AfterOrder.Place[i][j]) 
					Seance[a].Place[i][j] = 0;
		Order[Number].canceled = 1;
	}

	int FreePlaceNumberOfSeance(int N)
	{
		int c;
		for(int i=0;i<NumberPlace;i++)
			for (int j = 0; j < NumberPlace; j++)
				if (FreePlace(N, i, j))c++;

	}

	int FreeVIPPlaceNumberOfSeance(int N)
	{
		return Seance[N].FreeVIPlace;
	}

	DAT GetDateNow()
	{
		SYSTEMTIME Time;
		GetLocalTime(&Time);
		DAT Date;
		Date.Year = Time.wYear;
		Date.Month = Time.wMonth;
		Date.Day = Time.wDay;
		Date.Hour = Time.wHour;
		Date.Minute = Time.wMinute;

		return Date;
	}

	void DeleteSeance() // FirstSeance
	{
		for (int i = 0; i < NumberSeance; i++)
			Seance[i].NumberOfSeance--;
		NumberOfSeance = Seance.begin();
		Seance.erase(NumberOfSeance);
		NumberSeance--;
	}

	void SetDate(int n, int Month, int Day, int Hour, int Minute)
	{
		Seance[n].Date.Month = Month;
		Seance[n].Date.Day = Day;
		Seance[n].Date.Hour = Hour;
		Seance[n].Date.Minute = Minute;
	}
	void SetNumberOfRoom(int n, int Num)
	{
		Seance[n].NumberRoom = Num;
		if (Seance[n].NumberRoom == 2)Seance[n].Price = 320;
		else Seance[n].Price = 250;

	}

	bool FreePlace(int n, int PlaceH, int PlaceL)//свободно -1  занято - 0 
	{
		//cout << Seance[n].Place[PlaceH][PlaceL];
		if (Seance[n].Place[PlaceH][PlaceL] == 1) return 0;
		else return 1;
	}
	int NumberOfFreePlace(int n)
	{
		int c = 0;
		for (int i; i < NumberPlace; i++)
			for (int j; j < NumberPlace; j++)
				if (Seance[n].Place[i][j] == 0) c++;
		return c;

	}

	bool Save()
	{
		// не пригодилось
	}

	bool Open()
	{
		ifstream fin;

		fin.open("Films.txt");

		string buf;
		string Name, Director, Description;
		int Rat;

		if (fin.is_open())
		{
			while (!fin.eof())
			{
				fin >> buf;
				if (buf == "Название:")
					while (buf != "Режиссёр:")
					{
						Name = buf;
						fin >> buf;
					}
				if (buf == "Режиссёр:")
					while (buf != "Описание:")
					{
						Director = buf;
						fin >> buf;
					}
				if (buf == "Описание:")
					while (buf != "Рейтинг:")
					{
						Description = buf;
						fin >> buf;
					}
				if (buf == "Рейтинг:")
					fin >> Rat;
				AddFilm(Name, Director, Description, Rat);
			}
			return 1;
		}
		else return 0;

		fin.close();
	}
	
	int GetNumberFilms()
	{
		return NumberFilm;
	}
	string GetNameFilm(int Number)
	{
		return Biblioteka[Number].Name;
	}
	string GetDirectorFilm(int Number)
	{
		return Biblioteka[Number].Director;
	}
	string GetDescriptionFilm(int Number)
	{
		return Biblioteka[Number].Description;
	}
	int GetRatingFilm(int Number)
	{
		return Biblioteka[Number].Rat;
	}
	SEANCE GetSeance(int Number)
	{
		return Seance[Number];
	}
	int GetNumberSeance()
	{
		return NumberSeance;
	}
	int GetNumberOrders()
	{
		return NumberOrder;
	}
	ORDER GetOrder(int Number)
	{
		return Order[Number];
	}
};

int main()
{
	srand(time(0));
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	FillVIP1();
	setlocale(LC_ALL, "ru");
	DAT Time;
	Cash a;
	char menu;
	a.Open();
	Time = a.GetDateNow();
	for (int i = 0; i < 30; i++)//Эмуляция загрузки из файла
	{
		int Day = Time.Day + i;
		int Month = Time.Month;
		if (Day > 31) {Day = Day - 31; Month++; };//т.к. сейчас уже май(, а это тестовая программа
		for (int H = 10; H < 23; H += 3)
			a.AddSeance(Month, Day, H, Random(40) + 10);
	};
	for (int i = 0; i < 5; i++)
	{
		if (a.GetDateNow().Hour > a.GetSeance(0).Date.Hour)a.DeleteSeance();
		else if (a.GetDateNow().Hour == a.GetSeance(0).Date.Hour)
			if (a.GetDateNow().Minute > a.GetSeance(0).Date.Minute) a.DeleteSeance();
					
	}

	while (1)
	{
		Time = a.GetDateNow();
		for (int i=0;Time.Day == a.GetSeance(i).Date.Day && Time.Hour >= a.GetSeance(i).Date.Hour;i++)
		{

		};
		system("cls");
		TIMEUP;
		cout << "1.Сейчас в кино" << endl;
		cout << "2.Купить билет" << endl;
		cout << "3. О программе" << endl;
		cout << endl;
		cout << "0.Завершить работу"<<endl;

		cin >> menu;

		switch (menu)
		{
		case '1': 
		{
			system("cls");
			cout << "Сейчас в прокате:" << endl;
			for (int i = 0; i < a.GetNumberFilms(); i++)
				cout << i + 1 << '.' << a.GetNameFilm(i)<<endl;



			cin >> menu;

			switch (menu)
			{
			case '1':
			{
				system("cls");
				cout << "Название Фильма: " << a.GetNameFilm(0) << endl
					 << "Режиссёр: " << a.GetDirectorFilm(0) << endl
					<< "Описание: "; 
				int i;
				for (i = 0; i < a.GetDescriptionFilm(0).size(); i++)
				{
					cout << a.GetDescriptionFilm(0)[i];
					if (i % 57 == 0 && i != a.GetDescriptionFilm(1).size() - 1 && i != 0 && a.GetDescriptionFilm(0)[i] != ' ')cout << '-' << endl << "          ";
					if (i % 57 == 0 && i != a.GetDescriptionFilm(1).size() - 1 && i != 0 && a.GetDescriptionFilm(0)[i] == ' ')cout << endl << "          ";
				}
				if (i % 57 != 0 )cout << endl;
					cout << "Рейтинг:  " << a.GetRatingFilm(0) << '+' << endl << endl;
///////////////////////////////////////////////////////о фильме 
					cout << "Сеансы на ближайшие 3 дня:" << endl << endl;

					int NewDay=0;
					int c=0;
					for (int i = 0; NewDay < 4; i++)//пока не встречено 22 часа 4 раза
					{
						if (a.GetSeance(i).Date.Hour == 22) NewDay++;
						c++;
						if (a.GetSeance(i).Film.NumberofFilm == 0)
						{
							SEANCE NowSeance;
							NowSeance = a.GetSeance(i);

							cout << c << ')';
							cout << NowSeance.Date.Hour << ':' << NowSeance.Date.Minute
								<< ' ' << NowSeance.Date.Day << '.' << NowSeance.Date.Month << '.' << NowSeance.Date.Year
								<< ' ' << NowSeance.Film.Name << endl
								<< endl
								<< "Номер Зала:" << NowSeance.NumberRoom + 1 << endl
								<< endl;
							cout << "  ";
							for (int j = 1; j <= 10; j++)
								cout << left << setw(2) << j;
							cout << endl;

							for (int k = 0; k < NumberPlace; k++)
							{
								cout << setw(2) << k + 1;
								for (int l = 0; l < NumberPlace; l++)
								{
									if (NowSeance.Place[k][l] == 1) { RED; cout << '0' << ' '; GREEN; }
									else if (a.CheckVIP(k, l)) { YELLOW; cout << '0' << ' '; GREEN; }
									else { WHITE; cout << '0' << ' '; GREEN; }
								}
								if (k == 2) { WHITE; cout << " 0"; GREEN; cout << " - Свободные места"; }
								if (k == 4) { YELLOW; cout << " 0"; GREEN; cout << " - VIP места"; }
								if (k == 6) { RED; cout << " 0"; GREEN; cout << " - Занятые места"; }
								cout << endl;
							}
							cout << endl;
						}
					};

					cout << "Введите Номер Сеанса:";
					int Num;
					cin >> Num;

					if (Num < c + 1)
					{
M1:						system("cls");
						SEANCE NowSeance;
						NowSeance = a.GetSeance(Num-1);

						cout << Num << ')';
						cout << NowSeance.Date.Hour << ':' << NowSeance.Date.Minute
							<< ' ' << NowSeance.Date.Day << '.' << NowSeance.Date.Month << '.' << NowSeance.Date.Year
							<< ' ' << NowSeance.Film.Name << endl
							<< endl
							<< "Номер Зала:" << NowSeance.NumberRoom + 1 << endl
							<< endl;
						cout << "  ";
						for (int j = 1; j <= 10; j++)
							cout << left << setw(2) << j;
						cout << endl;

						for (int k = 0; k < NumberPlace; k++)
						{
							cout << setw(2) << k + 1;
							for (int l = 0; l < NumberPlace; l++)
							{
								if (NowSeance.Place[k][l] == 1) { RED; cout << '0' << ' '; GREEN; }
								else if (a.CheckVIP(k, l)) { YELLOW; cout << '0' << ' '; GREEN; }
								else { WHITE; cout << '0' << ' '; GREEN; }
							}
							if (k == 2) { WHITE; cout << " 0"; GREEN; cout << " - Свободные места"; }
							if (k == 4) { YELLOW; cout << " 0"; GREEN; cout << " - VIP места"; }
							if (k == 6) { RED; cout << " 0"; GREEN; cout << " - Занятые места"; }
							cout << endl;
						}
						cout << endl;
					}
					
					cout << "Введите через пробел места которые хотите купить (Пример 4 5 10 9 . ):";

					string Musor="";
					vector<int> PlaceH;
					vector<int> PlaceL;
					for(int y=0; Musor != ".";y++)
					{	
						cin >> Musor;
						if (y % 2 == 0 && Musor != ".")
						{
							if (Musor == "10")PlaceH.push_back(9);
							else PlaceH.push_back(atoi(&Musor[0])-1);
						}
						if (y % 2 == 1 && Musor != ".")
						{
							if (Musor == "10")PlaceL.push_back(10-1);
							else PlaceL.push_back(atoi(&Musor[0])-1);
						}
					}
					if (PlaceH.size() == PlaceL.size())
					{
						for (int y = 0; y < PlaceH.size(); y++)
						{
							if (!a.FreePlace(Num - 1, PlaceH[y], PlaceL[y]))
							{
								cout << "Место " << PlaceH[y] +1 << ',' << PlaceL[y] +1 << " занято." << endl;
								cout << "Попробуйте еще раз.";
								system("pause");
								goto M1;
							}
						}

						a.AddOrder(Num - 1, PlaceH, PlaceL, PlaceH.size());
					}
					else cout << "Ошибка ввода!";
					

					break;
			};
			case '2':
			{
				system("cls");
				cout << "Название Фильма: " << a.GetNameFilm(1) << endl
					<< "Режиссёр: " << a.GetDirectorFilm(1) << endl
					<< "Описание: ";
				int i;
				for (i = 0; i < a.GetDescriptionFilm(0).size(); i++)
				{
					cout << a.GetDescriptionFilm(1)[i];
					if (i % 57 == 0 && i != a.GetDescriptionFilm(1).size() - 1 && i != 0 && a.GetDescriptionFilm(1)[i] != ' ')cout <<'-'<< endl << "          ";
					if (i % 57 == 0 && i != a.GetDescriptionFilm(1).size() - 1 && i != 0 && a.GetDescriptionFilm(1)[i] == ' ')cout << endl << "          ";
				}
				if (i % 57 != 0)cout << endl;
				cout << "Рейтинг:  " << a.GetRatingFilm(1) << '+' << endl << endl;

				cout << "Сеансы на ближайшие 3 дня:" << endl << endl;

				int NewDay = 0;
				int c = 0;
				for (int i = 0; NewDay < 4; i++)//пока не встречено 22 часа 4 раза
				{
					if (a.GetSeance(i).Date.Hour == 22) NewDay++;
					c++;
					if (a.GetSeance(i).Film.NumberofFilm == 1)
					{
						SEANCE NowSeance;
						NowSeance = a.GetSeance(i);

						cout << c << ')';
						cout << NowSeance.Date.Hour << ':' << NowSeance.Date.Minute
							 << ' ' << NowSeance.Date.Day << '.' << NowSeance.Date.Month << '.' << NowSeance.Date.Year
							 << ' ' << NowSeance.Film.Name << endl
							 << endl
							 << "Номер Зала:" << NowSeance.NumberRoom + 1 << endl
							 << endl;
						cout << "  ";
						for (int j = 1; j <= 10; j++)
							cout << left << setw(2) << j;
						cout << endl;

						for (int k = 0; k < NumberPlace; k++)
						{
							cout << setw(2) << k + 1;
							for (int l = 0; l < NumberPlace; l++)
							{
								if (NowSeance.Place[k][l] == 1) { RED; cout << '0'<<' '; GREEN; }
								else if (a.CheckVIP(k, l)) { YELLOW; cout << '0' << ' '; GREEN; }
								else { WHITE; cout << '0' << ' '; GREEN; }
							}
							if (k == 2) { WHITE; cout << " 0"; GREEN; cout << " - Свободные места"; }
							if (k == 4) { YELLOW; cout << " 0"; GREEN; cout << " - VIP места"; }
							if (k == 6) { RED; cout << " 0"; GREEN; cout << " - Занятые места"; }
							cout << endl;
						}
						cout << endl;
					}
				};
				cout << "Введите Номер Сеанса:";
				int Num;
				cin >> Num;

				if (Num < c + 1)
				{
M2:					system("cls");
					SEANCE NowSeance;
					NowSeance = a.GetSeance(Num - 1);

					cout << Num << ')';
					cout << NowSeance.Date.Hour << ':' << NowSeance.Date.Minute
						<< ' ' << NowSeance.Date.Day << '.' << NowSeance.Date.Month << '.' << NowSeance.Date.Year
						<< ' ' << NowSeance.Film.Name << endl
						<< endl
						<< "Номер Зала:" << NowSeance.NumberRoom + 1 << endl
						<< endl;
					cout << "  ";
					for (int j = 1; j <= 10; j++)
						cout << left << setw(2) << j;
					cout << endl;

					for (int k = 0; k < NumberPlace; k++)
					{
						cout << setw(2) << k + 1;
						for (int l = 0; l < NumberPlace; l++)
						{
							if (NowSeance.Place[k][l] == 1) { RED; cout << '0' << ' '; GREEN; }
							else if (a.CheckVIP(k, l)) { YELLOW; cout << '0' << ' '; GREEN; }
							else { WHITE; cout << '0' << ' '; GREEN; }
						}
						if (k == 2) { WHITE; cout << " 0"; GREEN; cout << " - Свободные места"; }
						if (k == 4) { YELLOW; cout << " 0"; GREEN; cout << " - VIP места"; }
						if (k == 6) { RED; cout << " 0"; GREEN; cout << " - Занятые места"; }
						cout << endl;
					}
					cout << endl;
				}

				cout << "Введите через пробел места которые хотите купить (Пример 4 5 10 9 . ):";

				string Musor = "";
				vector<int> PlaceH;
				vector<int> PlaceL;
				for (int y = 0; Musor != "."; y++)
				{
					cin >> Musor;
					if (y % 2 == 0 && Musor != ".")
					{
						if (Musor == "10")PlaceH.push_back(10 - 1);
						else PlaceH.push_back(atoi(&Musor[0]) - 1);
					}
					if (y % 2 == 1 && Musor != ".")
					{
						if (Musor == "10")PlaceL.push_back(10 - 1);
						else PlaceL.push_back(atoi(&Musor[0]) - 1);
					}
				}
				if (PlaceH.size() == PlaceL.size())
				{
					for (int y = 0; y < PlaceH.size(); y++)
					{
						if (!a.FreePlace(Num - 1, PlaceH[y], PlaceL[y]))
						{
							cout << "Место " << PlaceH[y] + 1 << ',' << PlaceL[y] + 1 << " занято." << endl;
							cout << "Попробуйте еще раз.";
							system("pause");
							goto M2;
						}
					}

					a.AddOrder(Num - 1, PlaceH, PlaceL, PlaceH.size());
				}
				else cout << "Ошибка ввода!";

			};



			}



			break;
		};
		case '2': 
		{
			system("cls");
			TIMEUP;
			cout << "Сеансы на ближайшие 3 дня:" << endl << endl;

			cout << "Выберете сеанс:" << endl << endl;
		



			int NewDay = 0;
			int c = 0;
			for (int i = 0; NewDay < 4; i++)//пока не встречено 22 часа 4 раза
			{
				if (a.GetSeance(i).Date.Hour == 22) NewDay++;
					c++;
					SEANCE NowSeance;
					NowSeance = a.GetSeance(i);

					cout << c << ')';
					cout << NowSeance.Date.Hour << ':' << NowSeance.Date.Minute
						<< ' ' << NowSeance.Date.Day << '.' << NowSeance.Date.Month << '.' << NowSeance.Date.Year
						<< ' ' << NowSeance.Film.Name << endl
						<< endl
						<< "Номер Зала:" << NowSeance.NumberRoom + 1 << endl
						<< endl;
					cout << "  ";
					for (int j = 1; j <= 10; j++)
						cout << left << setw(2) << j;
					cout << endl;

					for (int k = 0; k < NumberPlace; k++)
					{
						cout << setw(2) << k + 1;
						for (int l = 0; l < NumberPlace; l++)
						{
							if (NowSeance.Place[k][l] == 1) { RED; cout << '0' << ' '; GREEN; }
							else if (a.CheckVIP(k, l)) { YELLOW; cout << '0' << ' '; GREEN; }
							else { WHITE; cout << '0' << ' '; GREEN; }
						}
						if (k == 2) { WHITE; cout << " 0"; GREEN; cout << " - Свободные места"; }
						if (k == 4) { YELLOW; cout << " 0"; GREEN; cout << " - VIP места"; }
						if (k == 6) { RED; cout << " 0"; GREEN; cout << " - Занятые места"; }
						cout << endl;
					}
					cout << endl;
			};

			cout << "Введите Номер Сеанса:";
			int Num;
			cin >> Num;

			if (Num < c + 1)
			{
M3:				system("cls");
				SEANCE NowSeance;
				NowSeance = a.GetSeance(Num - 1);

				cout << Num << ')';
				cout << NowSeance.Date.Hour << ':' << NowSeance.Date.Minute
					<< ' ' << NowSeance.Date.Day << '.' << NowSeance.Date.Month << '.' << NowSeance.Date.Year
					<< ' ' << NowSeance.Film.Name << endl
					<< endl
					<< "Номер Зала:" << NowSeance.NumberRoom + 1 << endl
					<< endl;
				cout << "  ";
				for (int j = 1; j <= 10; j++)
					cout << left << setw(2) << j;
				cout << endl;

				for (int k = 0; k < NumberPlace; k++)
				{
					cout << setw(2) << k + 1;
					for (int l = 0; l < NumberPlace; l++)
					{
						if (NowSeance.Place[k][l] == 1) { RED; cout << '0' << ' '; GREEN; }
						else if (a.CheckVIP(k, l)) { YELLOW; cout << '0' << ' '; GREEN; }
						else { WHITE; cout << '0' << ' '; GREEN; }
					}
					if (k == 2) { WHITE; cout << " 0"; GREEN; cout << " - Свободные места"; }
					if (k == 4) { YELLOW; cout << " 0"; GREEN; cout << " - VIP места"; }
					if (k == 6) { RED; cout << " 0"; GREEN; cout << " - Занятые места"; }
					cout << endl;
				}
				cout << endl;
			}

			cout << "Введите через пробел места которые хотите купить (Пример 4 5 10 9 . ):";

			string Musor = "";
			vector<int> PlaceH;
			vector<int> PlaceL;
			for (int y = 0; Musor != "."; y++)
			{
				cin >> Musor;
				if (y % 2 == 0 && Musor != ".")
				{
					if (Musor == "10")PlaceH.push_back(10 - 1);
					else PlaceH.push_back(atoi(&Musor[0]) - 1);
				}
				if (y % 2 == 1 && Musor != ".")
				{
					if (Musor == "10")PlaceL.push_back(10 - 1);
					else PlaceL.push_back(atoi(&Musor[0]) - 1);
				}
			}
			if (PlaceH.size() == PlaceL.size())
			{
				for (int y = 0; y < PlaceH.size(); y++)
				{
					if (!a.FreePlace(Num - 1, PlaceH[y], PlaceL[y]))
					{
						cout << "Место " << PlaceH[y] + 1 << ',' << PlaceL[y] + 1 << " занято." << endl;
						cout << "Попробуйте еще раз.";
						system("pause");
						goto M3;
					}
				}

				a.AddOrder(Num - 1, PlaceH, PlaceL, PlaceH.size());
			}
			else cout << "Ошибка ввода!";

			break;
		};
		case 'L': {system("cls"); cout << "By Login 28.04.2018" << endl; for (int i = 5; i > 0; i--) { cout << i << endl; sleep_for(chrono::seconds(1)); }; break; }
		case '3':
		{
			system("cls");
			cout << "Припокупке билетов создается заказ который можно отменить" << endl
				<< "Введите O в главном меню чтобы открыть список заказов " << endl;
			cout << "Так же там можно составить билеты " << endl;

			break;
		}
		case 'O':
		{
			system("cls");
			for (int i = 0; i < a.GetNumberOrders(); i++)
			{
				ORDER NewO;
				NewO = a.GetOrder(i);
				cout << i + 1 << ')' << NewO.AfterOrder.Date.Day << '.'
					<< NewO.AfterOrder.Date.Month << '.'
					<< NewO.AfterOrder.Date.Year << ' '
					<< NewO.AfterOrder.Date.Hour << ':'
					<< NewO.AfterOrder.Date.Minute << ','
					<< "Зал: " << NewO.AfterOrder.NumberRoom+1 << ','
					<< NewO.AfterOrder.Film.Name << ','
					<< "Забронированные места: ";
				for (int k = 0; k < NumberPlace; k++)
					for (int l = 0; l < NumberPlace; l++)
						if (NewO.BeforeOrder.Place[k][l] != NewO.AfterOrder.Place[k][l]) cout << '(' << k + 1 << ',' << l + 1 << ')' << ' ';
				cout << ",Итого:" << NewO.Total<<"   ";
				if (NewO.canceled == 1)cout << "Отменён";
				cout << endl;


			}
			cout << endl << endl;
			cout << "Введите номер заказа (или 0 для выхода):";
			int NumberO;
			cin >> NumberO;
			system("cls");
			if (NumberO > 0 && NumberO < a.GetNumberOrders() + 1)
			{
				ORDER NewO;
				NewO = a.GetOrder(NumberO-1);
				cout << NumberO  << ')' << NewO.AfterOrder.Date.Day << '.'
					<< NewO.AfterOrder.Date.Month << '.'
					<< NewO.AfterOrder.Date.Year << ' '
					<< NewO.AfterOrder.Date.Hour << ':'
					<< NewO.AfterOrder.Date.Minute << ','
					<< "Зал: " << NewO.AfterOrder.NumberRoom + 1 << ','
					<< NewO.AfterOrder.Film.Name << ','
					<< "Забронированные места: ";
				for (int k = 0; k < NumberPlace; k++)
					for (int l = 0; l < NumberPlace; l++)
						if (NewO.BeforeOrder.Place[k][l] != NewO.AfterOrder.Place[k][l]) cout << '(' << k + 1 << ',' << l + 1 << ')' << ' ';
				cout << ",Итого:" << NewO.Total << "   ";
				if (NewO.canceled == 1)cout << "Отменён";
				cout << endl << endl;

				cout << "1.Показать билеты" << endl;
				if (NewO.canceled == 0)cout << "2.Отменить заказ" << endl;
				char Musor;

				cin >> Musor;

				if (Musor == '1')
				{
					system("cls");
					for(int k=0;k<NumberPlace;k++)
						for (int l = 0; l<NumberPlace; l++)
							if (NewO.AfterOrder.Place[k][l] != NewO.BeforeOrder.Place[k][l])
							{
								cout << "Дата и время сеанса:" << NewO.AfterOrder.Date.Day << '.'
									<< NewO.AfterOrder.Date.Month << '.'
									<< NewO.AfterOrder.Date.Year << ' '
									<< NewO.AfterOrder.Date.Hour << ':'
									<< NewO.AfterOrder.Date.Minute<<endl;
								cout << "Название фильма:" << NewO.AfterOrder.Film.Name << endl;
								cout << "Номер зала:" << NewO.AfterOrder.NumberRoom + 1 << endl;
								cout << "Ряд:" << k + 1 << endl;
								cout << "Место:" << l + 1 << endl;
								cout << endl;

							}
				}
				if (NewO.canceled == 0 && Musor == '2') a.CancerOrder(NumberO - 1);

			}
			break;

		}
		case '0':exit(0);
		
		}

		for (int i = 0; i < 5; i++)
		{
			if(a.GetDateNow().Day == a.GetSeance(0).Date.Day)
			if (a.GetDateNow().Hour > a.GetSeance(0).Date.Hour)a.DeleteSeance();
			else if (a.GetDateNow().Hour == a.GetSeance(0).Date.Hour)
				if (a.GetDateNow().Minute > a.GetSeance(0).Date.Minute) a.DeleteSeance();

		}

			system("pause");
	}
	
	
	
	
	
	system("pause");

	return 0;
}
//for (int i = 0; i<a.GetNumberFilms(); i++)
//	cout << a.GetNameFilm(i) << endl
//	<< a.GetDirectorFilm(i) << endl
//	<< a.GetDescriptionFilm(i) << endl
//	<< a.GetRatingFilm(i) <<'+'<< endl;
