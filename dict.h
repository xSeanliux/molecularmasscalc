#include <iostream>
#include <string.h>
using namespace std;

bool containsBrackets(string str)
{
    int l = str.length();
    for(int i = 0; i < l; i++)
    {
        if(str[i] == ')' || str[i] == '(' )
        {
            return true;
        }

    }
    return false;
}

bool containsOps(string str)
{
    int l = str.length();
    for(int i = 0; i < l; i++)
    {
        if(str[i] == ')' || str[i] == '(' || str[i] == '*' || str[i] == '+')
        {
            return true;
        }

    }
    return false;
}

bool isUpper(char c)
{
    return (c <= 'Z' && c >= 'A');
}
bool isLower(char c)
{
    return (c <= 'z' && c >= 'a');
}

bool isDigit(char c)
{
    return (c <= '9' && c >= '0');
}

bool containsDigit(string str)
{
    int l = str.length();
    for(int i = 0; i < l; i++)
    {
        if(isDigit(str[i]))
        {
            return true;
        }

    }
    return false;
}

float getMass(string str)
{
    if(str == "H")
    {
        return 1.008;
    }
    else if(str == "He")
    {
        return 4.003;
    }
    else if(str == "Li")
    {
        return 6.94;
    }
    else if(str == "Be")
    {
        return 9.012;
    }
    else if(str == "B")
    {
        return 10.81;
    }
    else if(str == "C")
    {
        return 12.011;
    }
    else if(str == "N")
    {
        return 14.007;
    }
    else if(str == "O")
    {
        return 15.999;
    }
    else if(str == "F")
    {
        return 18.998;
    }
    else if(str == "Ne")
    {
        return 20.18;
    }
    else if(str == "Na")
    {
        return 22.990;
    }
    else if(str == "Mg")
    {
        return 24.305;
    }
    else if(str == "Al")
    {
        return 26.982;
    }
    else if(str == "Si")
    {
        return 28.085;
    }
    else if(str == "Ca")
    {
        return 40.078;
    }
    else if(str == "P")
    {
        return 30.974;
    }
    else if(str == "S")
    {
        return 32.06;
    }
    else if(str == "Cl")
    {
        return 35.45;
    }
    else if(str == "Ar")
    {
        return 39.948;
    }
    else if(str == "K")
    {
        return 39.098;
    }
    else if(str == "Sc")
    {
        return 44.956;
    }
    else if(str == "Ti")
    {
        return 47.867;
    }
    else if(str == "V")
    {
        return 50.9415;
    }
    else if(str == "Cr")
    {
        return 51.9961;
    }
    else if(str == "Mn")
    {
        return 54.938;
    }
    else if(str == "Ni")
    {
        return 58.6934;
    }
    else if(str == "Co")
    {
        return 58.9332;
    }
    else if(str == "Cu")
    {
        return 63.546;
    }
    else if(str == "Zn")
    {
        return 65.39;
    }
    else if(str == "Bk")
    {
        return 6500.39;
    }
    else
    {
        return -1;
    }



}


string query;

int showWorking(string query)
{

    string currentStr = "";
    int len = query.length();
    for(int i = 0; i < len; i++)
    {
        if(isDigit(query[i]))
        {
            currentStr += "*";
            currentStr += query[i];
            i++;
            while(isDigit(query[i]))
            {
                i++;
                currentStr += query[i];
            }
            i--;
            if(!(isDigit(query[i+1]) || query[i+1] == ')' || i == len-1))
            {
                currentStr += '+';
            }
        }
        else if(isUpper(query[i]))
        {
            string currentElement = "";
            currentElement += query[i];
            if(isLower(query[i+1]))
            {
                i++;
                currentElement += query[i];
            }
            double currentAmount = getMass(currentElement);
            currentStr += to_string(currentAmount);
            if(!(isDigit(query[i+1]) || query[i+1] == ')' || i == len-1))
            {
                currentStr += '+';
            }
        }
        else
        {
            currentStr += query[i];
        }

    }
    cout << currentStr << endl;


}


