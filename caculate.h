#ifndef CACULATE_H
#define CACULATE_H
#include <QString>
#include "big_int.h"
using namespace _big_int;

int priority(char c);

std::string postofix(std::string infix);

big_int caculateAnwser(std::string postfix);

#endif // CACULATE_H



