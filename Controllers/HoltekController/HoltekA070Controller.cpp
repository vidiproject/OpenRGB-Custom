/*-----------------------------------------------*\
|  HoltekA070Controller.cpp                       |
|                                                 |
|  Driver for Holtek USB Gaming Mouse [04d9:a070] |
|                                                 |
|  Santeri Pikarinen (santeri3700) 8/01/2020      |
\*-----------------------------------------------*/

#include "HoltekA070Controller.h"

#include <cstring>

HoltekA070Controller::HoltekA070Controller(hid_device* dev_handle, const char* path)
{
    dev         = dev_handle;
    location    = path;
}

HoltekA070Controller::~HoltekA070Controller()
{
    hid_close(dev);
}

std::string HoltekA070Controller::GetDeviceLocation()
{
    return("HID: " + location);
}

std::string HoltekA070Controller::GetSerialString()
{
    wchar_t serial_string[128];
    hid_get_serial_number_string(dev, serial_string, 128);

    std::wstring return_wstring = serial_string;
    std::string return_string(return_wstring.begin(), return_wstring.end());

    return(return_string);
}

/*-------------------------------------------------------------------------------------------------*\
| Private packet sending functions.                                                                 |
\*-------------------------------------------------------------------------------------------------*/

void HoltekA070Controller::SendCustomColor
    (
    unsigned char       red,
    unsigned char       green,
    unsigned char       blue
    )
{
    char usb_buf[8];

    /*-----------------------------------------------------*\
    | Zero out buffer                                       |
    \*-----------------------------------------------------*/
    memset(usb_buf, 0x00, sizeof(usb_buf));

    /*-----------------------------------------------------*\
    | Set up RGB Control packet                             |
    \*-----------------------------------------------------*/
    usb_buf[0x00]           = 0x07;  // PACKET SIZE?
    usb_buf[0x01]           = 0x0a;  // SET RGB
    usb_buf[0x02]           = 0x00;  // SAVE (does not work with SET RGB)
    usb_buf[0x03]           = red;   // RED
    usb_buf[0x04]           = green; // GREEN
    usb_buf[0x05]           = blue;  // BLUE
    usb_buf[0x06]           = 0x00;  // PADDING?
    usb_buf[0x07]           = 0x00;  // PADDING?

    // So far no saving function has been discovered for the "SET RGB" command.
    // Such functionality might not even exist for the A070 series.
    // The chosen RGB color will therefore reset after a power cycle.

    /*-----------------------------------------------------*\
    | Send packet                                           |
    \*-----------------------------------------------------*/
    hid_send_feature_report(dev, (unsigned char *)usb_buf, sizeof(usb_buf));
}

void HoltekA070Controller::SendMode
    (
    unsigned char       mode
    )
{

    char usb_buf[8];

    /*-----------------------------------------------------*\
    | Zero out buffer                                       |
    \*-----------------------------------------------------*/
    memset(usb_buf, 0x00, sizeof(usb_buf));

    /*-----------------------------------------------------*\
    | Set up lighting mode control packet                   |
    \*-----------------------------------------------------*/
    usb_buf[0x00]           = 0x07; // PACKET SIZE?
    usb_buf[0x01]           = 0x0b; // SET LIGHTING MODE
    usb_buf[0x02]           = 0x01; // SAVE
    usb_buf[0x03]           = mode; // MODE 01-04
    usb_buf[0x04]           = 0x00; // PADDING?
    usb_buf[0x05]           = 0x00; // PADDING?
    usb_buf[0x06]           = 0x00; // PADDING?
    usb_buf[0x07]           = 0x00; // PADDING?

    /*-----------------------------------------------------*\
    | Send packet                                           |
    \*-----------------------------------------------------*/
    hid_send_feature_report(dev, (unsigned char *)usb_buf, sizeof(usb_buf));
}
