#include "user.h"

User::User(QString name,QString password,int month)
{
    this->name=name;
    this->password=password;
    setValidityMonth(month);
}
void User::setValidityMonth(int month){
    this->validity=month*30*24*60*60;
}
