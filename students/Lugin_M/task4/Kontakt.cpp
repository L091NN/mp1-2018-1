#include<iostream>
#include<string>
#include<locale>
#include<windows.h>
#include<iomanip>
#include<fstream>
#define Max 100
#define Menuup cout<<"Контактов:"<<a.GetCount()<<"/"<<Max<<endl<<endl;
//#define RUcout   SetConsoleCP(1251);cout
#define Ncout    SetConsoleCP(866);cout
#define RUcin    SetConsoleCP(1251);cin
#define KODNORM    SetConsoleCP(866)
using namespace std;

class Contact
{
private:
	/*static*/ int count=0;
	string Surname[Max];
	string Name[Max];
	string SecondName[Max];
	string PhoneNumber[Max];
	string BD[Max];//день рождения
	bool FAV[Max];//избранный
	string ALFAVIT = RUString();
	string FILE = "Contacts.txt";
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
	void SetFAV(bool FAV, int i)
	{
		this->FAV[i] = FAV;
	};
	//	SetConsoleCP(1251); для ввода русских
	//  SetConsoleCP(866); стандартная кодировка
	void AddContact(string Surname,string Name,string SecondName,string PhoneNumber,string BD)
	{
		count++;//Количество Контактов

		SetSurname(Surname, count - 1);

		SetName(Name, count - 1);

		SetSecondName(SecondName, count - 1);

		if (PhoneNumber != "-")SetPhoneNumber(PhoneNumber, count - 1);
		else SetPhoneNumber("", count - 1);

		if (BD != "-")SetBD(BD, count - 1);
		else SetBD("", count - 1);

		Sort();
	};

	void DeleteContact(int i)
	{
		Surname[i] = "!!!";
		Sort();
		count--;
	};

	void FAVplus(int i)
	{
		FAV[i] = 1;
	};

	void FAVminus(int i)
	{
		FAV[i] = 0;
	};

	void SetContact(int i ,string a[5])
	{

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
		b = b + '!';
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

						bool buF;

						buF = FAV[i];
						FAV[i] = FAV[j];
						FAV[j] = buF;

						buf = Sort[i];
						Sort[i] = Sort[j];
						Sort[j] = buf;

						goto Zam;


					}
					else if (k == l)
					{
						for (int q = 1; q < max(Sort[i].size(), Sort[j].size()); q++)
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

								bool buF;

								buF = FAV[i];
								FAV[i] = FAV[j];
								FAV[j] = buF;

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
			if (a == GetSurname(i) || a == GetName(i) || a == GetSurname(i)+ GetName(i) || a==  GetName(i)+ GetSurname(i))
			{
				ShowContact(i);
			};
		};



	};

	void SearchChar(char a)
	{
		char a2=' ';
		int k=0;
		while (a != a2)
		{
			a2 = Char(k);
			k++;
		}

		if (k > 32)a2 = Char(k - 33);
		else a2 = Char(k + 33);

		for (int i = 0; i < count; i++)
		{
			if (a == GetSurname(i)[0] || a == GetName(i)[0] || a == GetSecondName(i)[0] || a2 == GetSurname(i)[0] || a2 == GetName(i)[0] || a2 == GetSecondName(i)[0])
			{
				ShowContact(i);
			};
		};
	};

	void SearchPhone(string a)
	{
		for (int i = 0; i < count; i++)
			if (a == GetPhoneNumber(i))
			{
				ShowContact(i);
			}
	};

	void ShowContacts()
	{
		UpOut();
		for (int i = 0; i < count; i++)
			ShowContact(i);
	};

	void ShowContact(int i)
	{
		Ncout << left << setw(3);
		if (GetFAV(i) == 1)cout << char(42);
		else cout << " ";
		cout << setw(4) << i + 1
			<< setw(15 + 3) << GetSurname(i)
			<< setw(10 + 3) << GetName(i)
			<< setw(15 + 3) << GetSecondName(i)
			<< setw(14 + 5) << GetPhoneNumber(i)
			<< setw(13 + 5) << GetBD(i)
			<< endl;;
	};

	void ShowFAV()
	{
		for (int i = 0; i < count; i++)
			if (GetFAV(i) == 1) ShowContact(i);
			
	};

	int GetCount()
	{
		return count;
	};

	void FILEOpen()
	{
		fstream fs;
		fs.open(FILE, fstream::in);
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
					if (Surname[z] == "+")SetFAV(1,z);
					else SetFAV(0, z);
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

	void FILESave()
	{
		fstream fs;
		fs.open(FILE, fstream::out);
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
				if (GetFAV(z) == 1) fs << "+" << " ";
				else fs << "_" << " ";
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
	bool GetFAV( int i)
	{
		return FAV[i];
	};

};

//int Contact::count = 0;

int main()
{
	setlocale(LC_ALL, "ru");
	Contact a;
	char menu= 'a';

	while (1)
	{
		system("cls");
		Menuup;
		a.ShowContacts();
		cout << endl;

		if (a.GetCount() == 0)
		{
			while ( menu != '1' && menu != '2')
			{
				cout << "1.Открыть файл" << endl
					<< "2.Добавить контакт" << endl
					<< endl
					<< "0.Выйти из программы" << endl;
				cin >>  menu;
				switch (menu)
				{
				case '1': {a.FILEOpen(); a.Sort(); break; }
				case '2': 
				{
					string Ent[5];
					int c=0;

					cout << "Обратите вниманий!ФИО-обязательное для заполнения поле." << endl
						<< "!Если пункт не требует заполнения введите - " << endl
						<< endl;

					cout << left;
					Ncout << setw(10) << "Фамилия:";
					RUcin >> Ent[c];
					c++;
					

					Ncout << setw(10) << "Имя:";
					RUcin >> Ent[c];
					c++;

					Ncout << setw(10) << "Отчество:";
					RUcin >> Ent[c];
					c++;

					//ФИО является обязательной информацией

					Ncout << setw(11) << "Номер тел.:";
					RUcin >> Ent[c];
					c++;

					Ncout << setw(11) << "Дата рож.:";
					RUcin >> Ent[c];
					
					a.AddContact(Ent[0], Ent[1], Ent[2], Ent[3], Ent[4]);
					break;
				}
				case '0': exit(0);
				}
			};
		}
		else
		{
			cout << endl;
			cout << "1.Добавить контакт" << endl
				 << "2.Найти контакт" << endl
				 << "3.Изменить контакт" << endl
				 << "4.Сохранить контакты" << endl
				 << "5.Показать избранных"<<endl
				 << endl
				 << "0.Выйти из программы" << endl;
			cout << endl;
			cin >> menu;

			switch (menu)
			{
			case '1':{
						system("cls");
						string Ent[5];
						int c = 0;

						cout << "Обратите вниманий!ФИО-обязательное для заполнения поле." << endl
							<< "!Если пункт не требует заполнения введите - " << endl
							<< endl;

						cout << left;
						Ncout << setw(10) << "Фамилия:";
						RUcin >> Ent[c];
						c++;


						Ncout << setw(10) << "Имя:";
						RUcin >> Ent[c];
						c++;

						Ncout << setw(10) << "Отчество:";
						RUcin >> Ent[c];
						c++;

						//ФИО является обязательной информацией

						Ncout << setw(11) << "Номер тел.:";
						RUcin >> Ent[c];
						c++;

						Ncout << setw(11) << "Дата рож.:";
						RUcin >> Ent[c];

						a.AddContact(Ent[0], Ent[1], Ent[2], Ent[3], Ent[4]);
						break;
					 }
			case '2':{
						system("cls");
						cout << "1.Найти по ФИО" << endl
							<< "2.Найти по телефону" << endl
							<< "3.Найти по первой букве" << endl
							<< endl
							<< "0.Выйти из программы" << endl;
						cin >> menu;
						switch (menu)
						{
						case '1'://найти по фио
						{
							system("cls");
							cout << "Введите Имя или Фамилию:"<<endl;
							string Search;
							RUcin >> Search;
							KODNORM;

							system("cls");

							a.UpOut();

							a.Search(Search);
							cout << endl<<endl;
							system("pause");
							break;

						}
						case '2':
						{
							system("cls");
							cout << "Введите номер телефона:";
							string PN;//PhoneNumber
							RUcin >> PN;
							KODNORM;
							cout << endl << endl;
							a.UpOut();
							a.SearchPhone(PN);
							

							
							cout << endl << endl;


							system("pause");
							break;
						};
						case '3':
						{
							system("cls");
							cout << "Введите первую букву ФИО:";
							char BUKVA;
							RUcin >> BUKVA;
							KODNORM;
							cout << endl << endl;
							a.UpOut();
							a.SearchChar(BUKVA);
							cout << endl << endl;

							system("pause");
							break;
						};
						case '0':exit(0);
						};
						break;
					 }
			case '3':
			{
				int i;

				system("cls");

				a.ShowContacts();
				cout << endl << endl;

				cout << "Введите номер контакта:" << endl;

				cin >> i;
				i--;
				system("cls");

				a.UpOut();
				a.ShowContact(i);

				cout << endl
					 << endl
					 << "1.Переименовать"<<endl;
				if (a.GetFAV(i) == 1)cout << "2.Удалить из избранных";
				else cout << "2.Добавить в избранное";
				cout << endl
					 << "3.Удалить контакт"<<endl
					 <<endl
					 << "0.Выйти из программы";

				cin >> menu;

				switch (menu)
				{
				case '1':
				{
					system("cls");

					string b[5];
					int Number = 0;
					int y = 2;

					cout << "!Если пункт не требует изменения введите -" << endl << endl;

					Ncout << setw(17) << "Старая фамилия:" << a.GetSurname(i)
						<< "     " << "\tНовая фамилия:\t";
					RUcin >> b[Number++];

					Ncout << setw(17) << "Старое имя:" << a.GetName(i)
						<< "     " << "\tНовое имя:\t";
					RUcin >> b[Number++];

					Ncout << setw(17) << "Старое Отчество:" << a.GetSecondName(i)
						<< "     " << "\tНовое Отчество:\t";
					RUcin >> b[Number++];

					Ncout << setw(17) << "Старый телефон:" << a.GetPhoneNumber(i)
						<< "     " << "\tНовый телефон:\t";
					RUcin >> b[Number++];

					Ncout << setw(17) << "Старая дата рож.:" << a.GetBD(i)
						<< "     " << "\tНовая дата рож.:";
					RUcin >> b[Number++];
					SetConsoleCP(866);

					while ((y != 0) && (y != 1))
					{
						cout << "Принять изменения?(1-ДА/0-НЕТ)" << endl;
						cin >> y;
					};
					if (y == 1)
						a.SetContact(i, b);
					break;
				};
				case '2':
				{
					a.SetFAV(((a.GetFAV(i) + 1) % 2), i);
					break;
				};
				case '3':
				{
					char y='2';
					while ((y != '0') && (y != '1'))
					{
						cout << endl << "Удалить контакт №" << i << "?(1-ДА/0-НЕТ)" << endl;
						cin >> y;
					};
					if (y == '1')
					a.DeleteContact(i);
					break;
				};
				case '0':exit(0);
				};

				break;
			};
			case '4':
			{
				a.FILESave();
				break;
			};
			case '5':
			{
				system("cls");
				a.UpOut();
				for (int i = 0; i < a.GetCount(); i++)
				{
					if (a.GetFAV(i) == 1)a.ShowContact(i);
				};
				cout << endl << endl;

				system("pause");
				break;
			};
			case '0':exit(0);
			}

		};

	}

	

	return 0;
}