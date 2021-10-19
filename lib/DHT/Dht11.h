/**
 * ***************************************************************************************************
 * @file Dht11.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * ***************************************************************************************************
 */
#ifndef _DHT11_H_
#define _DHT11_H_

#include <DHT.h>
#include <memory>

#define DHTPIN 4
#define DHTTYPE DHT11

typedef struct 
{
    float temperatur;
    float humidity;
} Dht11Output_t;

class DHT11Core
{
public:
    DHT11Core() {}

    ~DHT11Core() {}

    void DhtInit(std::shared_ptr<DHT>& dht);

    void DhtReadData(Dht11Output_t *pDht11Output, std::shared_ptr<DHT>& dht);
};



#endif //_DHT11_H_

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/