#ifndef MYVALIDATOR_H
#define MYVALIDATOR_H

#include <QObject>
#include <QValidator>

class myValidator :public  QValidator
{
    Q_OBJECT
public:
    myValidator();
    QValidator::State validate(QString &input, int &pos) const;
};

#endif // MYVALIDATOR_H
