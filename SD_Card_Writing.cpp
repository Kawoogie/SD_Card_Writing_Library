#include "SD_Card_Writing.h"

// File Prefix and header
#define FILE_PREFIX "MAXM86161_Data_"
#define FILE_HEADER "red, green, ir, force,\n"
#define FILE_FORMAT ".csv"

// Properties for the SD card logging
#define BUFFER_MAX_LEN 10

using ThisThread::sleep_for;

// SDBlockDevice sd(PinName::P0_6, PinName::P0_5, PinName::P0_4, PinName::P0_7); // Specify your hardware pins
BlockDevice *bd = BlockDevice::get_default_instance();  // mosi, miso, sclk, cs

//Configure pin for SD card Dectection
DigitalIn uSDdetect(P2_2, PullUp);

// File system to use
FATFileSystem fs("fs");

// Variable and function to read file names on SD card.
vector<string> filenames;

SD_Card_Writing::SD_Card_Writing()
{

}

int SD_Card_Writing::write()
{
    return 0;
}

int prepare_card()
{
    return 0;
}

void set_filename_root(str filename)
{
    _file_root = filename;
}

void set_file_header(str header)
{
    _file_header = header;
}

void set_file_format(str format)
{
    _file_format = format;
}

void SD_Card_Writing::print_file_names()
{
    serial.printf("File names:\n");
    for(vector<string>::iterator it=filenames.begin(); it < filenames.end(); it++)  
    {
        serial.printf("%s\n\r",(*it).c_str());
    }
    serial.printf("\n");
}

string SD_Card_Writing::open_new_file()
{
    // Search for next available file name
    bool file_name_found = false;
    int file_number = 1;
    string file_name;
    while (!file_name_found){

        // Convert the int to a string
        string name = FILE_PREFIX;
        name.append(to_string(file_number));
        // Construct the file name
        name.append(FILE_FORMAT);

        // Search for the string inside the vector of file names on the SD card.
        if ( std::find(filenames.begin(), filenames.end(), name) != filenames.end() ){
            file_number++; // If the file name is found, increment the number and search again.
            } else{
            file_name_found = true; // Update that the value of the next available file was found.
            file_name = name;}
    }
    // Open the file data will be saved in
    // Construct the file name and path
    string file_path = "/fs/";
    file_path.append(file_name);

    return file_path;
}

void SD_Card_Writing::read_file_names(char *dir)
{
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(dir);
    //read all directory and file names in current directory into filename vector
    while((dirp = readdir(dp)) != NULL) {
        filenames.push_back(string(dirp->d_name));
    }
    closedir(dp);
}

int SD_Card_Writing::sd_card_check()
{
    if (!uSDdetect) {
        return 0;
    }
    else{
        return 1
    }
}

int SD_Card_Writing::mount_file_system()
{
    fflush(stdout);
    int err = fs.mount(bd);
    return err;
}

int SD_Card_Writing::unmount_system()
{
    fflush(stdout);
    int err = fs.unmount();
    return err;
}

int SD_Card_Writing::_remove_system_file()
{
    char* system_file = (char*) "System Volume Information";
    int found = false;
    // Code to find the system file. Code removes the system_file name from the list of files.
    if (std::find(filenames.begin(), filenames.end(), system_file) != filenames.end()) {
        vector<string>::iterator new_end; 
        new_end = remove(filenames.begin(), filenames.end(), system_file);  // Returns index of last value not removed. Not needed for my code
         found = true;
         }
    return found;
}

