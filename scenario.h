#pragma once
#ifndef SCENARIO_H
#define SCENARIO_H

#include <QJsonObject>
#include <QString>
#include <QVector>

#include <memory>

class Scenario;
class Floor;

QJsonObject get_object(const QJsonObject& jo, const QString& key);

class Json
{
public:
    virtual QJsonObject to_json() const = 0;
    virtual void from_json(const QJsonObject& jo) = 0;
};

class Scenario : public Json
{
public:
    Scenario(const QString& name);

    QJsonObject to_json() const;
    void from_json(const QJsonObject& jo);

    QString name() const { return name_; }
    QVector<std::shared_ptr<Floor>>& floors() { return floors_; }

private:
    QString name_;
    QVector<std::shared_ptr<Floor>> floors_;
};

class Floor : public Json
{
public:
    Floor(const QString& name);

    QJsonObject to_json() const;
    void from_json(const QJsonObject& jo);

    QString name() const { return name_; }

private:
    QString name_;
};

#endif // SCENARIO_H
