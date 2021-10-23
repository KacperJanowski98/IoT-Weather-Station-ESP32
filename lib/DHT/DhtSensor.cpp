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

void DHTCore::DhtInit(std::shared_ptr<DHT>& dht)
{
    dht->begin();
}

void DHTCore::DhtReadData(DhtOutput_t *pDht11Output, std::shared_ptr<DHT>& dht)
{
    pDht11Output->humidity = dht->readHumidity();
    pDht11Output->temperatur = dht->readTemperature();
}

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/