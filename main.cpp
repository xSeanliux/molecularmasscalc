//演算法一

#include <iostream>
#include <string.h>
#include "dict.h"
using namespace std;
string ques;
bool isSupported;
struct Chem //一個個葉的資料型態
{
    string str;
    int childN;
    Chem *children[10000];
    int elements;
    int amount;
};

float calculate(Chem *root)
{ //給定根，計算其化學式的分（原）子量
    float sum = 0;

    if(root->elements <= 1 && !containsDigit(root->str) && !containsBrackets(root->str))
    { //若是原子，判斷資料庫內有沒有這個原子的資料（若沒有會有Error)
        if(getMass(root->str) < 0) isSupported = false;
        return getMass(root->str);
    }
    else
    { //否則加總其子葉
        for(int i = 0; i < root->childN; i++)
        {
            float k = calculate(root->children[i]) * root->children[i]->amount;
            if(k < 0) isSupported = false;
            sum += k;
        }
        return sum;
    }
}

void run(Chem *c)
{ //給定根，適當加入子葉
    //資料初始化
    int len = c->str.length();
    string currentStr = "";
    string currentAmount = "";
    int amount = 1;
    int N = 0; //stack
    for(int i = 0; i < len; i++)
    {
        if(isUpper(c->str[i]))
        {  //若找到大寫字母，則紀錄下來，以後用以判斷是否繼續加子葉
            c->elements++;
        }
        //Stack
        if(c->str[i] == '(')
        {
            N++;
        }
        else if(c->str[i] == ')')
        {
            N--;
        }
        //在括弧外
        if(N == 0)
        {
            if(currentStr == "")
            {
                if(isLower(c->str[i+1]))
                {//讀入一個個原子，藉由看下一個字母的大小寫來判斷原子長度
                    currentStr += c->str[i];
                    currentStr += c->str[i+1];
                    i++;
                }
                else
                {
                    currentStr = c->str[i];
                }
            }
            i++;
            while(isDigit(c->str[i]))
            { //若有係數，則讀入
                currentAmount += c->str[i];
                i++;
            }
            i--;
            if(currentAmount != "")
            { //如果有讀入係數，則轉成數字；否則係數設為 1
                amount = stoi(currentAmount);
            }
            if(currentStr[0] == '(')
            {
                //去除多餘左括弧 e.g. (((H)2)3 經過處理會變成 ((H)2)3
                currentStr = currentStr.substr(1);
            }
            //建立子葉
            Chem *child = new Chem;
            child->str = currentStr;
            child->childN = 0;
            child->elements = 0;
            child->amount = amount;
            c->children[c->childN] = child;
            c->childN++;
            currentStr = "";
            currentAmount = "";
            amount = 1;
        }
        else
        {
            currentStr += c->str[i];
        }
    }
    if(c->elements <= 1 && !containsBrackets(c->str))
    { //若只剩一個原子，也不用拆括弧了，那就沒有事做了
        return;
    }
    else
    {
        //否則對每一個子葉建他們的子葉
        for(int i = 0; i < c->childN; i++)
        {
            run(c->children[i]);
        }
    }

}

void f(string ques){
    //主程式再加一層包裝
    isSupported = true;
    //建立樹根
    Chem *root = new Chem();
    root->str = ques;
    root->childN = 0;
    root->  elements = 0;
    root->amount = 1;
    run(root);
    float amount = calculate(root);
    if(isSupported){
        cout << amount << endl;
    } else {
        cout << "I'm sorry! Either there was an imaginary atom in there, or there was an element not supported by this program. This program can only handle atoms with atomic numbers less than 30." << endl << "Please go back and check your input. Thank you.";
    }

}

int main()
{
    while(cin >> ques)
    {
        f(ques);
    }
}
