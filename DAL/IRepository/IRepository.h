#pragma once

//Паттерн Репозиторий.
//Нужен для удобного представления данных.
//В моём случае -- в виде <ключ/значение>

template<typename KeyType, typename ValueType>
struct IRepository
{
    virtual ValueType getValue(const KeyType& key) = 0;
    virtual void setValue(const KeyType& key, const ValueType& value) = 0;

    virtual ~IRepository() = default;
};


template<typename ValueType>
struct IRepository<void, ValueType>
{
    virtual ValueType getValue() = 0;
    virtual void setValue(const ValueType& value) = 0;

    virtual ~IRepository() = default;
};
