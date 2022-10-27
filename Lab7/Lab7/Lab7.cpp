// Lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <regex>
#include <map>

using namespace std;

class HarrisonModel
{
public:
    vector<vector<set<char>>> matrix;
    vector<int> idSubject;
    vector<int> idObject;
    vector<int> deletedObjects;
    vector<int> deletedSubjects;
    int n;
    int m;

    HarrisonModel()
    {
        vector<vector<set<char>>> init;
        vector<int> init2;

        matrix = init;
        idSubject = init2;
        idObject = init2;
        deletedObjects = init2;
        deletedSubjects = init2;
        n = 0;
        m = 0;
    }

    HarrisonModel(vector<vector<set<char>>> matrix)
    {
        this->matrix = matrix;
        this->n = matrix.size();

        if (matrix.size() == 0)
        {
            this->m = 0;
        }
        else
        {
            this->m = matrix[0].size();
        }

        for (int i = 0; i < n; i++)
        {
            idSubject.push_back(i);
        }

        for (int i = 0; i < m; i++)
        {
            idObject.push_back(i);
        }
        vector<int> init;
        deletedObjects = init;
        deletedSubjects = init;
    }


    void AddSubject(int j)
    {
        if (find(deletedSubjects.begin(), deletedSubjects.end(), j) != deletedSubjects.end())
        {
            deletedSubjects.erase((find(deletedSubjects.begin(), deletedSubjects.end(), j)));
        }
        else
        {
            n++;
            vector<set<char>> vec;
            vec.resize(m);

            matrix.push_back(vec);
            idSubject.push_back(j);
        }
    }

    void AddObject(int j)
    {
        if (find(deletedObjects.begin(), deletedObjects.end(), j) != deletedObjects.end())
        {
            deletedObjects.erase((find(deletedObjects.begin(), deletedObjects.end(), j)));
        }
        else
        {
            m++;
            set<char> set;
            for (int i = 0; i < n; i++)
            {
                matrix[i].push_back(set);
            }

            idObject.push_back(j);
        }
    }

    void DeleteSubject(int j)
    {
        int index = find(idSubject.begin(), idSubject.end(), j) - idSubject.begin();

        if (index != idSubject.size())
        {
            /*matrix.erase(matrix.begin() + index);*/
            vector<set<char>> empty;
            empty.resize(m);
            matrix[index] = empty;
            deletedSubjects.push_back(j);
        }

    }

    void DeleteObject(int j)
    {
        int index = find(idObject.begin(), idObject.end(), j) - idObject.begin();

        if (index != idObject.size())
        {
            for (int i = 0; i < n; i++)
            {
                set<char> emptySet;
                matrix[i][index] = emptySet;
            }

            deletedObjects.push_back(j);
        }
    }

    void AddEnter(char p, int i, int j)
    {
        if (find(deletedSubjects.begin(), deletedSubjects.end(), i) == deletedSubjects.end() && find(deletedObjects.begin(), deletedObjects.end(), j) == deletedObjects.end())
        {
            int index = find(idSubject.begin(), idSubject.end(), i) - idSubject.begin();
            int jndex = find(idObject.begin(), idObject.end(), j) - idObject.begin();

            if ((index != idSubject.size()) && (jndex != idObject.size()))
            {
                matrix[index][jndex].insert(p);
            }
        }

    }

    void DeleteEnter(char p, int i, int j)
    {
        if (find(deletedSubjects.begin(), deletedSubjects.end(), i) == deletedSubjects.end() && find(deletedObjects.begin(), deletedObjects.end(), j) == deletedObjects.end())
        {
            int index = find(idSubject.begin(), idSubject.end(), i) - idSubject.begin();
            int jndex = find(idObject.begin(), idObject.end(), j) - idObject.begin();

            if ((index != idSubject.size()) && (jndex != idObject.size()))
            {
                matrix[index][jndex].erase(p);
            }
        }
    }

    bool CheckEnter(char p, int i, int j)
    {
        if (find(deletedSubjects.begin(), deletedSubjects.end(), i) == deletedSubjects.end() && find(deletedObjects.begin(), deletedObjects.end(), j) == deletedObjects.end())
        {
            int index = find(idSubject.begin(), idSubject.end(), i) - idSubject.begin();
            int jndex = find(idObject.begin(), idObject.end(), j) - idObject.begin();

            if ((index != idSubject.size()) && (jndex != idObject.size()))
            {

                return (find(matrix[index][jndex].begin(), matrix[index][jndex].end(), p) != matrix[index][jndex].end());

            }

            return false;
        }
        else
        {
            return false;
        }
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

class InterpreterForHarrison
{
    HarrisonModel systemH;
    string systemInputPath;
    string commandsInputPath;
    string outputPath;
    map <string, int> commandList = { {"cco",1},{"ccs",2},{"cdo",3},{"cds",4},{"cer",5},{"cdr",6}, {"if",7} };

public:
    InterpreterForHarrison(string systemInputPath, string commandsInputPath, string outputPath)
    {
        this->systemInputPath = systemInputPath;
        this->commandsInputPath = commandsInputPath;
        this->outputPath = outputPath;

        ifstream input(systemInputPath);

        if (input.is_open())
        {
            vector<vector<set<char>>> temp;
            systemH = HarrisonModel(temp);
            int n;
            int m;
            string nn;
            string mm;

            getline(input, nn);
            getline(input, mm);

            n = stoi(nn);
            m = stoi(mm);

            for (int k = 0; k < m; k++)
            {
                systemH.AddObject(k);
            }
            for (int i = 0; i < n; i++)
            {
                systemH.AddSubject(i);
                string tempString;
                getline(input, tempString);
                vector<string> tempVecString = split(tempString, ";");


                for (int j = 0; j < m; j++)
                {
                    /*systemH.AddObject(j);*/
                    vector<string> tempVecSet = split(tempVecString[j], " ");

                    for (int c = 0; c < tempVecSet.size(); c++)
                    {
                        systemH.AddEnter(tempVecSet[c][0], i, j);
                    }
                }
            }

            input.close();

        }

    }

    HarrisonModel GetSystemH()
    {
        return systemH;
    }

    void CommandsInterpreter()
    {
        ifstream input(commandsInputPath);



        if (input.is_open())
        {
            string tempString;
            while (getline(input, tempString))
            {
                vector<string> tempVecString = split(tempString, " ");

                if (tempVecString[0] == "if")
                {
                    if (systemH.CheckEnter(tempVecString[1][0], atoi(tempVecString[2].c_str()), atoi(tempVecString[3].c_str())))
                    {
                        tempVecString[0] = tempVecString[4];
                    }
                    else
                    {
                        continue;
                    }
                }

                // commands
                // 1 -  cco i
                // 2 -  ccs i
                // 3 -  cdo i
                // 4 -  cds i
                // 5 -  cer p i j
                // 6 -  cdr p i j 
                // 7 -  if p i j com

                switch (commandList[tempVecString[0]])
                {
                case 1:
                    systemH.AddObject(atoi(tempVecString[1].c_str()));
                    break;
                case 2:
                    systemH.AddSubject(atoi(tempVecString[1].c_str()));
                    break;
                case 3:
                    systemH.DeleteObject(atoi(tempVecString[1].c_str()));
                    break;
                case 4:
                    systemH.DeleteSubject(atoi(tempVecString[1].c_str()));
                    break;
                case 5:
                    systemH.AddEnter(tempVecString[1][0], atoi(tempVecString[2].c_str()), atoi(tempVecString[3].c_str()));
                    break;
                case 6:
                    systemH.DeleteEnter(tempVecString[1][0], atoi(tempVecString[2].c_str()), atoi(tempVecString[3].c_str()));
                    break;
                }

            }
            input.close();
        }
    }

    void TypeSystem()
    {
        ofstream output(outputPath);

        output << "  ";
        for (int i = 0; i < systemH.idObject.size(); i++)
        {
            output << systemH.idObject[i] << "     ";
        }
        output << endl << endl;

        for (int i = 0; i < systemH.n; i++)
        {
            output << systemH.idSubject[i] << " ";
            for (int j = 0; j < systemH.m; j++)
            {
                for (char const& rule : systemH.matrix[i][j])
                {
                    output << rule;
                }
                output << ";  ";
            }
            output << endl;
        }

        output.close();

    }

};


//a) список объектов, доступ к которым не задан никакому субъекту(ни
//по чтению, ни по записи);
//b) список субъектов, не обращающихся ни к каким объектам(ни по
//чтению, ни по записи);
//c) список субъектов, имеющих полный доступ ко всем объектам;
//d) список C1, C2, …, Ct, где Ci – список субъектов, которые все имеют
//право записи в некоторый один объект oj(т.е.все субъекты из Ci могут
//    вступить в потенциальный конфликт при одновременной записи в объект oj);
//e) список субъектов, каждый из которых имеет полный доступ только к
//одному объекту, а к другим объектам доступа либо нет, либо только право
//чтения.
class HarrisonSelect
{
public:
    HarrisonModel systemH;

    HarrisonSelect()
    {
        this->systemH = HarrisonModel();
    };

    HarrisonSelect(HarrisonModel system)
    {
        this->systemH = system;
    };

    vector<int> GetFreeObjects()
    {
        vector<int> objects;

        for (int j = 0; j < systemH.m; j++)
        {
            bool flag = true;

            for (int i = 0; i < systemH.n; i++)
            {
                if (!systemH.matrix[i][j].empty())
                {
                    flag = false;
                }
            }
            if (flag)
            {
                objects.push_back(systemH.idObject[j]);
            }
        }
        return objects;
    }

    vector<int> GetFreeSubjects()
    {
        vector<int> subjects;

        for (int i = 0; i < systemH.n; i++)
        {
            bool flag = true;

            for (int j = 0; j < systemH.m; j++)
            {
                if (!systemH.matrix[i][j].empty())
                {
                    flag = false;
                }
            }
            if (flag)
            {
                subjects.push_back(systemH.idSubject[i]);
            }
        }
        return subjects;
    }

    vector<int> GetFullSubjects()
    {
        vector<int> subjects;

        for (int i = 0; i < systemH.n; i++)
        {
            bool flag = true;

            for (int j = 0; j < systemH.m; j++)
            {
                if (systemH.matrix[i][j].find('r') == systemH.matrix[i][j].end() || systemH.matrix[i][j].find('w') == systemH.matrix[i][j].end())
                {
                    flag = false;
                }
            }
            if (flag)
            {
                subjects.push_back(systemH.idSubject[i]);
            }
        }
        return subjects;
    }

    vector<vector<int>> GetSubjectsLists()
    {
        vector<vector<int>> subjectsLists;

        for (int j = 0; j < systemH.m; j++)
        {
            vector<int> tempSubjects;

            for (int i = 0; i < systemH.n; i++)
            {
                if (systemH.matrix[i][j].find('w') != systemH.matrix[i][j].end())
                {
                    tempSubjects.push_back(systemH.idSubject[i]);
                }
            }

            subjectsLists.push_back(tempSubjects);
        }
        return subjectsLists;
    }

    vector<int> GetSubjectsOneFullObject()
    {
        vector<int> subjects;

        for (int i = 0; i < systemH.n; i++)
        {
            bool flag1 = false;
            bool flag2 = true;

            for (int j = 0; j < systemH.m; j++)
            {
                if (systemH.matrix[i][j].find('r') != systemH.matrix[i][j].end() && systemH.matrix[i][j].find('w') != systemH.matrix[i][j].end())
                {
                    if (flag1 == false)
                    {
                        flag1 = true;
                    }
                    else
                    {
                        flag2 = false;
                    }
                }
            }

            if (flag1 && flag2)
            {
                subjects.push_back(systemH.idSubject[i]);
            }
        }

        return subjects;
    }

};

ostream& operator<<(ostream& os, const vector<int>& input)
{
    for (auto const& i : input)
    {
        os << i << " ";
    }
    return os;
}

ostream& operator<<(ostream& os, const vector<vector<int>>& input)
{
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            os << input[i][j] << " ";
        }
        os << endl;
    }
    return os;
}


int main()
{
    InterpreterForHarrison test = InterpreterForHarrison("in1.txt", "in2.txt", "out.txt");
    test.CommandsInterpreter();
    test.TypeSystem();
    HarrisonSelect selectTest = HarrisonSelect(test.GetSystemH());
    cout << selectTest.GetFreeObjects() << endl;
    cout << selectTest.GetFreeSubjects() << endl;
    cout << selectTest.GetFullSubjects() << endl;
    cout << selectTest.GetSubjectsLists() << endl;
    cout << selectTest.GetSubjectsOneFullObject() << endl;


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
