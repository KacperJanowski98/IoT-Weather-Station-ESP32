/**
 * ***************************************************************************************************
 * @file LPS25H.h
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-10-26
 * ***************************************************************************************************
 */
#ifndef LPS25H_H_
#define LPS25H_H_

#define LPS25H_ADDRESS     0x5C

#define WHO_AM_I           0x0F
#define WHO_AM_I_RETURN    0xBD // Contains the device ID, BDh

#define RES_CONF_REG       0x10 // Pressure and Temperature internal average configuration.
#define RES_CONF_DEFAULT   0x05

#define CTRL_REG1           0x20
#define POWER_UP            0x80
#define BDU_SET             0x04
#define ODR0_SET            0x10  // 1 read each second

#define CTRL_REG2           0x21
#define CTRL_REG3           0x22
#define REG_DEFAULT         0x00

#define STATUS_REG          0x27
#define TEMPERATURE_READY    0x1
#define PRESSURE_READY       0x2

#define PRESSURE_XL_REG     0x28
#define PRESSURE_L_REG      0x29
#define PRESSURE_H_REG      0x2A
#define TEMP_L_REG          0x2B
#define TEMP_H_REG          0x2C

class LPS25H
{
    private:
    uint8_t m_address;
    byte readRegister(byte slaveAddress, byte regToRead);
    bool writeRegister(byte slaveAddress, byte regToWrite, byte dataToWrite);

public:
    LPS25H(void);
    bool begin(void);
    bool activate(void);
    bool deactivate(void);

    int readPressure(void);
    int readTemperature(void);

protected:
    int m_pressure;
    int16_t m_temperature;
};

#endif /* LPS25H_H_ */

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/