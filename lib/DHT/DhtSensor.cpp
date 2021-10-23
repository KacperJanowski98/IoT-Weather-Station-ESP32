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
                float humidity,
                float computeHeat)
    : m_dht(dht)
    , m_temperature(temperature)
    , m_humidity(humidity)
    , m_computeHeat(computeHeat)
{}

DHTCore::DHTCore(const DHTCore& other)
    : m_dht(other.m_dht)
    , m_temperature(other.m_temperature)
    , m_humidity(other.m_humidity)
    , m_computeHeat(other.m_computeHeat)
{}

DHTCore::DHTCore(DHTCore&& other) noexcept
    : m_dht(std::move(other.m_dht))
    , m_temperature(std::move(other.m_temperature))
    , m_humidity(std::move(other.m_humidity))
    , m_computeHeat(std::move(other.m_computeHeat))
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
        std::swap(DHTCore::m_computeHeat, other.m_computeHeat);
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

float DHTCore::getComputeHeat()
{
    return DHTCore::m_computeHeat;
}

void DHTCore::DhtReadData()
{
    DHTCore::m_humidity = DHTCore::m_dht->readHumidity();
    DHTCore::m_temperature = DHTCore::m_dht->readTemperature();
}

void DHTCore::calculatedTemperature()
{
    DHTCore::m_computeHeat = DHTCore::m_dht->computeHeatIndex(DHTCore::m_temperature, DHTCore::m_humidity, false);
}

void DHTCore::displayParameter()
{
    Serial.print(F("Humidity: "));
    Serial.print(DHTCore::m_humidity);
    Serial.print(F("%  Temperature: "));
    Serial.print(DHTCore::m_temperature);
    Serial.print(F("°C "));
    Serial.print(DHTCore::m_computeHeat);
    Serial.print(F("°C "));
    Serial.print("\n");
}

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/