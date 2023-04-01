#include "myvalidator.h"

myValidator::myValidator()
{

}

QValidator::State myValidator::validate(QString &input, int &pos)const{
    for(int i=0;i<input.size();i++){
        if((input[i]>'9' || input[i]<'0')
                && input[i] != '^'
                && input[i] !='+'
                && input[i] != '-'
                && input[i] != '*'
                && input[i] != '/'
                && input[i] != '%'
                && input[i] != '('
                && input[i] != ')'){
            return QValidator::State::Invalid;
        }
    }
    return QValidator::State::Acceptable;
}
