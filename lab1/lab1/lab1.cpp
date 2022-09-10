#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string inputStr(string path)
{

    ifstream fin(path);
    string tempStr;
    string inputStr = "";
    if (fin.is_open())
    {
        while (getline(fin, tempStr))
        {
            inputStr += tempStr;
        }
    }
    fin.close();
    return inputStr;
}

void OutputStr(string path, string result)
{

    ofstream fout(path);
    if (fout.is_open())
    {
        fout << result;
    }
    fout.close();

}

string decode(string word)
{
    if (word.size() > 2)
    {
        string result = word.substr(word.length() - 3, 3) + word;
        result = result.replace(result.length() - 3, 3, 0, ' ');
        return result;
    }
    else
    {
        reverse(word.begin(), word.end());
        return word;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    /*string path;
    cin >> path;*/

    string text = inputStr("input.txt");
    string result = decode(text);
    OutputStr("output.txt", result);


}