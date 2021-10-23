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

typedef struct 
{
    float temperatur;
    float humidity;
} DhtOutput_t;

class DHTCore
{
public:
    DHTCore() {}

    ~DHTCore() {}

    void DhtInit(std::shared_ptr<DHT>& dht);

    void DhtReadData(DhtOutput_t *pDht11Output, std::shared_ptr<DHT>& dht);
};



#endif //_DHTSENSOR_H_

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/