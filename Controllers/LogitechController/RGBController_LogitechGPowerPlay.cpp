/*-----------------------------------------*\
|  RGBController_LogitechGPowerPlay.cpp     |
|                                           |
|  Generic RGB Interface for                |
|  Logitech G PowerPlay Wireless Mousemat   |
|                                           |
|  TheRogueZeta   8/31/2020                 |
\*-----------------------------------------*/

#include "RGBController_LogitechGPowerPlay.h"

RGBController_LogitechGPowerPlay::RGBController_LogitechGPowerPlay(LogitechGPowerPlayController* logitech_ptr)
{
    logitech = logitech_ptr;

    name        = "Logitech G PowerPlay Wireless Charging System";
    vendor      = "Logitech";
    type        = DEVICE_TYPE_MOUSEMAT;
    description = "Logitech G PowerPlay Wireless Charging System";
    location    = logitech->GetDeviceLocation();
    serial      = logitech->GetSerialString();

    mode Off;
    Off.name                            = "Off";
    Off.value                           = LOGITECH_G_POWERPLAY_MODE_OFF;
    Off.flags                           = 0;
    Off.color_mode                      = MODE_COLORS_PER_LED;
    modes.push_back(Off);

    mode Static;
    Static.name                         = "Static";
    Static.value                        = LOGITECH_G_POWERPLAY_MODE_STATIC;
    Static.flags                        = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode                   = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    mode Cycle;
    Cycle.name                          = "Cycle";
    Cycle.value                         = LOGITECH_G_POWERPLAY_MODE_CYCLE;
    Cycle.flags                         = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;
    Cycle.color_mode                    = MODE_COLORS_PER_LED;
    Cycle.speed_min                     = LOGITECH_G_POWERPLAY_SPEED_SLOWEST;
    Cycle.speed_max                     = LOGITECH_G_POWERPLAY_SPEED_FASTEST;
    Cycle.speed                         = LOGITECH_G_POWERPLAY_SPEED_NORMAL;
    modes.push_back(Cycle);

    mode Breathing;
    Breathing.name                      = "Breathing";
    Breathing.value                     = LOGITECH_G_POWERPLAY_MODE_BREATHING;
    Breathing.flags                     = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;
    Breathing.color_mode                = MODE_COLORS_PER_LED;
    Breathing.speed_min                 = LOGITECH_G_POWERPLAY_SPEED_SLOWEST;
    Breathing.speed_max                 = LOGITECH_G_POWERPLAY_SPEED_FASTEST;
    Breathing.speed                     = LOGITECH_G_POWERPLAY_SPEED_NORMAL;
    modes.push_back(Breathing);

    SetupZones();
}

RGBController_LogitechGPowerPlay::~RGBController_LogitechGPowerPlay()
{
    delete logitech;
}

void RGBController_LogitechGPowerPlay::SetupZones()
{
    zone GPowerPlay_logo_zone;
    GPowerPlay_logo_zone.name           = "Logo";
    GPowerPlay_logo_zone.type           = ZONE_TYPE_SINGLE;
    GPowerPlay_logo_zone.leds_min       = 1;
    GPowerPlay_logo_zone.leds_max       = 1;
    GPowerPlay_logo_zone.leds_count     = 1;
    GPowerPlay_logo_zone.matrix_map     = NULL;
    zones.push_back(GPowerPlay_logo_zone);

    led GPowerPlay_logo_led;
    GPowerPlay_logo_led.name = "Logo";
    leds.push_back(GPowerPlay_logo_led);

    SetupColors();
}

void RGBController_LogitechGPowerPlay::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_LogitechGPowerPlay::DeviceUpdateLEDs()
{
    UpdateZoneLEDs(0);
}

void RGBController_LogitechGPowerPlay::UpdateZoneLEDs(int zone)
{
    unsigned char red = RGBGetRValue(colors[zone]);
    unsigned char grn = RGBGetGValue(colors[zone]);
    unsigned char blu = RGBGetBValue(colors[zone]);

    logitech->SendMouseMatMode(modes[active_mode].value, modes[active_mode].speed, zone, red, grn, blu);
}

void RGBController_LogitechGPowerPlay::UpdateSingleLED(int led)
{
    UpdateZoneLEDs(led);
}

void RGBController_LogitechGPowerPlay::SetCustomMode()
{

}

void RGBController_LogitechGPowerPlay::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}
