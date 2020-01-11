#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "globals.h"

using namespace std;

class mymap{
private:

    string map_file_name;
    ifstream osu_map_file;
    bool open_error;

    short countdown;
    string title;
    string creator;
    string version;
    string artist;

    float HP;
    float CS;
    float OD;
    float AR;
    float slider_multipler;
    float slider_tick_rate;

    u_int object_count;
    u_int times_count;

public:

    vector<vector<int> > times;
    vector<string> dumped_file;

    mymap(string ,bool );
    int gettimings(){return times_count;}
    float getOD(){return OD;}
    float getAR(){return AR;}
    bool apply_map_modes(globals& ,bool);

    bool get_file_error();
    bool fill_osu_file(bool );
    bool dump_file_to_ram(bool );
    bool extract_timings(bool );
    void close_file();

    void printmapprops(bool );
    void printdumps(bool );
    void printtimings(bool );
    void printmodes(bool );
    int least_press_time_gap(globals& );

};

#endif // MYMAP_H
