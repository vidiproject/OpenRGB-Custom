/*-----------------------------------------*\
|  PatriotViperController.h                 |
|                                           |
|  Definitions and types for Patriot Viper  |
|  RGB RAM lighting controller              |
|                                           |
|  Adam Honse (CalcProgrammer1) 1/1/2020    |
\*-----------------------------------------*/

#include <string>
#include "i2c_smbus.h"

#pragma once

typedef unsigned char	viper_dev_id;
typedef unsigned short	viper_register;

enum
{
    VIPER_REG_STATIC                    = 0x01,     /* Set static mode                      */
    VIPER_REG_MODE                      = 0x03,     /* Mode register                        */
    VIPER_REG_LED0_DIRECT_COLOR         = 0x30,     /* LED 0 Color (R, B, G)                */
    VIPER_REG_LED1_DIRECT_COLOR         = 0x31,     /* LED 1 Color (R, B, G)                */
    VIPER_REG_LED2_DIRECT_COLOR         = 0x32,     /* LED 2 Color (R, B, G)                */
    VIPER_REG_LED3_DIRECT_COLOR         = 0x33,     /* LED 3 Color (R, B, G)                */
    VIPER_REG_LED4_DIRECT_COLOR         = 0x34,     /* LED 4 Color (R, B, G)                */
    VIPER_REG_APPLY                     = 0x35,     /* Apply Changes (0x01, 0x00, 0x00)     */
    VIPER_REG_LED0_EFFECT_COLOR         = 0x3B,     /* LED 0 Color (R, B, G)                */
    VIPER_REG_LED1_EFFECT_COLOR         = 0x3C,     /* LED 1 Color (R, B, G)                */
    VIPER_REG_LED2_EFFECT_COLOR         = 0x3D,     /* LED 2 Color (R, B, G)                */
    VIPER_REG_LED3_EFFECT_COLOR         = 0x3E,     /* LED 3 Color (R, B, G)                */
    VIPER_REG_LED4_EFFECT_COLOR         = 0x3F,     /* LED 4 Color (R, B, G)                */
    VIPER_REG_START                     = 0xFF,     /* Start Frame (0xFF, 0xFF, 0xFF)       */
};

enum
{
    VIPER_MODE_DARK                     = 0x00,     /* Dark mode                            */
    VIPER_MODE_BREATHING                = 0x01,     /* Breathing mode                       */
    VIPER_MODE_VIPER                    = 0x02,     /* Viper mode                           */
    VIPER_MODE_HEARTBEAT                = 0x03,     /* Heartbeat mode                       */
    VIPER_MODE_MARQUEE                  = 0x04,     /* Marquee mode                         */
    VIPER_MODE_RAINDROP                 = 0x05,     /* Raindrop mode                        */
    VIPER_MODE_AURORA                   = 0x06,     /* Aurora mode                          */
    VIPER_MODE_NEON                     = 0x08,     /* Neon mode                            */
};

enum
{
    VIPER_SPEED_MIN                     = 0xC8,     /* Slowest speed for non-breathing mode */
    VIPER_SPEED_DEFAULT                 = 0x64,     /* Default speed for non-breathing mode */
    VIPER_SPEED_MAX                     = 0x14,     /* Fastest speed for non-breathing mode */
    VIPER_SPEED_BREATHING_MIN           = 0xFF,     /* Slowest speed for breathing mode     */
    VIPER_SPEED_BREATHING_DEFAULT       = 0x0C,     /* Default speed for breathing mode     */
    VIPER_SPEED_BREATHING_MAX           = 0x00,     /* Fastest speed for breathing mode     */
};

class PatriotViperController
{
public:
    PatriotViperController(i2c_smbus_interface* bus, viper_dev_id dev, unsigned char slots);
    ~PatriotViperController();

    std::string     GetDeviceName();
    std::string     GetDeviceLocation();
    unsigned int    GetLEDCount();
    unsigned int    GetSlotCount();
    unsigned int    GetMode();
    void            SetMode(unsigned char new_mode, unsigned char new_speed);
    void            SetDirect();

    void            SetAllColors(unsigned char red, unsigned char green, unsigned char blue);
    void            SetEffectColor(unsigned char red, unsigned char green, unsigned char blue);
    void            SetLEDColor(unsigned int led, unsigned char red, unsigned char green, unsigned char blue);
    void            SetLEDColor(unsigned int slot, unsigned int led, unsigned char red, unsigned char green, unsigned char blue);
    void            SetLEDEffectColor(unsigned int led, unsigned char red, unsigned char green, unsigned char blue);
    void            SetLEDEffectColor(unsigned int slot, unsigned int led, unsigned char red, unsigned char green, unsigned char blue);

    void            ViperRegisterWrite(viper_register reg, unsigned char val0, unsigned char val1, unsigned char val2);
    bool            direct;

private:
    char                    device_name[32];
    unsigned int            led_count;
    unsigned char           slots_valid;
    i2c_smbus_interface*    bus;
    viper_dev_id            dev;
    unsigned char           mode;
    unsigned char           speed;
};
