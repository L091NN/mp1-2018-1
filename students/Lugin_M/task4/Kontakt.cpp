#include<iostream>
#include<string>
#include<locale>
#include<windows.h>
#include<iomanip>
#include<fstream>
#define Max 100
#define Menuup cout<<"Контактов:"<<GetCount()<<"/"<<Max<<endl<<endl;
#define RUcout   SetConsoleCP(1251);cout
#define Ncout    SetConsoleCP(866);cout
#define RUcin    SetConsoleCP(1251);cin

using namespace std;

class Contact
{
private:
	/*static*/ int count;
	string Surname[Max];
	string Name[Max];
	string SecondName[Max];
	string PhoneNumber[Max];
	string BD[Max];//день рождения
	string ALFAVIT = RUString();
	string FAIL = "Contacts.txt";
public:
	
	Contact()
	{

	};
	~Contact()
	{

	};

	void SetSurname(string Surname, int i)
	{
		this->Surname[i] = Surname;
	};
	void SetName(string Name, int i)
	{
		this->Name[i] = Name;
	};
	void SetSecondName(string SecondName, int i)
	{
		this->SecondName[i] = SecondName;
	};
	void SetPhoneNumber(string PhoneNumber, int i)
	{
		this->PhoneNumber[i] = PhoneNumber;
	};
	void SetBD(string BD, int i)
	{
		this->BD[i] = BD;
	};
	//	SetConsoleCP(1251); для ввода русских
	//  SetConsoleCP(866); стандартная кодировка
	void AddContact()
	{
		count++;//Количество Контактов

		string Ent;

		//system("cls");

		cout << "Обратите вниманий!ФИО-обязательное для заполнения поле." << endl
			<< "!Если пункт не требует заполнения введите - " << endl
			<< endl;

		cout << left;
		Ncout << setw(10) << "Фамилия:";
		RUcin >> Ent;
		SetSurname(Ent, count - 1);

		Ncout << setw(10) << "Имя:";
		RUcin >> Ent;
		SetName(Ent, count - 1);

		Ncout << setw(10) << "Отчество:";
		RUcin >> Ent;
		SetSecondName(Ent, count - 1);

		//ФИО является обязательгой информацией

		Ncout << setw(11) << "Номер тел.:";
		RUcin >> Ent;
		if (Ent != "-")SetPhoneNumber(Ent, count - 1);
		else SetPhoneNumber("", count - 1);

		Ncout << setw(11) << "Дата рож.:";
		RUcin >> Ent;
		if (Ent != "-")SetBD(Ent, count - 1);
		else SetBD("", count - 1);

		SetConsoleCP(866);
		Sort();
	};

	void SetContact(int i)
	{
		string a[5];
		int Number = 0;
		int y = 2;

		cout << "!Если пункт не требует изменения введите -" << endl << endl;
		
		Ncout << setw(17)<< "Старая фамилия:" << GetSurname(i)
			  << "     " << "\tНовая фамилия:\t";
		RUcin >> a[Number++];

		Ncout << setw(17) << "Старое имя:"<< GetName(i)
			  << "     "  << "\tНовое имя:\t";
		RUcin >> a[Number++];

		Ncout << setw(17) << "Старое Отчество:" << GetSecondName(i)
			  << "     " << "\tНовое Отчество:\t";
		RUcin >> a[Number++];

		Ncout << setw(17) << "Старый телефон:" << GetPhoneNumber(i)
			 << "     " << "\tНовый телефон:\t";
		RUcin >> a[Number++];

		Ncout << setw(17) << "Старая дата рож.:" << GetBD(i)
			 << "     " << "\tНовая дата рож.:";
		RUcin >> a[Number++];
		SetConsoleCP(866);

		while ((y != 0) && (y!=1))
		{
			cout << "Принять изменения?(1-ДА/0-НЕТ)" << endl;
			cin >> y;
		};
		if (y == 1)
			for (int k = 0; k < 5; k++)
			{
				if (a[k] != "-")
					switch (k)
					{
					case 0: {SetSurname(a[k], i); break;}
					case 1: {SetName(a[k], i); break;}
					case 2: {SetSecondName(a[k], i); break;}
					case 3: {SetPhoneNumber(a[k], i); break;}
					case 4: {SetBD(a[k], i); break;}
					};
			};
	};

	void UpOut()
	{
		Ncout << left << setw(3) << "Из."
			<< setw(4) << "№"
			<< setw(15 + 3) << "Фамилия"
			<< setw(10 + 3) << "Имя"
			<< setw(15 + 3) << "Отчество"
			<< setw(14 + 5) << "Номер телефона"
			<< setw(13 + 5) << "дата рождения"
			<< endl;
	};
	//шапка вывода

	char Char(int i)
	{
		int c = i % 64;
	 return char((c % 64) - 64);
		
	};
	string RUString()
	{
		string b;
		b = " ";
		int c = 0;
		for (int i = 1; i < 67; i++)
		{
			if (i < 15)
				if (i % 2 == 1) b = b + Char(i - c-1);
				else
				{
					c++;
					b = b + Char(i + 33 - c-2);
					
				}
			else
				if (i % 2 == 1)b = b + Char(i - c-2);
				else
				{
					c++;
					b = b + Char(i + 33 - c - 3);
				}
		}
		b[13] = char(168);
		b[14] = char(184);
		return b;
	}

	void Sort()
	{
		string Sort[Max];

		for (int i = 0; i < count; i++)
		{
			Sort[i] = GetSurname(i) +" "+ GetName(i)+" " + GetSecondName(i);
		};
		int i;
Zam:	i = 0;
		for (i; i < count-1; i++)//Перебирает все сверху вниз
		{
				int k = 0;
				while (!(ALFAVIT[k] == Sort[i][0]))
					k++;
				for (int j = i + 1; j < count; j++)
				{
					int l = 0;
					while (!(ALFAVIT[l] == Sort[j][0]))
						l++;
					if (k > l)
					{
						string buf;
						buf = Surname[i];
						Surname[i] = Surname[j];
						Surname[j] = buf;

						buf = Name[i];
						Name[i] = Name[j];
						Name[j] = buf;

						buf = SecondName[i];
						SecondName[i] = SecondName[j];
						SecondName[j] = buf;

						buf = PhoneNumber[i];
						PhoneNumber[i] = PhoneNumber[j];
						PhoneNumber[j] = buf;

						buf = BD[i];
						BD[i] = BD[j];
						BD[j] = buf;

						buf = Sort[i];
						Sort[i] = Sort[j];
						Sort[j] = buf;

						goto Zam;


					}
					else if (k == l)
					{
						for (int q = 1; q < max(sizeof(Sort[i]), sizeof(Sort[j])) - 1; q++)
						{
							int m = 0;
							while (!(ALFAVIT[m] == Sort[i][q]))
								m++;
							int n = 0;
							while (!(ALFAVIT[n] == Sort[j][q]))
								n++;
							if(m>n)
							{
								string buf;
								buf = Surname[i];
								Surname[i] = Surname[j];
								Surname[j] = buf;

								buf = Name[i];
								Name[i] = Name[j];
								Name[j] = buf;

								buf = SecondName[i];
								SecondName[i] = SecondName[j];
								SecondName[j] = buf;

								buf = PhoneNumber[i];
								PhoneNumber[i] = PhoneNumber[j];
								PhoneNumber[j] = buf;

								buf = BD[i];
								BD[i] = BD[j];
								BD[j] = buf;

								buf = Sort[i];
								Sort[i] = Sort[j];
								Sort[j] = buf;

								goto Zam;
								
							}
							else if (m < n) break;
						}
					};
				};


		};
	};
	//сортировка не идеальная, но рабочая(2 дня убил)Х|

	void Search(string a)
	{
		for (int i = 0; i < count; i++)
		{
			if (a == GetSurname(i) || a == GetName(i) || a == GetSecondName(i) || a==GetPhoneNumber(i) || a==GetBD(i))
			{
				Ncout << left << setw(3) << char(42)
					<< setw(4) << i + 1
					<< setw(15 + 3) << GetSurname(i)
					<< setw(10 + 3) << GetName(i)
					<< setw(15 + 3) << GetSecondName(i)
					<< setw(14 + 5) << GetPhoneNumber(i)
					<< setw(13 + 5) << GetBD(i)
					<< endl;
				continue;
			};
		};



	};

	void SearchChar(char a)
	{
		for (int i = 0; i < count; i++)
		{
			if (a == GetSurname(i)[0] || a == GetName(i)[0] || a == GetSecondName(i)[0])
			{
				Ncout << left << setw(3) << char(42)
					<< setw(4) << i + 1
					<< setw(15 + 3) << GetSurname(i)
					<< setw(10 + 3) << GetName(i)
					<< setw(15 + 3) << GetSecondName(i)
					<< setw(14 + 5) << GetPhoneNumber(i)
					<< setw(13 + 5) << GetBD(i)
					<< endl;
				continue;
			};
		};
	};

	void ShowContact()
	{
		UpOut();
		for (int i = 0; i < count; i++)
		{
			//SetConsoleCP(1251);
			Ncout << left << setw(3) << char(42)
				<< setw(4) << i + 1
				<< setw(15 + 3) << GetSurname(i)
				<< setw(10 + 3) << GetName(i)
				<< setw(15 + 3) << GetSecondName(i)
				<< setw(14 + 5) << GetPhoneNumber(i)
				<< setw(13 + 5) << GetBD(i)
				<< endl;
			SetConsoleCP(866);
		};
	};

	int GetCount()
	{
		return count;
	};

	void FailOpen()
	{
		fstream fs;
		fs.open(FAIL, fstream::in);
		if (!fs.is_open())
		{
			Ncout << "НЕ удалось считать файл";
		}
		else
		{
				fs >> count;
				for (int z = 0; !fs.eof(); z++)
				{

					fs >> Surname[z];
					fs >> Name[z];
					fs >> SecondName[z];
					fs >> PhoneNumber[z];
					if (PhoneNumber[z] == "-") SetPhoneNumber("", z);
					fs >> BD[z];
					if (BD[z] == "-") SetBD("", z);
				};
		}
   };

	void FailSave()
	{
		fstream fs;
		fs.open(FAIL, fstream::out);
//		fs.close();
//		fs.open(FAIL, fstream::app);
		if (!fs.is_open())
		{
			Ncout << "НЕ удалось считать файл";
		}
		else
		{
			fs << count << endl;
			for (int z = 0; z < count; z++)
			{
				fs << GetSurname(z) << " ";
				fs << GetName(z) << " ";
				fs << GetSecondName(z) << " ";
				if (GetPhoneNumber(z) == "") fs << "- ";
				else fs << GetPhoneNumber(z) << " ";
				if (GetBD(z) == "") fs << "- ";
				else fs << GetBD(z) << " ";
				fs << endl;
			}
		};
		fs.close();
	};

	string GetSurname(int i)
	{
		return Surname[i];
	};
	string GetName(int i)
	{
		return Name[i];
	};
	string GetSecondName(int i)
	{
		return SecondName[i];
	};
	string GetPhoneNumber(int i)
	{
		return PhoneNumber[i];
	};
	string GetBD(int i)
	{
		return BD[i];
	};

};

//int Contact::count = 0;

int main()
{
	setlocale(LC_ALL, "ru");
	Contact a;

	a.FailOpen();
	a.Sort();
	a.SearchChar('Л');
//	a.SearchFIO("Лугин");
//	a.SetConact(2);
	a.ShowContact();
//	a.FailSave();
//	cout<<a.RUString();

	
	system("pause");
	return 0;
}