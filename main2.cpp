#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class Rule
{
public:
    virtual string rule(string s) = 0;
};
class NormalizeCasing : public Rule
{
public:
    string rule(string s) override
    {
        string temp;
        string res = "";
        stringstream ss(s);
        while (ss >> temp)
        {
            temp[0]=toupper(temp[0]);
            for (int i=1;i<temp.length();i++)temp[i]=tolower(temp[i]);
            res += temp + " ";
        }
        return res;
    }
};
class RemoveSpecialCharacters : public Rule
{
public:
    string rule(string s) override
    {
        string res = "";
        for (int i = 1; i < s.length(); i++)
        {
            if (s[i] != ' ' && s[i] != '-' && s[i] != '_' && s[i] != '.')
                res += s[i];
        }
        return res;
    }
};
class AddDatePrefix : public Rule
{
public:
    string rule(string s) override
    {
        cout << "Nhap ngay thang nam: ";
        int day;
        int month;
        int year;
        cin >> day >> month >> year;
        string date = to_string(day) + to_string(month) + to_string(year);
        return date + s;
    }
};

class RenameCVFileUseCase
{
public:
    string rename(const string &originalFilename)
    {
        string res = originalFilename;
        NormalizeCasing nor;
        RemoveSpecialCharacters rem;
        AddDatePrefix add;
        res = nor.rule(res);
        res = rem.rule(res);
        res = add.rule(res);
        return res;
    }
};

int main()
{
    RenameCVFileUseCase cvFileRenamer;

    string originalFileName = "ho so xin viec_nguyen van a - cv_final.docx";
    string formattedFileName = cvFileRenamer.rename(originalFileName);

    cout << "Original File Name: " << originalFileName << endl;
    cout << "Formatted File Name: " << formattedFileName << endl;

    return 0;
}