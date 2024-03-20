#ifndef SD_CARD_WRITING_H
#define SD_CARD_WRITING_H
/**
 * Library to write to an SD card with
 * the MAX32630FTHR
 * This library was written to write a custom
 * set of data to an SD card with a particular file
 * name convention in a .csv file.
 * 
 * Here is an example of how the code is used:
 * @code
 * 
 * 
 * 
 * 
 * 
 * @endcode
*/
#include "mbed.h"
#include "max32630fthr.h"
#include "USBSerial.h"

#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include <type_traits>
#include <vector>
#include <string>


class SD_Card_Writing {
    public:
    SD_Card_Writing();
    int write();

    void print_file_names();
    string open_new_file();

    int remove_system_file();
    void read_file_names(char *dir);
    int sd_card_check();
    int mount_file_system();
    int unmount_system();



    private:


};

#endif