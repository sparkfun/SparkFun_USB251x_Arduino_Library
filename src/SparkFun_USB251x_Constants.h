/*
  This is a library written for the Microchip USB251xB USB Hub
  SparkFun sells these at its website:
  https://www.sparkfun.com/products/18014

  Do you like this library? Help support open source hardware. Buy a board!

  Written by Nathan Seidle @ SparkFun Electronics, April 20th, 2021

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __SPARKFUN_USB251x_CONSTANTS__
#define __SPARKFUN_USB251x_CONSTANTS__
#include <Arduino.h>

// Constants definitions
const byte USB251XB_I2C_ADDR = 0x2C;

// Registers definitions
const byte REGISTER_VENDOR_ID_LSB = 0x00;
const byte REGISTER_VENDOR_ID_MSB = 0x01;
const byte REGISTER_PRODUCT_ID_LSB = 0x02;
const byte REGISTER_PRODUCT_ID_MSB = 0x03;
const byte REGISTER_DEVICE_ID_LSB = 0x04;
const byte REGISTER_DEVICE_ID_MSB = 0x05;
const byte REGISTER_CONFIG1 = 0x06;
const byte REGISTER_CONFIG2 = 0x07;
const byte REGISTER_CONFIG3 = 0x08;
const byte REGISTER_NONREMOVABLE_DEVICES = 0x09;
const byte REGISTER_PORT_DISABLE_SELF = 0x0A;
const byte REGISTER_PORT_DISABLE_BUS = 0x0B;
const byte REGISTER_MAX_POWER_SELF = 0x0C;
const byte REGISTER_MAX_POWER_BUS = 0x0D;
const byte REGISTER_HUB_CONTROLLER_MAX_CURRENT_SELF = 0x0E;
const byte REGISTER_HUB_CONTROLLER_MAX_CURRENT_BUS = 0x0F;
const byte REGISTER_POWER_ON_TIME = 0x10;
const byte REGISTER_LANGUAGE_ID_HIGH = 0x11;
const byte REGISTER_LANGUAGE_ID_LOW = 0x12;
const byte REGISTER_MANUFACTURER_STRING_LENGTH = 0x13;
const byte REGISTER_PRODUCT_STRING_LENGTH = 0x14;
const byte REGISTER_SERIAL_STRING_LENGTH = 0x15;
const byte REGISTER_MANUFACTURER_STRING_START = 0x16;
const byte REGISTER_PRODUCT_STRING_START = 0x54;
const byte REGISTER_SERIAL_STRING_START = 0x92;
const byte REGISTER_BATTERY_CHARGING_ENABLE = 0xD0;
const byte REGISTER_STATUS = 0xFF;

const byte DEFAULT_SETTINGS[17] = {
  0x24, //Vendor ID
  0x04,
  0x14, //Product ID
  0x25,
  0xB3, //Device ID
  0x0B,
  0x9B, //Config 1 - 1001 1011 = Self powered, Individual port sensing and power control
  0x20, //Config 2 - 0010 0000 = No dynamic power enable, 
  0x02, //Config 3 - 0000 0010 = rsvd?
  0x00, //Non-removable devices
  0x00, //Port Disable Self
  0x00, //Port Disable Bus
  0x32, //Max power Self = 100mA
  0x32, //Max power Bus = 100mA
  0x32, //Hub controller max current self = 100mA
  0x32, //Hub controller max current bus = 100mA
  0x32, //Power on time
}; //17 bytes


#endif
