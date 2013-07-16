#include "scenario.h"

 std::shared_ptr<Scenario> Registry::scenario_(nullptr);

Scenario::Scenario(const QString& name) :
    name_(name)
{
}

QJsonObject Scenario::to_json() const
{
    QJsonObject jscenario;
    QJsonObject jfloors;

    jscenario.insert(QString("_floors"), QJsonValue(jfloors));
    for(const auto& f : floors_)
    {
        jfloors.insert(f.name(), QJsonValue(f.to_json()));
    }

    return jscenario;
}

 void Scenario::from_json(const QJsonObject& jo)
 {

 }

QJsonObject Floor::to_json() const
{
    QJsonObject jo;

    return jo;
}

 void Floor::from_json(const QJsonObject& jo)
 {

 }
