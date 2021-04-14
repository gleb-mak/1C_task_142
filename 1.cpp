#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Data
{
	int val;
	int x_index;
	int y_index;
};

vector<Data> LCS(vector<int>& x, vector<int>& y)
{
	int m = x.size();
	int n = y.size();
	vector<vector<int>> lcs(m, vector<int>(n));
	vector<vector<pair<int, int>>> prev(m, vector<pair<int, int>>(n));
	for (int i = 0; i < m; ++i)
	{
		lcs[i][0] = 0;
	}
	for (int i = 1; i < n; ++i)
	{
		lcs[0][i] = 0;
	}
	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (x[i] == y[j])
			{
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			}
			else
			{
				lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
			}
		}
	}
	vector<Data> ans;
	vector<int> x_indexs;
	vector<int> y_indexs;
	n = x.size() - 1;
	m = y.size() - 1;
	while (n >= 0 && m >= 0)
	{
		if (x[n] == y[m])
		{
			ans.push_back({x[n], n ,m});
			n--;
			m--;
		}
		else if (lcs[n - 1][m] > lcs[n][m - 1])
		{
			n--;
		}
		else
		{
			m--;
		}
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

void readVector(FILE* f, vector<int>& a)
{
    char tmp;
    tmp = getc(f);
    while (tmp != EOF)
    {
		tmp = tmp - 48;
        a.push_back((int)tmp);
        tmp = getc(f);
    }
}

int main(int argc, char** argv)
{
    FILE* old_file;
    FILE* new_file;
    if (argc != 3)
    {
        cout << "Введите два аргумента: название старого, а затем название нового" << endl;
        return -1;
    }
    else
    {
        old_file = fopen(argv[1], "r");
        new_file = fopen(argv[2], "r");
        if (old_file == NULL)
        {
            cout << "Ошибка открытия файлов" << endl;
            return -2;
        }
        if (new_file == NULL)
        {
            cout << "Ошибка открытия файлов" << endl;
            fclose(old_file);
            return -3;
        }
    }
    vector<int> of_container;
    vector<int> nf_container;

    readVector(old_file, of_container);
    fclose(old_file);
    readVector(new_file, nf_container);
    fclose(new_file);
	
	of_container.erase(of_container.begin() + of_container.size() - 1);
	nf_container.erase(nf_container.begin() + nf_container.size() - 1);

    cout<< "Старый файл" << endl;
    for (auto i = of_container.begin(); i != of_container.end(); i++)
    {
        cout << *i;
    }

    cout << "\n";
    cout << "Новый файл" << endl;

    for (auto i = nf_container.begin(); i != nf_container.end(); i++)
    {
        cout << *i;
    }
	vector<Data> res = LCS(of_container, nf_container);
	// for (int i = 0; i < res.size(); ++i)
	// {
	// 	cout << res[i].x_index << " ";
	// }
	vector<int> del;
	vector<pair<int,int>> add;
	int j = 0;
	int i = 0;
	while(i < of_container.size())
	{
		if (i <= res[res.size() - 1].x_index)
        {
			if (i == res[i].x_index)
			{
				i++;
				continue;
			}
			while ((i + j) != res[i].x_index)
			{
				del.push_back(i + j);
				j++;
			}
		}
        else
        {
            del.push_back(i);
        }
		i++;
	}
	j = 0;
	i = 0;
    while (i < nf_container.size())
    {
		if (i <= res[res.size() - 1].y_index)
		{
			if (i == res[i].y_index)
			{
				i++;
				continue;
			}
			while ((i + j) != res[i].y_index)
			{   
				add.push_back(make_pair(i + j, nf_container[i]));
				j++;
			}
		}
		else
		{
			add.push_back(make_pair(i, nf_container[i]));
		}
		i++;
    }
	ofstream fout;
	fout.open("diff.txt");
	for (int i = 0; i < del.size(); ++i)
	{
		fout << del[i] << " ";
	}
	fout << "\n";
	for (int i = 0; i < add.size(); ++i)
	{
		fout << add[i].first << " " << add[i].second << " ";
	}
	fout.close();
	// for (int i = 0; i < LCS(of_container, nf_container).size(); ++i)
	// 	cout << LCS(of_container, nf_container)[i] << " ";
    return 0;
}

