#include<iostream>
#include<math.h>
#include<locale.h>
#define Menuup1 cout << "������� �������:";a.GetFunction();cout << "      ";cout << "���������� ��������� ����:" << a.GetNumber() << endl;cout << endl;
#define Menuup2 cout << "������� �������:";a.GetFunction();cout  << endl << endl;
#define Menuup3 cout << "������� �������:";a.GetFunction();cout << "      ";cout << "���������� ��������� ����:" << a.GetNumber() <<"      x="<< a.Getpoint()<< endl << endl;


using namespace std;

class Taylor
{
private:
	int Function;//������� �������(1-sin(x) 2-cos(x) 3-exp(x))
	int number=0;//���������� ������ ����
	double x=0.0;//����� � � ������� ���������
	double const c = 0.0;//����� ��� ������� �������
	//bool vr;//�����(0) ��� ������ �������(1)
	long double ans;//��������� ��������

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
	//���������� ������ ����
//�� ����� 20 ��� ��������(��������� ��-�� ���� ���� ��� �������������� �� 20!)
	void Setpoint(double x)
	{
		this->x = x;
	}
	//����� � � ������� ���������
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
	void Getelement( int number=0/*����� ��������*/)
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
	void SinTaylor(bool vr = 0, int number = 0, int a = -1)//����� �������� ������� ����� �������������� �������� number,
		{											   //����� �������� ��� ��������� ��� ����� �������������� number �� ������
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
					if (vr == 0)//������� � ����� ����
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
					else//��������� �� ���������
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

	void CosTaylor(bool vr = 0, int number = 0, int a = -1)//����� �������� ������� ����� �������������� �������� number,
	{											   //����� �������� ��� ��������� ��� ����� �������������� number �� ������
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
				if (vr == 0)//������� � ����� ����
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
				else//��������� �� ���������
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

	void ExpTaylor(bool vr = 0, int number = 0, int a = -1)//����� �������� ������� ����� �������������� �������� number,
	{											   //����� �������� ��� ��������� ��� ����� �������������� number �� ������
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
				if (vr == 0)//������� � ����� ����
				{
					if (i == 0)cout << "exp(c)";
					else if (i == 1)cout << "+exp(c)(x-c)";
					else cout << "+(exp(c)/" << i << "!)(x-c)^" << i;
				}
				else//��������� �� ���������
				{
					if (i > 0)fact = fact * i;
					ans = ans + (pow(x, i) / fact);
				};
			};





	};
};

int main()
{
	int menu;//��� ��������� � ����
	Taylor a;
	long double Answer;
	setlocale(LC_ALL, "ru");
	//�������������� �� ����, ������ ���� � go to)
menu:system("cls");
	Menuup1;
	cout << "1.������� �������" << endl
		<< "2.������ ���������� ���������" << endl
		<< "3.�������� ������� ����" << endl
		<< "4.�������� �������� ���" << endl
		<< "5.���������� �������� ����" << endl
		<< "6.�������� � ��������� ���������" << endl
		<< "\n0.����� �� ���������" << endl;
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
							cout << "�� �� ����.�������� �����.\n\n";
							i++;
							goto case1;
					};
					goto menu;
				}
				else //���� ���� �������� �������� ��������
					{
						cout << "1.sin(x)\n2.cos(x)\n3.exp(x)\n\n0.����� � ����";
						cin >> n;
						if (n == 1 || n == 2 || n == 3)a.SetFunction(n);
						else if (n != 0)
							 {
								system("cls");
								Menuup1;
								cout << "�� �� ����.�������� �����.\n\n";
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
					cout << "��� ���������� ������ ��������� ���������� ��������� �� ������ ��������� 20.\n\n������� ���������� ��������� ����:\n";
					cin >> n;
					if (n > 0)a.Setnumber(n);
					else 
					{
							system("cls");
							Menuup1;
							cout << "���������� ��������� ������ ���� �������������.\n\n";
							i++;
							goto case2;
					};
					goto menu;
				}
				else //���� ���� �������� �������� ��������
				{
					cout << "\n0.����� � ����\n\n������� ���������� ��������� ����:\n";
					cin >> n;
					if (n > 0)a.Setnumber(n);
					else if (n != 0)
						{
							system("cls");
							Menuup1;
							cout << "���������� ��������� ������ ���� �������������.\n\n";
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
					cout << "������� ����� ��������:";
					cin >> n;
					if (n > 0) {
						system("cls"); a.Getelement(n); cout << "\n\n����� � ����\n"; char t; cin >> t;
					}
					else
					{
						system("cls");
						Menuup1;
						cout << "����� �������� ������ ���� �������������.\n\n";
						i++;
						goto case3;
					};
					goto menu;
				}
				else //���� ���� �������� �������� ��������
				{
					cout << "\n0.����� � ����\n\n������� ����� ��������:\n";
					cin >> n;
					if (n > 0) {
						system("cls"); a.Getelement(n); cout << "\n\n����� � ����\n"; char t; cin >> t;
							   }
					else if (n != 0)
					{
						system("cls");
						Menuup1;
						cout << "����� �������� ������ ���� �������������.\n\n";
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
				cout << "\n\n����� � ����\n";
				cin >> t;
				goto menu;
		    };
	case 5: {
		double x;
		char t, m = '1';
case5:	system("cls");
		Menuup3;
		cout << "������� �������� ����� x=";
		cin >> x;
		a.Setpoint(x);
		system("cls");
		Menuup3;
		Answer = a.Getans();
		a.GetFunction();
		cout << "=" << Answer << endl << endl << "1.������ ����� x\n\n ����� � ����" << endl;
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
		cout << "������� �������� ����� x=";
		cin >> x;
		a.Setpoint(x);
		system("cls");
		Menuup3;
		Answer = a.Getans();
		cout << "�������� �� ������� �������:";
		a.GetFunction();
		cout << "=" << Answer;
		cout << "\n\n";
		switch (a.GetFunctionint())
		{
		case 1: {cout << "��������� ��������: sin(" << x << ")=" << sin(x); k = sin(x); break; };
		case 2: {cout << "��������� ��������: cos(" << x << ")=" << cos(x); k = cos(x); break; };
		case 3: {cout << "��������� ��������: exp(" << x << ")=" << exp(x); k = exp(x); break; };
		};
		cout << "\n\n���������� �� �������:" << abs(k - Answer);
		cout<<"\n\n1.������ ����� x\n\n ����� � ����" << endl;
		cin >> t;
		if (t == m) goto case6;
		else goto menu;
			};
	case 0:exit(0);
	};

	system("pause");
	 return 0;
}
