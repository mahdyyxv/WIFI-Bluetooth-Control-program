#pragma once

#include "common.hpp"

std::string Display_Bluetooth_Status();
bool TurnBluetooth(bool on = true);
bool ConnectBluetoothDevice(std::string deviceAddress, bool pairing = false);
