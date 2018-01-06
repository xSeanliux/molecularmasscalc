#include <iostream>
#include <string.h>
#include "dict.h"
using namespace std;

struct Num //資料結構，用以儲存葉子
{
    string str;
    int amount;
    int nChild = 0;
    Num *children[100000];
};

float runTree(Num *n) //給定一個數學式，計算數學式的值
{
    if(!containsOps(n->str)) //若僅剩數字在內，那就回傳數字就好了
    {
        //cout << n->str << endl;
        return stof(n->str);
    }
    else //否則，加總其子葉
    {
        float sum = 0;
        for(int i = 0; i< n->nChild; i++)
        {
            float k = runTree(n->children[i]) * n->children[i]->amount;
            sum += k;
        }
        return sum;
    }
}

void parseTree(Num *n)//給定一個葉，分析數學式並適當加子葉
{
    n->nChild = 0;
    int specialTokens = 0;
    int len = n->str.length();
    string currentStr = "";
    string currentAmount = "";
    int amount = 1;
    int N = 0; //stack
    for(int i = 0; i < len; i++)
    {
        //Stack
        if(n->str[i] == '(')
        {
            N++;
            specialTokens++;
        }
        else if(n->str[i] == ')')
        {
            N--;
            specialTokens++;
        }
        if(N == 0)//若不在括弧內
        {
            if(currentStr == "") //若目前沒有資料
            {
                //先看看有沒有數字（有可能剛從括弧出來）
                while(isDigit(n->str[i]) || n->str[i] == '.')
                {
                    currentStr += (char)n->str[i];
                    i++;
                }
                if(n->str[i] == '*')//有乘法
                {
                    i+=1;//跳過，再開始讀數字
                    specialTokens++;
                    while(isDigit(n->str[i]) || n->str[i] == '.')
                    {
                        currentAmount += (char)n->str[i];
                        i++;
                    }

                }
            }
            else //若還是有乘法，再做一次
            {
                if(n->str[i+1] == '*')
                {
                    i+=2;
                    specialTokens++;
                    while(isDigit(n->str[i]) || n->str[i] == '.')
                    {
                        currentAmount += (char)n->str[i];
                        i++;
                    }

                }
            }




            if(currentAmount != "")//如果不是乘以一，那就替換成係數
            {
                amount = stoi(currentAmount);
            }

            if(currentStr[0] == '(')
            { //防止多餘的左括弧 e.g. (((1)*2)*3
                currentStr = currentStr.substr(1);
            }
            if(currentStr != "")
            { //建立子葉
                Num *child = new Num;
                child->str = currentStr;

                child->nChild = 0;
                child->amount = amount;
                n->children[n->nChild] = child;
                n->nChild++;
                currentStr = "";
                currentAmount = "";
                amount = 1;

            }

        }
        else
        {
            currentStr += (char)n->str[i];
        }
    }
    if(specialTokens != 0)
    { //若還是有計算子，括弧未處理, 那就還是要繼續建子葉
        for(int i = 0 ; i < n->nChild; i++)
        {
            parseTree(n->children[i]);
        }
    }
    else
    {
        return;
    }

}

string parseChem(string query){ //將化學式轉成數學式 e.g. parseChem(CO2) = 12 + 16 * 3
    string currentStr = "";
    int len = query.length();
    for(int i = 0; i < len; i++)
    {
        if(isDigit(query[i]))
        { //若有數字就要加 "*" 運算子
            currentStr += "*";
            currentStr += query[i];
            i++;
            while(isDigit(query[i]))
            {
                currentStr += query[i];
                i++;
            }
            i--;
            if(!(isDigit(query[i+1]) || query[i+1] == ')' || i == len-1))
            {
                //在接下來不是數字（數字未完），
                //不是右括弧e.g. 不能有 (16+)，也不是結束的情況下，
                //加上一個 "+" 運算子
                currentStr += '+';
            }
        }
        else if(isUpper(query[i]))
        {  //是原子
            string currentElement = "";
            currentElement += query[i];
            if(isLower(query[i+1])) //看下一個字母判定長度為何e.g. CO, Co 不同
            {
                i++;
                currentElement += query[i];
            }
            double currentAmount = getMass(currentElement); //先查表得原子量
            currentStr += to_string(currentAmount);
            if(!(isDigit(query[i+1]) || query[i+1] == ')' || i == len-1))
            { //在之前提果的前提之下，適當加入 "+" 運算子
                currentStr += '+';
            }
        }
        else
        {

            currentStr += query[i]; //否則原封不動的放回去
            if(query[i] == ')' && isUpper(query[i+1]))
            {
                //在右括弧與數字之間要有 "+" 運算子
                currentStr += '+';
            }

        }

    }
    //建立樹根
    cout << currentStr << endl;
    return currentStr;

}

int main()
{
    while(cin >> query)
    { //使用者輸入和主要程式
        Num *root = new Num;
        root->str = parseChem(query);

        root->nChild = 0;
        parseTree(root);
        cout << "=" << runTree(root) << endl;
    }

}


