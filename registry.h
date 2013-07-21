#pragma once
#ifndef REGISTRY_H
#define REGISTRY_H

#include "exception.h"

template <class T>
class Registry
{
public:
    static std::shared_ptr<T> instance() { if (nullptr == instance_) throw ErgException("Registry instance not set - null"); return instance_; }
    static void set(const std::shared_ptr<T>& instance) { instance_ = instance; }
    static bool valid() { return !!instance_; }
private:
    static std::shared_ptr<T> instance_;
};

template <class T>
std::shared_ptr<T> Registry<T>::instance_(nullptr);

#endif // REGISTRY_H
