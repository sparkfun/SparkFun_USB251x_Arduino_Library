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

#ifndef __SPARKFUN_USB251X_ARDUINO_LIBRARY__
#define __SPARKFUN_USB251X_ARDUINO_LIBRARY__

#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_USB251x_Constants.h"
#include "SparkFun_USB251x_IO.h"

class USB251x
{
  public:
    // Default constructor
    USB251x() {}

    bool begin(TwoWire& wirePort = Wire);

    void setDefaults(); //Write most common settings
    void attach(); //Set USB_ATTACH bit and go!

    //Helper functions for the more common 2-byte registers
    void setVendorID(uint16_t vendorID);
    void setProductID(uint16_t productID);
    void setDeviceID(uint16_t deviceID);

    //Read/write single bytes
    byte readByte(byte addr);
    void writeByte(byte addr, byte value);

  private:
    // I2C communication object instance
    USB251X_IO usb251x_io;
};

#endif
