#include "scenario.h"

#include "exception.h"

QJsonObject get_object(const QJsonObject& jo, const QString& key)
{
    auto res(jo.find(key));

    if(jo.end() == res || !res.value().isObject())
        throw ErgException("failed to find Json object: " + key);

    return res.value().toObject();
}

auto find(const QJsonObject& jo, const QString& key) -> decltype(jo.find(key))
{
    auto ret(jo.find(key));

    if(jo.end() == ret)
        throw ErgException("failed to find Json object: " + key);

    return ret;
}

template <class Container, class Name>
void error_check_duplicate(const Container& container, const Name& name)
{
    for(const auto& elem : container)
        if(elem->name() == name)
            throw ErgException("invalid duplicate found: " + name);
}

void error_check_object(const QJsonObject::Iterator& iter)
{
    if(!iter.value().isObject())
        throw ErgException("floor object not found: " + iter.key());
}

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
        jfloors.insert(f->name(), QJsonValue(f->to_json()));
    }

    return jscenario;
}

void Scenario::from_json(const QJsonObject& jo)
{
    auto jfloors(get_object(jo, "_floors"));

    for(auto iter(jfloors.begin()); iter != jfloors.end(); ++iter)
    {
        error_check_duplicate(floors_, iter.key());

        auto floor(std::make_shared<Floor>(iter.key()));

        error_check_object(iter);

        floor->from_json(iter.value().toObject());

        floors_.push_back(std::move(floor));
    }
}

Floor::Floor(const QString& name) : name_(name)
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
