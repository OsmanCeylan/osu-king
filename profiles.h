#ifndef PROFILES_H
#define PROFILES_H

#include <string>
#include <iostream>
#include <fstream>

#include "mymap.h"

using namespace std;

class profiles
{
  public:

    short setting_counter;

    string osu_replay_key;
    bool osu_replay_key_checker;

    bool debug_pmode;
    bool debug_pmode_checker;

    string hack_mode;
    bool hack_mode_checker;

    string osu_file_name;
    bool osu_file_name_checker;

    string key_enum_start_way;
    bool key_enum_start_way_checker;

    string key_enum_start_action;
    bool key_enum_start_action_checker;

    char key_enum_keyboard_start_key;
    bool key_enum_keyboard_start_key_checker;

    string event_id;
    bool event_id_checker;

    string map_modes;
    bool map_modes_checker;

    bool file_error;
    ifstream init_file_stream;

    short x_break_distance;
    bool x_break_distance_checker;

    short n_lock_timer;
    bool n_lock_timer_checker;

    /*string key_method;

    string osu_retry_button;
    char key_press_waited_key;

    int x_press_obj_dist;
    int x_press_obj_time_dist;
    bool slider_uses_check;

    int slider_check_max_random;
    int slider_no_check_max_random;
    int min_sleep_error;
    int sleep_error_multipler;

    bool press_some_greens;
    int  press_some_greens_prime;
    bool press_some_oranges;
    int  press_some_oranges_prime;

    bool my_prefect_hit;
    bool correct_my_hit;

    int my_screen_w;
    int my_screen_h;

    bool enable_debug;
    float silence_jump_wait;
    int nlock_frekans;
    bool timing_testing;
    bool errors_specs;

    int slider_out_error_skew;
    int press_gap;*/

    profiles(string );

    bool get_file_error(){
        if (file_error)     cout << "Couldnt open settings.ini" << endl;
        return file_error;
    }

    bool check(mymap& );
    void loaddefaults();
    void usedefaults();
    void profiledebugprint();

};



struct OD{
    int neg_green_start;
    int neg_green_width;
    int neg_blue_start;
    int neg_blue_width;

    int pos_blue_start;
    int pos_blue_width;
    int pos_green_start;
    int pos_green_width;
    float multipler;
    int green_multipler;

    float OD_NUM;
};

struct OD getCurrentODinfo(float ,struct OD& );

#endif // PROFILES_H
