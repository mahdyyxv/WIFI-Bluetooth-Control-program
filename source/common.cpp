#include "../include/common.hpp"


std::map<uint8_t, std::string> CommandList = {
    {WIFI_STATUS, "nmcli radio wifi"},
    {WIFI_ON, "nmcli radio wifi on"},
    {WIFI_OFF, "nmcli radio wifi off"},
    {AVAILABLE_WIFI, "nmcli device wifi list"},
    {SAVED_WIFI, "nmcli connection show"},
    {CONNECT_TO_SAVED_WIFI,"nmcli connection up"},
    {CONNECT_TO_NEW_WIFI, "nmcli device wifi connect"},
    {DELETE_SAVED_NETWORK, "nmcli connection delete"},
    {MODIFY_SSID_1, "sudo nmcli connection modify"},
    {MODIFY_SSID_2, "802-11-wireless.ssid"},
    {BLUETOOTH_STATUS, "bluetoothctl show"},
    {BLUETOOTH_ON, "bluetoothctl power on"},
    {BLUETOOTH_OFF, "bluetoothctl power off"},
    {BLUETOOTH_PAIR, "bluetoothctl pair"},
    {BLUETOOTH_CONNECT, "bluetoothctl connect"}

};

std::string execCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    
    // Open pipe to the command
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read output into result
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    auto it = result.find("Error");
    if(it != std::string::npos)
    {
        return "Error";    
    } 
    return result;
}