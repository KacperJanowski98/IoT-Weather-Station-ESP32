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

/**
 * @brief Construct a new DHTCore::DHTCore object
 * 
 * @param dht Sensor
 * @param temperature Temperature 
 * @param humidity Humidity
 * @param computeHeat Compute heat
 */
DHTCore::DHTCore(std::shared_ptr<DHT> dht,
                float temperature,
                float humidity,
                float computeHeat)
    : m_dht(dht)
    , m_temperature(temperature)
    , m_humidity(humidity)
    , m_computeHeat(computeHeat)
{}

/**
 * @brief Copy construct a new DHTCore::DHTCore object
 * 
 * @param other DHTCore object
 */
DHTCore::DHTCore(const DHTCore& other)
    : m_dht(other.m_dht)
    , m_temperature(other.m_temperature)
    , m_humidity(other.m_humidity)
    , m_computeHeat(other.m_computeHeat)
{}

/**
 * @brief Move construct a new DHTCore::DHTCore object
 * 
 * @param other DHTCore object
 */
DHTCore::DHTCore(DHTCore&& other) noexcept
    : m_dht(std::move(other.m_dht))
    , m_temperature(std::move(other.m_temperature))
    , m_humidity(std::move(other.m_humidity))
    , m_computeHeat(std::move(other.m_computeHeat))
{}

/**
 * @brief Copy operator
 * 
 * @param other DHTCore object
 * @return DHTCore& 
 */
DHTCore &DHTCore::operator=(const DHTCore& other)
{
    if (this != &other)
    {
        *this = DHTCore(other);
    }
    return *this;
}

/**
 * @brief Move operator
 * 
 * @param other DHTCore object
 * @return DHTCore& 
 */
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

/**
 * @brief Destroy the DHTCore::DHTCore object
 * 
 */
DHTCore::~DHTCore() = default;

void DHTCore::DhtInit()
{
    DHTCore::m_dht->begin();
}

/**
 * @brief Temperature reading function
 * 
 * @return float Value of temperature
 */
float DHTCore::getTemperature()
{
    return DHTCore::m_temperature;
}

/**
 * @brief Humidity reading function
 * 
 * @return float Value of humidity
 */
float DHTCore::getHumidity()
{
    return DHTCore::m_humidity;
}

/**
 * @brief Compute heat reading function
 * 
 * @return float Value of compute heat
 */
float DHTCore::getComputeHeat()
{
    return DHTCore::m_computeHeat;
}

/**
 * @brief The function that reads the measurement data from the sensor
 * 
 */
void DHTCore::DhtReadData()
{
    DHTCore::m_humidity = DHTCore::m_dht->readHumidity();
    DHTCore::m_temperature = DHTCore::m_dht->readTemperature();
}

/**
 * @brief Calculating compute heat function
 * 
 */
void DHTCore::calculatedTemperature()
{
    DHTCore::m_computeHeat = DHTCore::m_dht->computeHeatIndex(DHTCore::m_temperature, DHTCore::m_humidity, false);
}

/**
 * @brief The function that displays the readout of the sensor values in the log
 * 
 */
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