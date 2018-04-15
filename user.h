#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User(QString name,QString password,int month);
    QString name;
    QString password;
    uint validity;//有效期，秒;
    void setValidityMonth(int month);
};

#endif // USER_H
