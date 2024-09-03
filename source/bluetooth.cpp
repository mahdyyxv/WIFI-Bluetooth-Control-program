#include "../include/bluetooth.hpp"
#include <string>

std::string Display_Bluetooth_Status()
{
    std::string returned = execCommand(CommandList[BLUETOOTH_STATUS].c_str());
    if(returned.find("Powered: yes") != std::string::npos)
    {
        return "Enabled";
    } 
    else if (returned.find("Powered: no") != std::string::npos)
    {
        return "Disabled"; 
    }
    return "Status can't be knowed";
}

bool TurnBluetooth(bool on)
{
    if(on)
    {
        execCommand(CommandList[BLUETOOTH_ON].c_str());
        if(Display_Bluetooth_Status() == "Enabled") return true;
        else return false;

    }
    execCommand(CommandList[BLUETOOTH_OFF].c_str());
    if(Display_Bluetooth_Status() == "Disabled") return true;
    else return false;
}

bool ConnectBluetoothDevice(std::string deviceAddress, bool pairing)
{    
    std::string returned = "";
    if (pairing)
    {
        returned = execCommand((CommandList[BLUETOOTH_PAIR] + " " +deviceAddress).c_str());
        if (returned.find("Pairing successful") != std::string::npos)
        return true;
    }
    returned = execCommand((CommandList[BLUETOOTH_CONNECT] + " " + deviceAddress).c_str());
    if (returned.find("Connection successful") != std::string::npos)
    {
        return true;
    }
    return false;
}