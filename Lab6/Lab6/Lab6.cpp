// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream> 
using namespace std;
typedef BOOL(*function)();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HINSTANCE hLib = LoadLibraryA("../Debug/dll.dll");
	if (hLib == NULL)
		printf("Error loading library\n");
	else
	{
		function SetHook = (function)GetProcAddress(hLib, "?SetHook@@YAHXZ");
		function DeleteHook = (function)GetProcAddress(hLib, "?DeleteHook@@YAHXZ");
		if (SetHook == NULL || DeleteHook == NULL)
		{
			printf("Error dll import.\n");
			FreeLibrary(hLib);
		}
		else
		{
			if (SetHook())
			{
				printf("Proc hooked.\nPress any Key to unhook.\n");
				_getch();
				if (DeleteHook())
					printf("Unhooked.\n");
				else
					printf("Error unsetting.\n");
			}
			else
				printf("Error while setting hook.\n");
		}
	}
	printf("Press any key to exit program.\n");
	_getch();
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
