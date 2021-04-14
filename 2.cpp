#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#define BUF 100

using namespace std;

void readVector(FILE* f, vector<char>& a)
{
	char temp;
	temp = getc(f);
	while (temp != EOF)
	{
		a.push_back(temp);
		temp = getc(f);
	}
}

void readDiff(FILE* f, vector<int>& a, vector<int>& b)
{
	char temp;
	char current_number[BUF]; 
	int switcher = 1;
	while (switcher)
	{
		temp = getc(f);
		int i = 0;
		for (i = 0; temp != ' ' && temp != '\n' && temp != EOF; i++)
		{
			if (i >= BUF)
			{
				cout<< "увеличьте define BUF!" << endl;
				return;
			}
			current_number[i] = temp;
			temp = getc(f);
		}
		current_number[i] = '\0';
		a.push_back(atoi(current_number));
		if (temp == '\n' || temp == EOF)
			switcher = 0;
	}
	while (!switcher)
	{
		temp = getc(f);
		int i = 0;
		for (i = 0; temp != ' ' && temp != '\n' && temp != EOF; i++)
		{
			if (i >= BUF)
			{
				cout<< "увеличьте define BUF!" << endl;
				return;
			}
			current_number[i] = temp;
			temp = getc(f);
		}
		current_number[i] = '\0';
		b.push_back(atoi(current_number));
		if (temp == '\n' || temp == EOF)
			switcher = 1;

	}
	
}

void cutAway(vector<char>& of_container, vector<int>& a_container)
{
	int offset = 0;
	for (auto i : a_container)
	{
		of_container.erase(of_container.begin() + i - offset);
		offset++;		
	}
}

int main(int argc, char** argv)
{
	FILE* dif_file;
	FILE* old_file;
	if (argc != 3)
	{
		cout << "Введите два аргумента: название diff, а затем название старого" << endl;
		return -1;
	}
	else
	{
		dif_file = fopen(argv[1], "r");
		old_file = fopen(argv[2], "r");
		if (dif_file == NULL)
		{
			cout << "Ошибка открытия файлов" << endl;
			return -2;
		}
		if (old_file == NULL)
		{
			cout << "Ошибка открытия файлов" << endl;
			fclose(dif_file);
			return -3;
		}		
	}
	vector<char> of_container;
	vector<int> a_container;
	vector<int> b_container;
	
	readDiff(dif_file, a_container, b_container);
	fclose(dif_file);
	readVector(old_file, of_container);
	fclose(old_file);

	cout<< "Старый файл" << endl;
	for (auto i = of_container.begin(); i != of_container.end(); i++)
	{
		cout << *i;
	}

	cout << "\n";

	cout<< "a_container" << endl;
	for (auto i = a_container.begin(); i != a_container.end(); i++)
	{
		cout << *i << " ";
	}

	cout << "\n";
	cout << "b_container" << endl;
	
	for (auto i = b_container.begin(); i != b_container.end(); i++)
	{
		cout << *i << " ";
	}

	cout << "\n";
	cutAway(of_container, a_container);

	cout<< "Старый файл" << endl;
	for (auto i = of_container.begin(); i != of_container.end(); i++)
	{
		cout << *i;
	}

	cout << "\n";

	return 0;
}
