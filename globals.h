#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <vector>

using namespace std;

struct screen_config{

    int osu_screen_w = 512;
    int osu_screen_h = 384;

    int screen_w =1920;
    int screen_h =1020;

    int left_gap_x= 384;
    int right_gap_x =384;
    int total_x_width=1152;

    int up_gap_y=125;
    int down_gap_y=91;
    int total_y_height=864;

    float multipler = 2.25;

    int hit_box_of_note = 30;

};

class globals{
  public:

    string def_indir_map_file_name = "hard.osu";

    string map_modes = "HDHR";                                  //Will play hdhr always
    bool mod_hr_on=true;
    bool mod_hd_on=true;

    bool debug_mode=true;
    bool draw_ui_sshot=false;                                    //experimental debuging
    int ui_avarage_color_breaker=2;                              //if avg. color > 4 then start emulate keys
    int ui_gap_beetwen_sshots = 1000;                            //5ms beetwen taking screenshots

    string key_enum_start_way = "keyboard";
    string event_id = "/dev/input/event4";                      //maybe make it auto
    bool ui_helper_for_first_obj=true;
    string osu_replay_key="t";                                   //make t replay

    screen_config res1920_1080;

    int x_break_distance = 75;
    int n_lock_timer = 4;
    int manual_ar_picking_time=-7;
    int post_error_fix =100;

    long extracted_minimum_key_press_time;

    vector<vector<int>> ARtable{{70,900},{80,750},{90,600},{91,585},{98,480},{100,450}};
    vector<vector<int>> ODtable{{70,37,83,138},{80,31,75,118},{84,28,72,113},{90,25,67,108},{91,24,66,107},{98,20,60,100},{100,19,59,89}};
    vector<int> currentODtable;


    vector<int> circle_error_pattern_995{61,65,67,25,28,38,84,89,3,8,
                                     48,52,57,39,44,13,17,21,59,
                                     96,94,88,71,50,9,14,54,20,
                                     69,77,97,76,43,75,68,49,5,11,
                                     26,39,49,95,84,73,61,78,55,
                                     15,29,44,66,86,80,74,57,29,37
                                     ,11,17,44,60,63,68,85,71,57,
                                      56,44,21,29,17,5,8,27,39,
                                      41,61,63,54,70,81,91,70};                                                   //%99.5+ pattern

    vector<int> circle_error_pattern_975{61,65,67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        102,94,88,71,5,07,14,54,20,
                                        69,77,97,76,43,75,68,49,5,11,
                                        26,39,49,95,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,00,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,-5,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45,61,65,67,25,28,38,84,89,00,50,
                                         48,52,57,39,44,13,17,21,59,
                                         102,94,88,71,5,07,14,54,20,
                                         69,77,97,76,43,75,68,49,5,11,
                                         26,39,49,95,84,73,61,78,55,
                                         15,29,44,66,86,80,74,57,29,37,
                                         11,17,44,60,63,68,85,71,57,
                                         56,44,21,29,17,00,15,27,39,
                                         41,61,63,54,70,81,91,70,44,
                                         14,35,40,60,45,50,52,71,37,
                                         27,42,55,65,54,42,45};                                                    //%97.5+ pattern

    vector<int> circle_error_pattern_981{61,65,67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        102,94,88,71,9,8,14,54,20,
                                        69,77,93,76,43,75,68,49,5,11,
                                        26,39,49,94,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,00,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45,61,
                                        65,67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        112,94,88,71,9,8,14,54,20,
                                        69,77,93,76,43,75,68,49,5,11,
                                        26,39,49,94,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,00,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45};                                                    //%98.1+ pattern

    vector<int> circle_error_pattern_985{61,65,67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        106,88,75,45,38,10,14,54,20,
                                        69,77,93,76,43,75,68,49,5,11,
                                        26,39,49,94,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,3,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45,61,65,
                                        67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        95,88,75,45,38,10,14,54,20,
                                        69,77,93,76,43,75,68,49,5,11,
                                        26,39,49,94,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,-5,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45};                                                    //%98.5+ pattern

    vector<int> circle_error_pattern_990{61,65,67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        106,88,75,45,38,10,14,54,20,
                                        69,77,93,76,43,75,68,49,15,39,
                                        26,39,49,94,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,3,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45,61,65,
                                        67,25,28,38,84,89,00,50,
                                        48,52,57,39,44,13,17,21,59,
                                        95,88,75,45,38,10,14,54,20,
                                        69,77,93,76,43,75,68,49,7,16,
                                        26,39,49,94,84,73,61,78,55,
                                        15,29,44,66,86,80,74,57,29,37,
                                        11,17,44,60,63,68,85,71,57,
                                        56,44,21,29,17,45,15,27,39,
                                        41,61,63,54,70,81,91,70,44,
                                        14,40,60,45,50,52,71,37,
                                        27,42,55,65,54,42,45,61,65,67,
                                         25,28,38,84,89,00,50,
                                         48,52,57,39,44,13,17,21,59,
                                         68,88,75,45,38,10,14,54,20,
                                         69,77,93,76,43,75,68,49,15,39,
                                         26,39,49,94,84,73,61,78,55,
                                         15,29,44,66,86,80,74,57,29,37,
                                         11,17,44,60,63,68,85,71,57,
                                         56,44,21,29,17,3,15,27,39,
                                         41,61,63,54,70,81,91,70,44,
                                         14,40,60,45,50,52,71,37,
                                         27,42,55,65,54,42,45,61,65,
                                         67,25,28,38,84,89,00,50,
                                         48,52,57,39,44,13,17,21,59,
                                         95,88,75,45,38,10,14,54,20,
                                         69,77,93,76,43,75,68,49,9,16,
                                         26,39,49,94,84,73,61,78,55,
                                         15,29,44,66,86,80,74,57,29,37,
                                         11,17,44,60,63,68,85,71,57,
                                         56,44,21,29,17,45,15,27,39,
                                         41,61,63,54,70,81,90,70,44,
                                         14,40,60,45,50,52,71,37,
                                         27,42,55,65,54,42,45};                                                    //%99+ pattern



    vector<int> slider_error_pattern{60,63,69,20,25,35,87,92,-5,0,
                                     47,55,62,30,45,5,9,18,69,
                                     110,100,97,79,50,-2,3,59,15,
                                     72,82,115,77,40,76,67,48,-5,12,
                                     25,38,48,101,88,75,60,75,54,
                                     14,30,45,65,87,82,77,52,24,38
                                     ,10,19,44,60,63,68,92,71,57,
                                      56,44,21,29,17,-2,6,27,39,
                                      41,61,63,54,70,81,99,70};                                                   //(+-%10 pattern)
};

#endif // GLOBALS_H