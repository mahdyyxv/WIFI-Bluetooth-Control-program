#include "../include/wifi.hpp"

static std::map<std::string, std::string> parseNetplanFiles();
static void saveDataToFile(const std::string& filename);
static void saveDataToFile(const std::string& filename, const std::string& FileContent);
static bool CheckIFNetworkExist(const std::string& SSID);
static std::vector<std::string> GenerateFilesFromDir();
static std::map<std::string, std::string> FindSsidInformation(const std::string &SSID);
static void ChangeFileInfo(std::string& fileData, const std::string& OldWord, const std::string& NewWord);



std::map<std::string, std::string> NetworkCrendentials;

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Display_wifi_status()
{
    return "Wi-Fi Status: " + execCommand(CommandList[WIFI_STATUS].c_str());
}

/**
 * @brief turning wifi on/off  
 * on -> true
 * off -> false
 *
 * @param on_off 
 */
void TurnWifi(bool on_off)
{
    if(on_off == true)
    {
        execCommand(CommandList[WIFI_ON].c_str());
    }
    else
    {
        execCommand(CommandList[WIFI_OFF].c_str());
    }
}

/**
 * @brief connect to saved Network by ssid
 * 
 * @param ssid 
 */
bool Connect_To_Wifi(const std::string &ssid)
{
    if(CheckIFNetworkExist(ssid))
    {
        execCommand((CommandList[CONNECT_TO_SAVED_WIFI] + " '" + ssid + "'").c_str());
        return true;
    }
    return false;
}

/**
 * @brief connect to new network by ssid and password
 * 
 * @param ssid 
 * @param password 
 */
void Connect_To_Wifi(const std::string &ssid, const std::string &password)
{
    execCommand((CommandList[CONNECT_TO_NEW_WIFI] + " " + "'" +ssid + "'" + " password '" + password + "'" ).c_str());
}

/**
 * @brief Save network crendentials localy during program runtime
 * 
 */
void Save_WiFi_Networks()
{
    NetworkCrendentials = parseNetplanFiles();
}

/**
 * @brief Save network crendentials to file on pc
 * 
 * @param FileName output file name where we store crendentials
 */
void Save_WiFi_Networks(const std::string &FileName)
{
    Save_WiFi_Networks();
    saveDataToFile(FileName);
}

bool Remove_Saved_Network(const std::string &ssid)
{
    if(CheckIFNetworkExist(ssid))
    {
        std::string test = execCommand((CommandList[DELETE_SAVED_NETWORK] + " '" + ssid + "'" ).c_str());
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param OldSsid 
 * @param NewSsid 
 * @return true 
 * @return false 
 */
bool Modifiy_Saved_Network(const std::string &OldSsid, const std::string &NewSsid)
{
    if(CheckIFNetworkExist(OldSsid) && OldSsid.find(NewSsid) == std::string::npos)
    {
        std::string ContentOfFile = "";
        std::string FileName = "";
        std::map<std::string, std::string> Data =  FindSsidInformation(OldSsid);
        ContentOfFile = Data.begin()->second;
        FileName = "/etc/netplan/" + Data.begin()->first;
        system("sudo systemctl stop NetworkManager");
        std::cout<< "Stop Network\n";
        ChangeFileInfo(ContentOfFile, OldSsid, NewSsid);
        std::cout<< "Change File Info Network\n";
        saveDataToFile(FileName, ContentOfFile);
        std::cout<< "Save Data To Network File\n";
        system("sudo netplan apply");
        std::cout<< "Apply Network\n";
        system("sudo systemctl restart NetworkManager");
        return true;
    }
    return false;
}
/**
 * @brief 
 * 
 * @param ssid 
 * @param OldPassword 
 * @param NewPassword 
 * @return true 
 * @return false 
 */
bool Modifiy_Saved_Network(const std::string &ssid, const std::string &OldPassword ,const std::string &NewPassword)
{
    if(CheckIFNetworkExist(ssid) && NewPassword.length() >= 8 && NewPassword != OldPassword)
    {
        std::string ContentOfFile = "";
        std::string FileName = "";
        std::map<std::string, std::string> Data =  FindSsidInformation(ssid);
        ContentOfFile = Data.begin()->second;
        FileName = "/etc/netplan/" + Data.begin()->first;
        system("sudo systemctl stop NetworkManager");
        std::cout<< "Stop Network\n";
        ChangeFileInfo(ContentOfFile, OldPassword, NewPassword);
        std::cout<< "Change File Info Network\n";
        saveDataToFile(FileName, ContentOfFile);
        std::cout<< "Save Data To Network File\n";
        system("sudo netplan apply");
        std::cout<< "Apply Network\n";
        system("sudo systemctl restart NetworkManager");
    }
    return false;
}
/**
 * @brief 
 * 
 * @param OldSsid 
 * @param OldPassword 
 * @param NewSsid 
 * @param NewPassword 
 * @return true 
 * @return false 
 */
bool Modifiy_Saved_Network( const std::string &OldSsid, const std::string &OldPassword,
                            const std::string &NewSsid, const std::string &NewPassword)
{
    if(CheckIFNetworkExist(OldSsid) && OldSsid.find(NewSsid) == std::string::npos)
    {
        if(NewPassword.length() >= 8 && NewPassword != OldPassword)
        {
            std::string ContentOfFile = "";
            std::string FileName = "";
            std::map<std::string, std::string> Data =  FindSsidInformation(OldSsid);
            ContentOfFile = Data.begin()->second;
            FileName = "/etc/netplan/" + Data.begin()->first;
            system("sudo systemctl stop NetworkManager");
            std::cout<< "Stop Network\n";
            ChangeFileInfo(ContentOfFile, OldSsid, NewSsid);
            ChangeFileInfo(ContentOfFile, OldPassword, NewPassword);
            std::cout<< "Change File Info Network\n";
            saveDataToFile(FileName, ContentOfFile);
            std::cout<< "Save Data To Network File\n";
            system("sudo netplan apply");
            std::cout<< "Apply Network\n";
            system("sudo systemctl restart NetworkManager");
            return true;
        }
    }
    return false;
}


bool Search_For_Network(const std::string &ssid)
{
    std::string availablenetworks = execCommand((CommandList[AVAILABLE_WIFI] ).c_str());
    if(availablenetworks.find(ssid) != std::string::npos)
    {
        return true;
    }
    return false;
}

void show_saved_network()
{
    std::cout << execCommand((CommandList[SAVED_WIFI] + "| grep wifi").c_str());
}

void show_available_network()
{
    std::cout << execCommand(CommandList[AVAILABLE_WIFI].c_str());
}

static std::map<std::string, std::string> parseNetplanFiles() {
    std::vector<std::string> files = GenerateFilesFromDir();
    
    std::map<std::string, std::string> localNetworkCrendentials;
    for (const auto& file : files) {
        std::string command = "sudo cat /etc/netplan/" + file;
        std::string returned = execCommand(command.c_str());

        std::string::size_type pos = 0;
        pos = returned.rfind("name: ");
        std::string::size_type start = returned.find("\"", pos) + 1;
        std::string::size_type end = returned.find("\"", start);
        std::string ssid = returned.substr(start, end - start);

        pos = returned.find("password: ");
        if (pos != std::string::npos) {
            start = returned.find("\"", pos) + 1;
            end = returned.find("\"", start);
            std::string password = returned.substr(start, end - start);
            localNetworkCrendentials[ssid] = password;
        }
    }
    return localNetworkCrendentials;
}

static std::vector<std::string> GenerateFilesFromDir()
{
    std::vector<std::string> files = {};
    for(auto i : execCommand("ls /etc/netplan"))
    {
        static std::string Temp;
        if(i != '\n')
        {
            Temp+=i;
        }
        else{
            files.push_back(Temp);
            Temp.clear();
        }
    }
    return files;
}

static std::map<std::string, std::string> FindSsidInformation(const std::string &SSID)
{
    std::vector<std::string> files = GenerateFilesFromDir();
    std::map<std::string, std::string> FileInfo = {{"Null", "Null"}};
    for (const auto& file : files) {
        std::string command = "sudo cat /etc/netplan/" + file;
        std::string returned = execCommand(command.c_str());
        
        if(returned.find(SSID) != std::string::npos)
        {
            FileInfo.clear();
            FileInfo.insert({file, returned}) ;
            return FileInfo;
        }
    }
    return FileInfo;
}

static void ChangeFileInfo(std::string& fileData, const std::string& OldWord, const std::string& NewWord)
{
    size_t pos = 0;
    int counter = 0;
    // std::cout<< fileData<< std::endl;
    // std::cout << "Press Enter to continue...";
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
    // std::cin.get(); // Wait for Enter key
    while ( ( pos = fileData.find(OldWord) ) != std::string::npos ) {
        fileData.replace(pos, OldWord.length(), NewWord);
        std::cout << "founded " << counter++ << std::endl;
    }
}

static void saveDataToFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        
        for (const auto& network : NetworkCrendentials) {
            outfile << std::endl;
            outfile << "SSID: " << network.first << std::endl <<"Password: " << network.second << std::endl;
            outfile << std::endl << "*********************************************************************" << std::endl;
        }
        outfile.close();
        std::cout << "Networks saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}
static void saveDataToFile(const std::string& filename, const std::string& FileContent) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        
        for (const auto& Data : FileContent) {
            outfile << Data;
        }
        outfile.close();
        std::cout << "Data saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}


static bool CheckIFNetworkExist(const std::string& SSID)
{
    std::string savednetworks = execCommand((CommandList[SAVED_WIFI] + "| grep wifi").c_str());

    if(savednetworks.find(SSID) != std::string::npos)
    {
        return true;
    }
    return false;
}