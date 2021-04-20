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

#include "SparkFun_USB251x_IO.h"
#include "SparkFun_USB251x_Constants.h"

bool USB251X_IO::begin(byte address, TwoWire& wirePort)
{
  _i2cPort = &wirePort;
  _address = address;
  return isConnected();
}

bool USB251X_IO::isConnected()
{
  _i2cPort->beginTransmission(_address);
  if (_i2cPort->endTransmission() == 0)
  {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(0x00);
    _i2cPort->endTransmission(false); //Don't release bus
    _i2cPort->requestFrom(_address, 2U); //We have to read 2 bytes, the first is throw away number of bytes available, always 32
    byte incomingBytes = _i2cPort->read();
    if (incomingBytes == 0x20) //We should always have 32 bytes avaialable
      return (true);
  }
  return (false);
}

void USB251X_IO::writeMultipleBytes(byte registerAddress, const byte* buffer, byte const packetLength)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->write(packetLength); //Byte count - specific to USB251x SMB interface
  for (byte i = 0; i < packetLength; i++)
    _i2cPort->write(buffer[i]);

  _i2cPort->endTransmission();
}

void USB251X_IO::readMultipleBytes(byte registerAddress, byte* buffer, byte const packetLength)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->endTransmission(false); //Don't release bus

  _i2cPort->requestFrom(_address, packetLength);
  for (byte i = 0; (i < packetLength) && _i2cPort->available(); i++)
    buffer[i] = _i2cPort->read();
}

byte USB251X_IO::readSingleByte(byte registerAddress)
{
  byte result;
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->endTransmission(false); //Don't release bus
  _i2cPort->requestFrom(_address, 2U); //We have to read 2 bytes, the first is throw away number of bytes available, always 32
  byte incomingBytes = _i2cPort->read();
  if (incomingBytes > 0)
    return (_i2cPort->read());
  return (0xFF); //Error
}

void USB251X_IO::writeSingleByte(byte registerAddress, byte const value)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->write(1U); //Byte count
  _i2cPort->write(value);
  _i2cPort->endTransmission();
}

void USB251X_IO::setRegisterBit(byte registerAddress, byte const bitPosition)
{
  byte value = readSingleByte(registerAddress);
  value |= (1 << bitPosition);
  writeSingleByte(registerAddress, value);
}

void USB251X_IO::clearRegisterBit(byte registerAddress, byte const bitPosition)
{
  byte value = readSingleByte(registerAddress);
  value &= ~(1 << bitPosition);
  writeSingleByte(registerAddress, value);
}

bool USB251X_IO::isBitSet(byte registerAddress, byte const bitPosition)
{
  byte value = readSingleByte(registerAddress);
  byte mask = 1 << bitPosition;
  if (value & mask)
    return true;
  else
    return false;
}
