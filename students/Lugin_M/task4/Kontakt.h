#pragma once
#include<iostream> 
#include<math.h> 
#include<string> 
#include<locale> 
#include<iomanip>
#include<fstream>
#define NumberofMassive 100;

using namespace std;

class Kontakt
{
private:
	static int count;
	string Surname[100];
	string Name[100];
	string SecondName[100];
	string PhoneNumber[100];
	string BD[100];//день рождения 
			  //jdi 
public:
	Kontakt()
	{

	};
	~Kontakt()
	{

	};
	void SetSurname(string Surname, int i)
	{
		this->Surname[i] = "";
		this->Surname[i] = Surname;
	};
	void SetName(string Name, int i)
	{
		this->Name[i] = "";
		this->Name[i] = Name;
	};
	void SetSecondName(string SecondName, int i)
	{
		this->SecondName[i] = "";
		this->SecondName[i] = SecondName;
	};
	void SetPhoneNumber(string PhoneNumber, int i)
	{
		this->PhoneNumber[i] = "";
		this->PhoneNumber[i] = PhoneNumber;
	};
	void SetBD(string BD, int i)
	{
		this->BD[i] = "";
		this->BD[i] = BD;
	};

	void AddContact()
	{
		count++;//Количество Контактов

		string Ent;

		system("cls");

		cout << left;
		cout << setw(10)<<"Фамилия:";
		cin >> Ent;
		SetSurname(Ent,count-1);

		cout << setw(10) << "Имя:";
		cin >> Ent;
		SetName(Ent, count-1);

		cout << setw(10) << "Отчество:";
		cin >> Ent;
		SetSecondName(Ent, count-1);

		//ФИО является обязательгой информацией

		cout << setw(11) << "Номер тел.:";
		cin >> Ent;
		SetPhoneNumber(Ent, count-1);

		cout << setw(11) << "Дата рож.:";
		cin >> Ent;
		SetBD(Ent, count-1);
		

	};

	void ChangeContact()
	{

	};

	void Sorting()
	{

	};


	void UpOut()
		{
			system("cls");
	cout << left << setw(3) << "Из."
		<< setw(4) << "№"
		<< setw(15 + 3) << "Фамилия"
		<< setw(10 + 3) << "Имя"
		<< setw(15 + 3) << "Отчество"
		<< setw(14 + 5) << "Номер телефона"
		<< setw(13 + 5) << "дата рождения"
		<< endl;
		};
	//шапка вывода
	void ShowConact()
	{
		UpOut();
		for (int i = 0; i < count; i++)
		{
			cout << left << setw(3) << char(42)
				 << setw(4) << i + 1
				 << setw(15 + 3) << GetSurname(i)
				 << setw(10 + 3) << GetName(i)
				 << setw(15 + 3) << GetSecondName(i)
				 << setw(14 + 5) << GetPhoneNumber(i)
				 << setw(13 + 5) << GetBD(i)
			 	 << endl;
		};

	};

	void SaveKontakts()
	{
		ofstream fout;
		fout.open("Kontakts.txt",ofstream::app);
		if (!fout.is_open())
			cout << "Файл не открылся" << endl;
		else
		for(int i=0;i<count;i++)
		fout << Surname[i] <<" "<< Name[i] <<" " << SecondName[i] << " " << PhoneNumber[i] << " " << BD[i] << endl;
		fout.close();

	};


	int GetCount()
	{
		return count;
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