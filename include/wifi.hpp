#pragma once
#include "common.hpp"

extern std::map<std::string, std::string> NetworkCrendentials;

std::string Display_wifi_status();

void TurnWifi(bool on_off = true);

bool Connect_To_Wifi(const std::string &ssid);
void Connect_To_Wifi(const std::string &ssid, const std::string &password);

void Save_WiFi_Networks();
void Save_WiFi_Networks(const std::string &FileName);

bool Remove_Saved_Network(const std::string &ssid);

bool Modifiy_Saved_Network(const std::string &OldSsid, const std::string &NewSsid);
bool Modifiy_Saved_Network(const std::string &ssid, const std::string &OldPassword ,const std::string &NewPassword);
bool Modifiy_Saved_Network( const std::string &OldSsid, const std::string &OldPassword,
                            const std::string &NewSsid, const std::string &NewPassword);

bool Search_For_Network(const std::string &ssid);
void show_saved_network();
void show_available_network();

