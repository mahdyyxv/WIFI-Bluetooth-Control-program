#pragma once

#include <iostream>
#include <cstdio>   // For popen() and fgets()
#include <map>
#include <memory>   // For std::shared_ptr
#include <array>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <cstddef>
#include <cstdlib>


constexpr uint8_t WIFI_STATUS              =   1;
constexpr uint8_t WIFI_ON                  =   2;
constexpr uint8_t WIFI_OFF                 =   3;
constexpr uint8_t AVAILABLE_WIFI           =   4;
constexpr uint8_t SAVED_WIFI               =   5;
constexpr uint8_t CONNECT_TO_SAVED_WIFI    =   6;
constexpr uint8_t CONNECT_TO_NEW_WIFI      =   7;
constexpr uint8_t DELETE_SAVED_NETWORK     =   8;
constexpr uint8_t MODIFY_SSID_1            =   9;
constexpr uint8_t MODIFY_SSID_2            =   10;
constexpr uint8_t BLUETOOTH_STATUS         =   11;
constexpr uint8_t BLUETOOTH_ON             =   12;
constexpr uint8_t BLUETOOTH_OFF            =   13;
constexpr uint8_t BLUETOOTH_PAIR           =   14;
constexpr uint8_t BLUETOOTH_CONNECT        =   15;

std::string execCommand(const char* cmd);
extern std::map<uint8_t, std::string> CommandList;
