/**
 * ***************************************************************************************************
 *  @file Dht11.cpp
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * ***************************************************************************************************
 */
#include "Dht11.h"

void DHT11Core::DhtInit(std::shared_ptr<DHT>& dht)
{
    dht->begin();
}

void DHT11Core::DhtReadData(Dht11Output_t *pDht11Output, std::shared_ptr<DHT>& dht)
{
    pDht11Output->humidity = dht->readHumidity();
    pDht11Output->temperatur = dht->readTemperature();
}

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/