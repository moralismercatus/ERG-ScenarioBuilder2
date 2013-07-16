#pragma once
#ifndef SCENARIO_H
#define SCENARIO_H

#include <QJsonObject>
#include <QString>
#include <QVector>

#include <memory>

class Scenario;
class Floor;

class Registry
{
public:
    static std::shared_ptr<Scenario> instance() { return scenario_; }
    static void set(const std::shared_ptr<Scenario>& scenario) { scenario_ = scenario; }
private:
    static std::shared_ptr<Scenario> scenario_;
};

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

private:
    QString name_;
    QVector<Floor> floors_;
};

class Floor : public Json
{
public:
    Floor(const std::string& name);

    QJsonObject to_json() const;
    void from_json(const QJsonObject& jo);

    QString name() const { return name_; }

private:
    QString name_;
};

#endif // SCENARIO_H
