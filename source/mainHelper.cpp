#include "../include/mainHelper.hpp"

static void WifiSubMenu();
static void BluetoothSubMenu();

void MainMenu()
{
    int Choice = 0;
    std::cout << "You should know that most of this Program Feature \nNeeds You to be an admin\nIF You aren't you should exit and run again\nWith Admin Previlege"<<std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
    std::cin.get(); // Wait for Enter key
    while(true)
    {
        system("clear");
        std::cout << "Control Program \n-----------------------"<<std::endl;
        std::cout << "1- Wifi Control" <<  std::endl;
        std::cout << "2- Bluetooth Control" << std::endl;
        std::cout << "3- Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> Choice;
        
        switch(Choice)
        {
            case 1: WifiSubMenu();
                    break;
            case 2: BluetoothSubMenu();
                    break;
            case 3: exit(0);
            default: break;
        }
        system("clear");
    }
}

static void WifiSubMenu()
{
    int Choice = 0;
    std::string ssid = "";
    std::string password = "";
    std::string Newssid = "";
    std::string Newpassword = "";
    std::string FileName = "";

    while(true)
    {
        system("clear");
        std::cout << "Wifi Control Program \n-----------------------"<<std::endl;
        std::cout << "1- Display Wifi Status" << std::endl;
        std::cout << "2- Turn Wifi On" << std::endl;
        std::cout << "3- Turn Wifi Off" << std::endl;
        std::cout << "4- Connect to Wifi" << std::endl;
        std::cout << "5- Remove a Saved Network" << std::endl;
        std::cout << "6- Modify SSID Only" << std::endl;
        std::cout << "7- Modify Password Only" << std::endl;
        std::cout << "8- Modify SSID and Password" << std::endl;
        std::cout << "9- Search for a Network" << std::endl;
        std::cout << "10- Save Network" << std::endl;
        std::cout << "11- Back To Main Menu" << std::endl;
        std::cout << "Choice: ";
        std::cin >> Choice;
        system("clear");

        switch (Choice) {
            case 1: 
                    std::cout << Display_wifi_status() << std::endl;
                    break;

            case 2: 
                    TurnWifi(true);
                    std::cout << "Wifi On" << std::endl;
                    break; 

            case 3: 
                    TurnWifi(false);
                    std::cout << "Wifi Off" << std::endl;
                    break; 

            case 4: 
                    std::cout << "1- Old Network" << std::endl;
                    std::cout << "2- New Network" << std::endl;
                    std::cin >> Choice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                    switch (Choice) {
                        case 1: 
                                show_saved_network();
                                std::cout << "Please Enter SSID: " << std::endl;
                                std::getline(std::cin, ssid);  // Get the full SSID with spaces
                                std::cout << "Connecting to " << ssid << std::endl;
                                if(Connect_To_Wifi(ssid)) 
                                    std::cout << "Connected to " << ssid << std::endl;
                                else 
                                    std::cout << "Failed to Connect to " << ssid << " - Incorrect SSID Probably!" << std::endl;
                                break;

                        case 2: 
                                show_available_network();
                                std::cout << "Please Enter SSID: " << std::endl;
                                std::getline(std::cin, ssid);  // Get the full SSID with spaces
                                std::cout << "Please Enter Password: " << std::endl;
                                std::getline(std::cin, password);  // Get the full password with spaces
                                std::cout << "Trying to connect to " << ssid << std::endl;
                                Connect_To_Wifi(ssid, password);
                                std::cout << ssid << password;
                                break;

                        default: 
                                break;
                    }
                    break;

            case 5: 
                    show_saved_network();
                    std::cout << "Please Enter SSID: " << std::endl;
                    std::getline(std::cin, ssid);  // Get the full SSID with spaces
                    if(Remove_Saved_Network(ssid)) 
                        std::cout << "Deleted successfully" << std::endl;
                    else 
                        std::cout << "Can't delete " << ssid << " - Incorrect SSID Probably!" << std::endl;
                    break;
    
            case 6: std::cout << "Please Enter Old SSID: " << std::endl;
                    std::getline(std::cin, ssid);   
                    std::cout << "Please Enter New SSID: " << std::endl;
                    std::getline(std::cin, Newssid);
                    if(Modifiy_Saved_Network(ssid, Newssid)) std::cout << "Modified successfully!" << std::endl;
                    else std::cout << "Can't modify " << ssid << " - Incorrect SSID Probably " << std::endl;
                    break;
    
            case 7: std::cout << "Please Enter SSID: " << std::endl;
                    std::getline(std::cin, ssid);   
                    std::cout << "Please Enter Old Password: " << std::endl;
                    std::getline(std::cin, password);
                    std::cout << "Please Enter New Password: " << std::endl;
                    std::getline(std::cin, Newpassword);
                    if(Modifiy_Saved_Network(ssid, password, Newpassword)) std::cout << "Modified successfully!" << std::endl;
                    else std::cout << "Can't modify " << ssid << " - Incorrect SSID OR Password Probably " << std::endl;
                    break;
    
            case 8: std::cout << "Please Enter Old SSID: " << std::endl;
                    std::getline(std::cin, ssid);   
                    std::cout << "Please Enter Old Password: " << std::endl;
                    std::getline(std::cin, password);
                    std::cout << "Please Enter New SSID: " << std::endl;
                    std::getline(std::cin, ssid);   
                    std::cout << "Please Enter New Password: " << std::endl;
                    std::getline(std::cin, Newpassword);
                    if(Modifiy_Saved_Network(ssid, password, Newssid, Newpassword)) std::cout << "Modified successfully!" << std::endl;
                    else std::cout << "Can't modify " << ssid  << std::endl;
                    break;
    
            case 9: std::cout << "Please Enter SSID: " << std::endl;
                    std::getline(std::cin, ssid);  // Get the full SSID with spaces
                    if(Search_For_Network(ssid)) 
                        std::cout << "Found!" << std::endl;
                    else 
                        std::cout << "Not Found!" << std::endl;
                    break;
            
            case 10:std::cout << "1- save during program runtime" << std::endl;
                    std::cout << "2- save to file" << std::endl;
                    std::cout << "3- Go back to Wifi Menu"<< std::endl;
                    std::cout << "Please Enter your choice: " << std::endl;
                    std::cin >> Choice;
                    switch(Choice)
                    {
                        case 1: Save_WiFi_Networks();
                                std::cout << "DONE!!" << std::endl;
                                break;

                        case 2: std::cout << "Enter File name without spaces: ";
                                std::cin >> FileName;
                                Save_WiFi_Networks(FileName);
                                std::cout << "DONE!!" << std::endl;
                                break;

                        case 3: break;
                        
                        default: std::cout << "Invalid choice" << std::endl;
                    }
                    break;
            case 11:return;
            
            default:std::cout << "incorrect Choice *_* " << std::endl;
                    break;
        }

        // Wait for the user to press Enter before continuing
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
        std::cin.get(); // Wait for Enter key
    }
}

static void BluetoothSubMenu()
{
    int Choice = 0;
    std::string Address = "";
    while(true)
    {
        system("clear");
        std::cout << "Bluetooth Control Program \n-----------------------"<<std::endl;
        std::cout << "1- Display Bluetooth Status" << std::endl;
        std::cout << "2- Turn Bluetooth On" << std::endl;
        std::cout << "3- Turn Bluetooth Off" << std::endl;
        std::cout << "4- Connect to Bluetooth" << std::endl;
        std::cout << "5- Back To Main Menu" << std::endl;
        std::cout << "Choice: ";
        std::cin >> Choice;
        system("clear");
        switch (Choice) {
            case 1: std::cout << Display_Bluetooth_Status() << std::endl;
                    break;
            case 2: if(TurnBluetooth()) std::cout << "Turned On" << std::endl;
                    else std::cout << "Can't Turn bluetooth On" << std::endl;
                    break;
            case 3: if(TurnBluetooth()) std::cout << "Turned Off" << std::endl;
                    else std::cout << "Can't Turn bluetooth Off" << std::endl;
                    break; 
            case 4: std::cout << "Please Wait until Scan is finished" << std::endl;
                    system("hcitool scan");
                    std::cout <<"Note: if your device not here enter anything instead of real address and go back" << std::endl;
                    std::cout << "Please Enter Device Address" << std::endl;
                    std::cin >> Address;
                    std::cout << std::endl;
                    std::cout << "1- Pair To device" << std::endl;
                    std::cout << "2- Connect To device" << std::endl;
                    std::cout << "3- Go Back to Bluetooth Menu" << std::endl;
                    std::cout << "Choice: ";
                    std::cin >> Choice;
                    switch (Choice) {
                        case 1: if(ConnectBluetoothDevice(Address, true)) std::cout << "Paired Success!" <<std::endl;
                                else std::cout << "Can't Pair Device" << std::endl; 
                                break;
                        case 2: if(ConnectBluetoothDevice(Address)) std::cout << "Connection Success!" <<std::endl;
                                else std::cout << "Can't Connect Device" << std::endl;
                                break;
                        default:std::cout << "incorrect Choice *_* " << std::endl;
                                break;
                    }
                    break;
                    
            case 5: return;
            default: 
                    std::cout << "incorrect Choice *_* " << std::endl;
                    break;
        }
        // Wait for the user to press Enter before continuing
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
        std::cin.get(); // Wait for Enter key
    }
}
