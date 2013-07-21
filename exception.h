#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

class ErgException : public QException
{
public:
    ErgException(QString msg) : msg_(msg) {}
    void raise() const { throw *this; }
    ErgException* clone() const { return new ErgException(*this); }
    const QString whatq() const { return msg_; }

private:
    QString msg_;
};

#endif // EXCEPTION_H
