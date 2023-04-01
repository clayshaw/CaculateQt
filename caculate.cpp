#include <iostream>
#include <string>
#include <stack>
#include "big_int.h"
#include "caculate.h"
#include "other.h"
#include <QDebug>

using namespace std;
using namespace _big_int;

int priority(char c)
{
    if (c == '+' || c == '-'){
        return 1;
    } else if (c == '*' || c == '/' || c == '%'){
        return 2;
    } else if(c == '^'){
        return 3;
    } else {
        return 0;
    }
}

std::string postofix(std::string infix)
{

    /*
        1. 讀取中序表達式的每一個字符
        2. 如果是數字，直接輸出
        3. 如果是左括號，入棧
        4. 如果是右括號，將棧頂元素彈出並輸出，直到遇到左括號
        5. 如果是運算符，將棧頂元素彈出並輸出，直到遇到優先級低於或等於該運算符的元素
        6. 將該運算符入棧
        7. 重複2-6，直到中綴表達式讀取完畢
        8. 將棧中剩餘的元素彈出並輸出
    */
    infix = dezero(infix);
    std::string postfix;
    std::stack<char> s;
    for (int i = 0; i < (int)infix.size(); i++)
    {
        if (infix[i] >= '0' && infix[i] <= '9'){
            postfix += infix[i];
        } else if (infix[i] == '('){
            s.push(infix[i]);
        } else if (infix[i] == ')'){
            while (s.top() != '('){
                postfix += ' ';
                postfix += s.top();
                s.pop();
            }
            s.pop();
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '^'){
            postfix+= ' ';
            while (!s.empty() && priority(s.top()) >= priority(infix[i])){
                postfix += ' ';
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
        }
    }
    while (!s.empty())
    {
        postfix += ' ';
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

big_int caculateAnwser(std::string postfix){
    /*
        1. 讀取後序表達式的每一個字符
        2. 如果是數字，入棧
        3. 如果是運算符，將棧頂的兩個元素彈出，進行運算，並將結果入棧
        4. 重複2-3，直到後序表達式讀取完畢
        5. 將棧頂元素彈出，即為表達式的結果
    */
    postfix = postofix(postfix);
    std::stack<big_int> s;
    for (int i = 0; i < (int)postfix.size(); i++)
    {
        if (postfix[i] >= '0' && postfix[i] <= '9'){
            big_int num = 0;
            while (postfix[i] >= '0' && postfix[i] <= '9'){
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            s.push(num);
        } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '%' || postfix[i] == '^'){
            big_int num1 = s.top();s.pop();
            big_int num2 = s.top();s.pop();
            switch (postfix[i])
            {
            case '+':
                s.push(num2 + num1);
                break;
            case '-':
                s.push(num2 - num1);
                break;
            case '*':
                s.push(num2 * num1);
                break;
            case '/':
                s.push(num2 / num1);
                break;
            case '%':
                s.push(num2 % num1);
                break;
            case '^':
                s.push(num2 ^ num1);
                break;
            default:
                break;
            }
        }
    }
    return s.top();
}
