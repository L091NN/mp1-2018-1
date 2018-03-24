#include<iostream>
#include<math.h>
#include<locale.h>
#define Menuup1 cout << "Текущая функция:";a.GetFunction();cout << "      ";cout << "Количество Элементов ряда:" << a.GetNumber() << endl;cout << endl;
#define Menuup2 cout << "Текущая функция:";a.GetFunction();cout  << endl << endl;
#define Menuup3 cout << "Текущая функция:";a.GetFunction();cout << "      ";cout << "Количество Элементов ряда:" << a.GetNumber() <<"      x="<< a.Getpoint()<< endl << endl;


using namespace std;

class Taylor
{
private:
	int Function;//текущая функция(1-sin(x) 2-cos(x) 3-exp(x))
	int number=0;//количество членов ряда
	double x=0.0;//точка х в формуле Маклорена
	double const c = 0.0;//точка для формулы Тейлора
	//bool vr;//вывод(0) или расчет функции(1)
	long double ans;//результат подсчета

public:
	Taylor()
	{

	};
	~Taylor()
	{

	};
	void SetFunction(int Function)
	{
		this->Function = Function;
	};
	//1-sin(x) 2-cos(x) 3-exp(x)
	void Setnumber(int number)
	{
		this->number = number;
	};
	//количество членов ряда
//не более 20 при подсчете(факториал из-за лонг лонг инт подсчитывается до 20!)
	void Setpoint(double x)
	{
		this->x = x;
	}
	//точка х в формуле Маклорена
	long double Getans()
	{
		ans = 0.0;
		switch (Function)
		{
		case 1: {SinTaylor(1); break; };
		case 2: {CosTaylor(1); break; };
		case 3: {ExpTaylor(1); break; };
		}
		return ans;
	};
	void GetFunction()
	{
		switch (Function)
		{
		case 1: {cout << "sin(x)"; break; };
		case 2: {cout << "cos(x)"; break; };
		case 3: {cout << "exp(x)"; break; };
		default:cout << "No Function";
		}
	};
	int GetFunctionint()
	{
		return Function;
	};
	int GetNumber()
	{	
		return number;
	};
	void Getelement( int number=0/*номер элемента*/)
	{
		switch (Function)
		{
		case 1: {SinTaylor(0,number,number-1); break; };
		case 2: {CosTaylor(0, number, number - 1); break; };
		case 3: {ExpTaylor(0, number, number - 1); break; };
		}
	};
	void Getsequence()
	{
		switch (Function)
		{
		case 1: {SinTaylor(0); break; };
		case 2: {CosTaylor(0); break; };
		case 3: {ExpTaylor(0); break; };
		}
	};
	double Getpoint()
	{
		return x;
	};

	protected:
	void SinTaylor(bool vr = 0, int number = 0, int a = -1)//чтобы получить элемент будет использоваться входящий number,
		{											   //чтобы получить или посчитать ряд будет использоваться number из класса
			long long int fact = 1;
			if (a != -1)
				for (int i = a; i < number; i++)
				{
					if (i == 0)cout << "sin(c)";
					else if (i == 1)cout << "cos(c)(x-c)";
					else switch (i % 4)
					{
					case 0: {cout << "(sin(c)/" << i << "!)(x-c)^" << i; break; };
					case 1: {cout << "(cos(c)/" << i << "!)(x-c)^" << i; break; };
					case 2: {cout << "-(sin(c)/" << i << "!)(x-c)^" << i; break; };
					case 3: {cout << "-(cos(c)/" << i << "!)(x-c)^" << i; break; };
					};


				}

			else
				for (int i = 0; i < this->number; i++)
				{
					if (vr == 0)//вывести в общем виде
					{
						if (i == 0)cout << "sin(c)";
						else if (i == 1)cout << "+cos(c)(x-c)";
						else switch (i % 4)
						{
						case 0: {cout << "+(sin(c)/" << i << "!)(x-c)^" << i; break; };
						case 1: {cout << "+(cos(c)/" << i << "!)(x-c)^" << i; break; };
						case 2: {cout << "-(sin(c)/" << i << "!)(x-c)^" << i; break; };
						case 3: {cout << "-(cos(c)/" << i << "!)(x-c)^" << i; break; };
						};
					}
					else//посчитать по Маклорену
					{
						if (i > 0)fact = fact * i;
						switch (i % 4)
						{
						case 1: {ans = ans + (pow(x, i) / fact); break; };
						case 3: {ans = ans - (pow(x, i) / fact); break; };
						};
					};
				};





		};

	void CosTaylor(bool vr = 0, int number = 0, int a = -1)//чтобы получить элемент будет использоваться входящий number,
	{											   //чтобы получить или посчитать ряд будет использоваться number из класса
		long long int fact = 1;
		if (a != -1)
			for (int i = a; i < number; i++)
			{
				if (i == 0)cout << "cos(c)";
				else if (i == 1)cout << "-sin(c)(x-c)";
				else switch (i % 4)
				{
				case 0: {cout << "(cos(c)/" << i << "!)(x-c)^" << i; break; };
				case 1: {cout << "-(sin(c)/" << i << "!)(x-c)^" << i; break; };
				case 2: {cout << "-(cos(c)/" << i << "!)(x-c)^" << i; break; };
				case 3: {cout << "(sin(c)/" << i << "!)(x-c)^" << i; break; };
				};


			}

		else
			for (int i = 0; i < this->number; i++)
			{
				if (vr == 0)//вывести в общем виде
				{
					if (i == 0)cout << "cos(c)";
					else if (i == 1)cout << "-sin(c)(x-c)";
					else switch (i % 4)
					{
					case 0: {cout << "+(cos(c)/" << i << "!)(x-c)^" << i; break; };
					case 1: {cout << "-(sin(c)/" << i << "!)(x-c)^" << i; break; };
					case 2: {cout << "-(cos(c)/" << i << "!)(x-c)^" << i; break; };
					case 3: {cout << "+(sin(c)/" << i << "!)(x-c)^" << i; break; };
					};
				}
				else//посчитать по Маклорену
				{	
					if (i > 0)fact = fact * i;
					switch (i % 4)
					{
					case 0: {ans = ans + (pow(x, i) / fact); break; };
					case 2: {ans = ans - (pow(x, i) / fact); break; };
					};
					
				};
			};





	};

	void ExpTaylor(bool vr = 0, int number = 0, int a = -1)//чтобы получить элемент будет использоваться входящий number,
	{											   //чтобы получить или посчитать ряд будет использоваться number из класса
		long long int fact = 1;
		if (a != -1)
			for (int i = a; i < number; i++)
			{
				if (i == 0)cout << "exp(c)";
				else if (i == 1)cout << "exp(c)(x-c)";
				else cout << "(exp(c)/" << i << "!)(x-c)^"<<i;
			}

		else
			for (int i = 0; i < this->number; i++)
			{
				if (vr == 0)//вывести в общем виде
				{
					if (i == 0)cout << "exp(c)";
					else if (i == 1)cout << "+exp(c)(x-c)";
					else cout << "+(exp(c)/" << i << "!)(x-c)^" << i;
				}
				else//посчитать по Маклорену
				{
					if (i > 0)fact = fact * i;
					ans = ans + (pow(x, i) / fact);
				};
			};





	};
};

int main()
{
	int menu;//для навигации в меню
	Taylor a;
	long double Answer;
	setlocale(LC_ALL, "ru");
	//выпендриваться не буду, создам меню с go to)
menu:system("cls");
	Menuup1;
	cout << "1.Выбрать Функцию" << endl
		<< "2.Задать количество элементов" << endl
		<< "3.Показать элемент ряда" << endl
		<< "4.Показать заданный ряд" << endl
		<< "5.Рассчитать значение ряда" << endl
		<< "6.Сравнить с эталонным значением" << endl
		<< "\n0.Выйти из программы" << endl;
	cin >> menu;
	switch (menu)
	{
	case 1: {
				system("cls");
				int n, i = 0;
				Menuup1;
case1:			if (i < 1)
				{
					cout << "1.sin(x)\n2.cos(x)\n3.exp(x)\n";
					cin >> n;
					if (n == 1 || n == 2 || n == 3)a.SetFunction(n);
					else 
					{
							system("cls");
							Menuup1;
							cout << "Ты не прав.Попробуй снова.\n\n";
							i++;
							goto case1;
					};
					goto menu;
				}
				else //если было выбранно неверное значение
					{
						cout << "1.sin(x)\n2.cos(x)\n3.exp(x)\n\n0.Выйти в меню";
						cin >> n;
						if (n == 1 || n == 2 || n == 3)a.SetFunction(n);
						else if (n != 0)
							 {
								system("cls");
								Menuup1;
								cout << "Ты не прав.Попробуй снова.\n\n";
								i++;
								goto case1;
							 };
							goto menu;
						};
	};//	case 1
	case 2: {
				system("cls");
				int n, i = 0;
				Menuup1;
case2:			if (i < 1)
				{
					cout << "Для корректной работы программы количество элементов не должно превышать 20.\n\nВведите количество элементов ряда:\n";
					cin >> n;
					if (n > 0)a.Setnumber(n);
					else 
					{
							system("cls");
							Menuup1;
							cout << "Количество элементов должно быть положительным.\n\n";
							i++;
							goto case2;
					};
					goto menu;
				}
				else //если было выбранно неверное значение
				{
					cout << "\n0.Выйти в меню\n\nВведите количество элементов ряда:\n";
					cin >> n;
					if (n > 0)a.Setnumber(n);
					else if (n != 0)
						{
							system("cls");
							Menuup1;
							cout << "Количество элементов должно быть положительным.\n\n";
							i++;
							goto case2;
						};
					goto menu;
				};

			};
	case 3: {
				system("cls");
				int n,i=0;
				Menuup2;
case3:			if (i < 1)
				{
					cout << "Введите номер элемента:";
					cin >> n;
					if (n > 0) {
						system("cls"); a.Getelement(n); cout << "\n\nВыйти в меню\n"; char t; cin >> t;
					}
					else
					{
						system("cls");
						Menuup1;
						cout << "Номер элемента должен быть положительным.\n\n";
						i++;
						goto case3;
					};
					goto menu;
				}
				else //если было выбранно неверное значение
				{
					cout << "\n0.Выйти в меню\n\nВведите номер элемента:\n";
					cin >> n;
					if (n > 0) {
						system("cls"); a.Getelement(n); cout << "\n\nВыйти в меню\n"; char t; cin >> t;
							   }
					else if (n != 0)
					{
						system("cls");
						Menuup1;
						cout << "Номер элемента должен быть положительным.\n\n";
						i++;
						goto case3;
					};
					goto menu;
				};


			};
	case 4: {
				system("cls");
				Menuup1;
				a.Getsequence();
				char t;
				cout << "\n\nВыйти в меню\n";
				cin >> t;
				goto menu;
		    };
	case 5: {
		double x;
		char t, m = '1';
case5:	system("cls");
		Menuup3;
		cout << "Введите значение точки x=";
		cin >> x;
		a.Setpoint(x);
		system("cls");
		Menuup3;
		Answer = a.Getans();
		a.GetFunction();
		cout << "=" << Answer << endl << endl << "1.задать новый x\n\n Выйти в меню" << endl;
		cin >> t;
		if (t == m) goto case5;
		else goto menu;

		

		system("pause");
		
			};
	case 6: {
		double x,k;
		char t, m = '1';
case6:	system("cls");
		Menuup3;
		cout << "Введите значение точки x=";
		cin >> x;
		a.Setpoint(x);
		system("cls");
		Menuup3;
		Answer = a.Getans();
		cout << "Значение по формуле Тейлора:";
		a.GetFunction();
		cout << "=" << Answer;
		cout << "\n\n";
		switch (a.GetFunctionint())
		{
		case 1: {cout << "Эталонное значение: sin(" << x << ")=" << sin(x); k = sin(x); break; };
		case 2: {cout << "Эталонное значение: cos(" << x << ")=" << cos(x); k = cos(x); break; };
		case 3: {cout << "Эталонное значение: exp(" << x << ")=" << exp(x); k = exp(x); break; };
		};
		cout << "\n\nотклонение от эталона:" << abs(k - Answer);
		cout<<"\n\n1.задать новый x\n\n Выйти в меню" << endl;
		cin >> t;
		if (t == m) goto case6;
		else goto menu;
			};
	case 0:exit(0);
	};

	system("pause");
	 return 0;
}
