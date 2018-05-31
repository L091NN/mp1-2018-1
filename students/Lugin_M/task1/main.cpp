#include <iostream>
#include <locale>

using namespace std;

class KON
{
	double kg;
public:
	KON(double kg=1.0)
	{
		this->kg = kg;
	}
	void SetKG(double kg)
	{
		this->kg = kg;
	}

	double Karat()
	{
		return 5000 * kg;
	}

	double mg()
	{
		return 1000 * kg;
	}

	double Tonn()
	{
		return kg * 0.001;
	}

	double lb()
	{
		return kg * 2.2046226218;
	}

	double oz()
	{
		return kg * 35.27396194958;
	}

	double GetKG()
	{
		return kg;
	}

};

int main()
{
	setlocale(LC_ALL, "ru");
  cout << "Hello!" << endl;
  KON a;
  string menu;

  while (1)
  {
	  system("cls");
	  cout << "Текущий вес в килограммах: " << a.GetKG() << endl << endl;
	  cout << ' ' << a.GetKG() << " kg = " << a.Karat() << " karat" << endl;
	  cout << ' ' << a.GetKG() << " kg = " << a.oz() << " oz" << endl;
	  cout << ' ' << a.GetKG() << " kg = " << a.Tonn() << " tonn" << endl;
	  cout << ' ' << a.GetKG() << " kg = " << a.lb() << " lb" << endl;
	  cout << ' ' << a.GetKG() << " kg = " << a.mg() << " mg" << endl;

	  cout << endl;

	  cout << "Введите change чтобы поменять значение киллограмм или exit для выхода..." << endl;

	  cin >> menu;

	  if (menu == "change")
	  {
		  system("cls");
		  cout << "Текущий вес в килограммах: ";
		  double postavte4plz;
		  cin >> postavte4plz;
		  a.SetKG(postavte4plz);
	  }
	  if (menu == "exit")
	  {
		  exit(0);
	  }
  }
  return 0;
}
