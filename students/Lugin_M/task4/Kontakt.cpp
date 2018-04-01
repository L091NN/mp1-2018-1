#include"Kontakt.h"

int Kontakt::count = 0;

int main()
{
	int menu;
	setlocale(LC_ALL, "ru");
	Kontakt a;
	string t = "алокс";

	if (int(t[0]) > -33) t[0] = char(int(t[0]) - 32);

	cout << (int)t[0]<< t<<sizeof(Kontakt);

	for (int i = 0; i < 256; i++)
		cout << i <<"  "<<char(i) << endl;









	system("pause");
	return 0;
}