/**
 * ***************************************************************************************************
 * @file DhtSensor.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * ***************************************************************************************************
 */
#ifndef _DHTSENSOR_H_
#define _DHTSENSOR_H_

#include <DHT.h>
#include <memory>

#define DHTPIN 4
#define DHTTYPE DHT11

class DHTCore
{
public:
    DHTCore(std::shared_ptr<DHT> dht,
            float temperature,
            float humidity);

    DHTCore(const DHTCore& other);

    DHTCore(DHTCore&& other) noexcept;

    DHTCore& operator=(const DHTCore& other);

    DHTCore& operator=(DHTCore&& other) noexcept;

    ~DHTCore();

    void DhtInit();

    float getTemperature();

    float getHumidity();

    void DhtReadData();
private:
    std::shared_ptr<DHT> m_dht;
    float m_temperature;
    float m_humidity;
};



#endif //_DHTSENSOR_H_

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/