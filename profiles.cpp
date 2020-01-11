#include "profiles.h"
#include "main.h"

profiles::profiles(std::string init_file)
{
    file_error=false;
    init_file_stream.open(init_file);
    setting_counter=0;

    if (!(init_file_stream.is_open()))
    {
        cout << "Cant open file @open_setting_file" << endl;
        file_error=true;
        return;
    }

    string* line = new string;
    string  comment= "#";

    loaddefaults();

    while ( !init_file_stream.eof() )
    {

      init_file_stream >> *line;

      if (line->compare("debug_mode")==0)
      {
          setting_counter++;
          init_file_stream >> *line;

          debug_pmode=stoi(*line);
          debug_pmode_checker=true;

      }

      else if (line->compare("n_lock_timer")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          n_lock_timer=stoi(*line);
          n_lock_timer_checker=true;
      }

      else if (line->compare("hack_method")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          hack_mode.insert(0,*line);
          hack_mode_checker=true;
      }

      else if (line->compare("osu_file_name")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          osu_file_name.insert(0,*line);
          osu_file_name_checker=true;
      }

      else if (line->compare("key_enum_start_way")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          key_enum_start_way.insert(0,*line);
          key_enum_start_way_checker=true;
      }

      else if (line->compare("key_enum_start_action")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          key_enum_start_action.insert(0,*line);
          key_enum_start_action_checker=true;
      }

      else if (line->compare("key_enum_keyboard_start")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          key_enum_keyboard_start_key=*line->c_str();
          key_enum_keyboard_start_key_checker=true;
      }


      else if (line->compare("key_enum_dev_event_id")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          event_id.insert(0,*line);
          event_id_checker=true;
      }

      else if (line->compare("map_mode")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          map_modes.insert(0,*line);
          map_modes_checker=true;
      }

      else if (line->compare("osu_replay_key")==0)
      {
          setting_counter++;
          init_file_stream >> *line;
          osu_replay_key.insert(0,*line);
          osu_replay_key_checker=true;

      }

      else if (line->compare("x_break_distance")==0)
      {
          setting_counter++;
          init_file_stream >> *line;

          x_break_distance=stoi(*line);
          x_break_distance_checker=true;
      }


    }

    usedefaults();
    profiledebugprint();
}

void profiles::loaddefaults()
{
    debug_pmode_checker=false;
    hack_mode_checker=false;
    osu_file_name_checker=false;
    key_enum_start_way_checker=false;
    key_enum_start_action_checker=false;
    key_enum_keyboard_start_key_checker=false;
    event_id_checker=false;
    map_modes_checker=false;
    osu_replay_key_checker=false;
    x_break_distance_checker=false;
    n_lock_timer_checker=false;

}

void profiles::usedefaults(){

    if (debug_pmode_checker==false)   debug_pmode=0;
    if (hack_mode_checker==false)       hack_mode="key_enum";
    if (osu_file_name_checker==false)   osu_file_name="hard.osu";
    if (key_enum_start_way_checker==false)  key_enum_start_way="mouse";
    if (key_enum_start_action_checker==false)   key_enum_start_action="press";
    if (key_enum_keyboard_start_key_checker==false) key_enum_keyboard_start_key='z';
    if (map_modes_checker==false)       map_modes="HDHR";
    if (osu_replay_key_checker==false)       osu_replay_key='t';
    if (x_break_distance_checker==false)       x_break_distance=50;
    if (n_lock_timer_checker==false)       n_lock_timer=5;

}

void profiles::profiledebugprint(){
    if (debug_pmode){
        cout << "Loaded settings" << endl;
        cout << "---------------------------------------" << endl;

        cout << hack_mode << "  -  ";
        if (!hack_mode_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << osu_file_name << "  -  ";
        if (!osu_file_name_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << key_enum_start_way << "  -  ";
        if (!key_enum_start_way_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << key_enum_start_action << "  -  ";
        if (!key_enum_start_action_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << key_enum_keyboard_start_key << "  -  ";
        if (!key_enum_keyboard_start_key_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << event_id << "  -  ";
        if (!event_id_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << map_modes << "  -  ";
        if (!map_modes_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << osu_replay_key << "  -  ";
        if (!osu_replay_key_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << x_break_distance << "  -  ";
        if (!x_break_distance_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;

        cout << n_lock_timer << "  -  ";
        if (!n_lock_timer_checker)
            cout << "Def" << endl;
        else
            cout << "Param" << endl;


        cout << "-----------------------------------------"<< endl;
    }

}

struct OD getCurrentODinfo(float my_od, struct OD& crr)
{
    struct OD OD98, OD84, OD91, OD100;

    //THESE NUMBERS IS MANUAL RIGHT NOW
    //NEEDS TO BE AUTOMATIC DETECT

    /*OD98.OD_NUM=9.8;
    OD98.neg_green_start=-97;
    OD98.neg_green_width=64;
    OD98.neg_blue_start=-33;
    OD98.neg_blue_width=33;

    OD98.pos_blue_start=0;
    OD98.pos_blue_width=33;
    OD98.pos_green_start=34;
    OD98.pos_green_width=64;
    OD98.multipler=20.5;
    OD98.green_multipler=40;*/

    OD98.OD_NUM=9.8;                            //PASS TEST
    OD98.neg_green_start=-61;
    OD98.neg_green_width=40;
    OD98.neg_blue_start=-21;
    OD98.neg_blue_width=21;

    OD98.pos_blue_start=0;
    OD98.pos_blue_width=21;
    OD98.pos_green_start=21;
    OD98.pos_green_width=40;
    OD98.multipler=20.5;
    OD98.green_multipler=40;

  /*OD100.OD_NUM=10;
    OD100.neg_green_start=-96;
    OD100.neg_green_width=64;
    OD100.neg_blue_start=-32;
    OD100.neg_blue_width=31;

    OD100.pos_blue_start=1;
    OD100.pos_blue_width=31;
    OD100.pos_green_start=32;
    OD100.pos_green_width=64;
    OD100.multipler=19.5;   if (debug_mode)
    OD100.green_multipler=40;*/

    OD100.OD_NUM=10.0;                              //PASS TEST
    OD100.neg_green_start=-61;
    OD100.neg_green_width=40;
    OD100.neg_blue_start=-21;
    OD100.neg_blue_width=21;

    OD100.pos_blue_start=0;
    OD100.pos_blue_width=21;
    OD100.pos_green_start=21;
    OD100.pos_green_width=40;
    OD100.multipler=19.5;
    OD100.green_multipler=40;

  /*OD84.OD_NUM=8.4;
    OD84.neg_green_start=-115;
    OD84.neg_green_width=69;
    OD84.neg_blue_start=-46;
    OD84.neg_blue_width=45;

    OD84.pos_blue_start=1;
    OD84.pos_blue_width=47;
    OD84.pos_green_start=48;
    OD84.pos_green_width=67;
    OD84.multipler=28.5;
    OD84.green_multipler=43;*/

    OD84.OD_NUM=8.4;
    OD84.neg_green_start=-72;
    OD84.neg_green_width=43;
    OD84.neg_blue_start=-29;
    OD84.neg_blue_width=29;

    OD84.pos_blue_start=0;
    OD84.pos_blue_width=29;
    OD84.pos_green_start=29;
    OD84.pos_green_width=43;
    OD84.multipler=28.5;
    OD84.green_multipler=43;

    OD91.OD_NUM=9.1;
    OD91.neg_green_start=-107;
    OD91.neg_green_width=67;
    OD91.neg_blue_start=-39;
    OD91.neg_blue_width=38;

    OD91.pos_blue_start=1;
    OD91.pos_blue_width=39;
    OD91.pos_green_start=40;
    OD91.pos_green_width=68;
    OD91.multipler=24.5;
    OD91.green_multipler=42;

    //if (debug_mode)     cout << "C_OD: " << my_od << endl;

    if (my_od*10 == 100)      crr = OD100;
    if (my_od*10 == 98)     crr = OD98;
    if (my_od*10 == 91)     crr = OD91;
    if (my_od*10 == 84)     crr = OD84;

    return OD91;
}

