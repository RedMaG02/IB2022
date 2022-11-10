// lab8(2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <regex>

using namespace std;

class ChineseWall
{
	map<int, int> _firms; // obj : firm
	map<int, int> _conflictClasses; // firm : class
	vector < vector < set<int>>> _subjects;
	vector < vector < set<int>>> _objects;
	vector<int> _subjIds;
	vector<int> _objIds;

public:
	ChineseWall()
	{
	}

	ChineseWall(vector<int> objs, vector<int> subjs, map<int, int> firms, map<int, int> conflictClasses)
	{
		_firms = firms;
		_conflictClasses = conflictClasses;

		_objects.resize(objs.size());
		for (int i = 0; i < objs.size(); i++)
		{
			_objects[i].resize(2);
			_objIds.push_back(objs[i]);
		}

		_subjects.resize(subjs.size());
		for (int i = 0; i < subjs.size(); i++)
		{
			_subjects[i].resize(2);
			_subjIds.push_back(subjs[i]);
		}

	}

	bool ReadObject(int sub, int obj)
	{

		//int subjId = _subjIds[sub];
		int subjId = find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin();
		int objId = find(_objIds.begin(), _objIds.end(), obj) - _objIds.begin();
		int objFirm = _firms[obj];
		int objConflictClass = _conflictClasses[objFirm];

		for (int o : _subjects[subjId][0])
		{
			if (_firms[o] != objFirm && _conflictClasses[_firms[o]] == objConflictClass)
			{
				return false;
			}
		}

		_subjects[subjId][0].insert(obj);
		_objects[objId][0].insert(sub);
		return true;
	}

	bool WriteObject(int sub, int obj)
	{
		if (_subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][0].empty())
		{
			_subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][0].insert(obj);
			_subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][1].insert(obj);
			_objects[find(_objIds.begin(), _objIds.end(), obj) - _objIds.begin()][0].insert(sub);
			_objects[find(_objIds.begin(), _objIds.end(), obj) - _objIds.begin()][1].insert(sub);
			return true;
		}
		else
		{
			auto firstobj = *_subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][0].begin();
			for (auto obj : _subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][0])
			{
				if (_firms[firstobj] != _firms[obj])
				{
					return false;
				}

			}

			_subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][0].insert(obj);
			_subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][1].insert(obj);
			_objects[find(_objIds.begin(), _objIds.end(), obj) - _objIds.begin()][0].insert(sub);
			_objects[find(_objIds.begin(), _objIds.end(), obj) - _objIds.begin()][1].insert(sub);
			return true;
		}
	}

	void DropHistory()
	{

		for (int i = 0; i < _subjects.size(); i++)
		{
			_subjects[i][0].clear();
			_subjects[i][1].clear();
		}

		for (int i = 0; i < _objects.size(); i++)
		{
			_objects[i][0].clear();
			_objects[i][1].clear();
		}
	}

	set<int> GetBriefCase(int firm)
	{
		set<int> briefCase;

		for (auto& obj : _firms)
		{
			if (obj.second == firm)
			{
				briefCase.insert(obj.first);
			}
		}

		return briefCase;
	}

	vector < map<int, int>> GetSubjectHistory(int sub)
	{
		vector < map<int, int>> subjectHistory;
		subjectHistory.resize(2);

		for (int obj : _subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][0])
		{
			subjectHistory[0][obj] = _firms[obj];
		}

		for (int obj : _subjects[find(_subjIds.begin(), _subjIds.end(), sub) - _subjIds.begin()][1])
		{
			subjectHistory[1][obj] = _firms[obj];
		}
		return subjectHistory;
	}

	vector < set < int>> GetObjectHistory(int obj)
	{
		return _objects[find(_objIds.begin(), _objIds.end(), obj) - _objIds.begin()];
	}

};

vector<string> split(const string& input, const string& regex)
{

	// passing -1 as the submatch index parameter performs splitting
	std::regex re(regex);
	std::sregex_token_iterator
		first{ input.begin(), input.end(), re, -1 },
		last;
	return { first, last };

}

int main()
{
	ChineseWall chinaWall;
	map <string, int> commandList = { {"START",1},{"READ",2},{"WRITE",3},{"REPORTS",4},{"REPORTO",5} ,{"BRIEFCASE",6} };
	ifstream input("input.txt");
	if (input.is_open())
	{
		vector<int> objs;
		vector<int> subjs;
		map<int, int> firms;
		map<int, int> conflictClasses;
		string tempString;
		vector<string> tempStringVec;
		getline(input, tempString);
		tempStringVec = split(tempString, " ");

		for (int i = 1; i < tempStringVec.size(); i++)
		{
			objs.push_back(stoi(tempStringVec[i]));
		}

		getline(input, tempString);
		tempStringVec = split(tempString, " ");

		for (int i = 1; i < tempStringVec.size(); i++)
		{
			subjs.push_back(stoi(tempStringVec[i]));
		}

		bool flag = true;

		while (getline(input, tempString))
		{
			if (tempString == "e")
			{
				flag = false;
			}
			else
			{
				if (flag)
				{
					tempStringVec = split(tempString, " ");
					firms[stoi(tempStringVec[0])] = stoi(tempStringVec[1]);
				}
				else
				{
					tempStringVec = split(tempString, " ");
					conflictClasses[stoi(tempStringVec[0])] = stoi(tempStringVec[1]);
				}
			}
		}

		chinaWall = ChineseWall(objs, subjs, firms, conflictClasses);
	}

	string tempString = "";


	cout << "START" << endl;
	cout << "READ s o" << endl;
	cout << "WRITE s o" << endl;
	cout << "REPORTS s" << endl;
	cout << "REPORTO o" << endl;
	cout << "BRIEFCASE f" << endl;
	cout << "EXIT" << endl;

	while (tempString != "EXIT")
	{
		getline(cin, tempString);
		vector<string> tempVecString = split(tempString, " ");

		switch (commandList[tempVecString[0]])
		{
		case 1:
			chinaWall.DropHistory();
			break;
		case 2:
			if (chinaWall.ReadObject(stoi(tempVecString[1]), stoi(tempVecString[2])))
			{
				cout << "accessed" << endl;
			}
			else
			{
				cout << "refused" << endl;
			}
			break;
		case 3:
			if (chinaWall.WriteObject(stoi(tempVecString[1]), stoi(tempVecString[2])))
			{
				cout << "accessed" << endl;
			}
			else
			{
				cout << "refused" << endl;
			}
			break;
		case 4:
		{
			vector<map<int, int>> res;
			res = chinaWall.GetSubjectHistory(stoi(tempVecString[1]));

			cout << "sub readed: " << endl;

			for (auto pair : res[0])
			{
				cout << pair.first << " " << pair.second << endl;
			}

			cout << "sub writed: " << endl;

			for (auto pair : res[1])
			{
				cout << pair.first << " " << pair.second << endl;
			}

			break;
		}
		case 5:
		{
			vector<set<int>> ress;
			ress = chinaWall.GetObjectHistory(stoi(tempVecString[1]));
			cout << "obj readed by: " << endl;

			for (auto el : ress[0])
			{
				cout << el << endl;
			}

			cout << "obj writed by: " << endl;

			for (auto el : ress[1])
			{
				cout << el << endl;
			}

			break;
		}
		case 6:
			set<int> resset = chinaWall.GetBriefCase(stoi(tempVecString[1]));
			cout << "objects: " << endl;
			for (auto el : resset)
			{
				cout << el << endl;
			}
			break;
		}
	}


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
