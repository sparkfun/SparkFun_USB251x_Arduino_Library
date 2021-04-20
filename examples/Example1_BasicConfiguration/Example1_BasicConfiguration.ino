/*
  Using the USB251xB USB Hub
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 20th, 2021
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/18014

  This example demonstrates how to set the Vendor and Product IDs of the USB Hub then activate it.

  The Qwiic USB Hub is designed to operate as a hub out of the box, with good default settings. If you want to
  tweak various settings on the hub, you first need to close the I2C pullup jumper. This will cause the SCL
  pin to be pulled high putting the USB251xB into SMBUS (I2C) mode. Once it is in I2C config mode, it will not
  enumerate as a hub until you write all necessary and set the USB_ATTACH bit. Once attached, the device
  will lock itself out of I2C and attempt to enumerate. All future communication over I2C will be ignored
  until the UB251xB is reset or power cycled.

  Hardware Connections:
  In general, the hub will act as a hub without any external interferace. If you want to config the hub close
  the I2C jumper with solder, connect a Qwiic cable to a SparkFun RedBoard or other microcontroller with
  Qwiic and then load this firmware.
*/

#include <Wire.h>
#include "SparkFun_USB251x_Arduino_Library.h"

USB251x myHub;

void setup()
{
  Serial.begin(115200);
  Serial.println("USB251x USB Hub Example");

  Wire.begin();

  if (myHub.begin() == false)
  {
    Serial.println("Device not found. USB251xB may already be in hub mode. Please check wiring or reset the hub. Freezing...");
    while (1);
  }

  Serial.println("Writing default settings to hub");
  myHub.setDefaults(); //Write ROM defaults

//  myHub.setVendorID(0x0424);
//  myHub.setProductID(0x2514);
//  myHub.setDeviceID(0x0BB3);

//  byte IDlsb = myHub.readByte(REGISTER_DEVICE_ID_LSB);
//  Serial.print("IDlsb: 0x");
//  Serial.println(IDlsb, HEX);
//
//  byte IDmsb = myHub.readByte(REGISTER_DEVICE_ID_MSB);
//  Serial.print("IDmsb: 0x");
//  Serial.println(IDmsb, HEX);
//
//  myHub.writeByte(REGISTER_CONFIG1, 0x9C); //Address, value
//
//  byte config1 = myHub.readByte(REGISTER_CONFIG1);
//  Serial.print("config1: 0x");
//  Serial.println(config1, HEX);

  //Once the hub starts up (attach) it no longer responds over I2C
  //The hub must have its reset line pulled low or be power cycled to re-enter configuration mode
  Serial.println("Attaching hub. Hub should now appear on computer. It is now locked and no longer configurable until it is reset or power cycled.");
  myHub.attach(); //Locks settings and begin acting as hub
}

void loop()
{

}
