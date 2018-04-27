#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<locale>
#include<string>
#include<vector>
#include<windows.h>
#include<stdio.h>


#include<fstream>
//#include <thread>
//#include<chrono>

#define NumberPlace 10

#define GREEN SetConsoleTextAttribute(handle, FOREGROUND_GREEN)
#define WHITE SetConsoleTextAttribute(handle, FOREGROUND_WHITE)
#define RED SetConsoleTextAttribute(handle, FOREGROUND_RED)

using namespace std;

//using namespace this_thread;

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
	int NumberRoom;//номер зала (для удобства доступа)
	DAT Date; // интовые значения 
	FILM Film; // Название Фильма без пробелов
	int Price; // цена зависит от номера зала(0,1 - 250, 2- 320)
	bool Place[NumberPlace][NumberPlace];//Занято - 1, не занято - 0
	int FreeVIPlace = 20;

	SEANCE& operator = (const SEANCE &s)
	{
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
	int Total;
	SEANCE BeforeOrder;
	SEANCE AfterOrder;
};

class Cinema
{
protected:
	vector<SEANCE> Seance;// информация о всех сеансах
	vector<SEANCE>::iterator NumberOfSeance = Seance.begin();// зачем тебе это?
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

	void AddSeance(int Month,int Day,int Hour, int Minute)
	{
		NumberSeance++;
		SEANCE NewSeance;
		NewSeance.Film = Biblioteka[Random(1)];
		NewSeance.NumberRoom = Random(2);
		NewSeance.Price;
	};



	bool CheckVIP(int PlaceH, int PlaceL)
	{
		if (VIP[PlaceH][PlaceL] == 1) return 1;
		else return 0;
	}

	void AddOrder(int Number, int PlaceH[], int PlaceL[],int NumberTicket)
	{
		NumberOrder++;//увеличевает количество ордеров
		Order.resize(NumberOrder);//добавляет в вектор
		NumberOfOrder = NumberOfOrder + NumberOrder - 1;//перемещает итератор
		Order[NumberOrder - 1].BeforeOrder = Seance[Number];
		Order[NumberOrder - 1].AfterOrder = Seance[Number];
		Order[NumberOrder - 1].NumberSeanceInOrder = Number;

		for (int i = 0; i < NumberTicket; i++)
			Order[NumberOrder - 1].AfterOrder.Place[PlaceH[i]][PlaceL[i]] = 1;

		for (int i = 0; i < NumberTicket; i++)
			if (CheckVIP(PlaceH[i], PlaceL[i]) == 1)
			{
				Order[NumberOrder - 1].Total = (Order[NumberOrder - 1].Total + Seance[Number].Price * 1.5);
				Order[NumberOrder - 1].AfterOrder.FreeVIPlace--;
			}
			else Order[NumberOrder - 1].Total = Order[NumberOrder - 1].Total + Seance[Number].Price;

			Seance[Number] = Order[NumberOrder - 1].AfterOrder;

	}

	void CancerOrder(int Number)
	{
		for (int i = 0; i < NumberPlace; i++)
			for (int j = 0; j < NumberPlace; j++)
				if (Order[Number - 1].BeforeOrder.Place[i][j] != Order[Number - 1].AfterOrder.Place[i][j]) Seance[Order[Number - 1].NumberSeanceInOrder].Place[i][j] = 0;
		Order[Number - 1].canceled = 1;
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

	void DeleteSeance(int n)
	{

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
		Seance[n].NumberRoom = Num-1;
		if (Seance[n].NumberRoom == 2)Seance[n].Price = 320;
		else Seance[n].Price = 250;

	}

	bool FreePlace(int n, int PlaceH, int PlaceL)
	{
		if (Seance[n].Place[PlaceH][PlaceL] == 0) return 1;
		else return 0;
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

	void Testvivod()
	{
		for (int j = 0; j < NumberPlace; j++)
		{
			for (int k = 0; k < NumberPlace; k++)
			{
				cout << VIP[j][k];
			}
			cout << endl;

		}
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
};

int main()
{
	srand(time(0));
	FillVIP1();
	setlocale(LC_ALL, "ru");
	DAT Time;
	Cash a;
	//system("cls");
//	Time = a.GetDateNow();
	//cout << Time.Hour << ':' << Time.Minute << ' ' << Time.Day << '.' << Time.Month << '.' << Time.Year << endl;;
	a.Open();

	a.AddSeance();
	
	system("pause");

	return 0;
}
//for (int i = 0; i<a.GetNumberFilms(); i++)
//	cout << a.GetNameFilm(i) << endl
//	<< a.GetDirectorFilm(i) << endl
//	<< a.GetDescriptionFilm(i) << endl
//	<< a.GetRatingFilm(i) << endl;