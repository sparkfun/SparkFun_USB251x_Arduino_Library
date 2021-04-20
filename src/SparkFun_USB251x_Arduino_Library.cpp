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

#include "SparkFun_USB251x_Arduino_Library.h"

bool USB251x::begin(TwoWire& wirePort)
{
  // Initialize the selected I2C interface
  if (usb251x_io.begin(USB251XB_I2C_ADDR, wirePort) == false)
    return (false);

  return (true);
}

//Controls USB_ATTACH bit
//Once bit is set, device settings are locked and hub begins acting like a hub
void USB251x::attach(void)
{
  usb251x_io.setRegisterBit(REGISTER_STATUS, 0);
}


//Write default settings to hub
//Upon reset, if device straps to SMBUS, it will sit with 0x00 in every register
void USB251x::setDefaults()
{
  usb251x_io.writeMultipleBytes(REGISTER_VENDOR_ID_LSB, DEFAULT_SETTINGS, sizeof(DEFAULT_SETTINGS));
}

byte USB251x::readByte(byte addr)
{
  return (usb251x_io.readSingleByte(addr));
}

void USB251x::writeByte(byte addr, byte value)
{
  usb251x_io.writeSingleByte(addr, value);
}

void USB251x::setVendorID(uint16_t vendorID)
{
  usb251x_io.writeMultipleBytes(REGISTER_VENDOR_ID_LSB, (byte*)&vendorID, 2);
}

void USB251x::setProductID(uint16_t productID)
{
  usb251x_io.writeMultipleBytes(REGISTER_PRODUCT_ID_LSB, (byte*)&productID, 2);
}

void USB251x::setDeviceID(uint16_t deviceID)
{
  usb251x_io.writeMultipleBytes(REGISTER_DEVICE_ID_LSB, (byte*)&deviceID, 2);
}
