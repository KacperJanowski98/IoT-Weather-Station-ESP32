/**
 * ***************************************************************************************************
 *  @file DhtSensor.cpp
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * ***************************************************************************************************
 */
#include "DhtSensor.h"

DHTCore::DHTCore(std::shared_ptr<DHT> dht,
                float temperature,
                float humidity)
    : m_dht(dht)
    , m_temperature(temperature)
    , m_humidity(humidity)
{}

DHTCore::DHTCore(const DHTCore& other)
    : m_dht(other.m_dht)
    , m_temperature(other.m_temperature)
    , m_humidity(other.m_humidity)
{}

DHTCore::DHTCore(DHTCore&& other) noexcept
    : m_dht(std::move(other.m_dht))
    , m_temperature(std::move(other.m_temperature))
    , m_humidity(std::move(other.m_humidity))
{}

DHTCore &DHTCore::operator=(const DHTCore& other)
{
    if (this != &other)
    {
        *this = DHTCore(other);
    }
    return *this;
}

DHTCore &DHTCore::operator=(DHTCore&& other) noexcept
{
    if (this != &other)
    {
        std::swap(DHTCore::m_dht, other.m_dht);
        std::swap(DHTCore::m_humidity, other.m_humidity);
        std::swap(DHTCore::m_temperature, other.m_temperature);
    }
    return *this;
}

DHTCore::~DHTCore() = default;

void DHTCore::DhtInit()
{
    DHTCore::m_dht->begin();
}

float DHTCore::getTemperature()
{
    return DHTCore::m_temperature;
}

float DHTCore::getHumidity()
{
    return DHTCore::m_humidity;
}

void DHTCore::DhtReadData()
{
    DHTCore::m_humidity = m_dht->readHumidity();
    DHTCore::m_temperature = m_dht->readTemperature();
}

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/