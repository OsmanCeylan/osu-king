#include "main.h"

using namespace std;
using namespace cv;

int main()
{
    globals settings;

    mymap osu_map(settings.def_indir_map_file_name, settings.debug_mode);
    if (osu_map.get_file_error())                                              return 0;

    if (!osu_map.fill_osu_file(settings.debug_mode))                           return 0;
    if (!osu_map.dump_file_to_ram(settings.debug_mode))                        return 0;
    if (!osu_map.extract_timings(settings.debug_mode))                         return 0;
    if (!osu_map.apply_map_modes(settings, settings.debug_mode))               return 0;
    osu_map.least_press_time_gap(settings);
    osu_map.close_file();

    Display* display;
    Window root;

    while (true){
        if (!emulate(settings, osu_map, display, root))  break;
    }

    return 0;
}

bool emulate(globals& setts, mymap& a_map, Display* display, Window& root)
{

    long first_stamp, next_stamp, new_stamp, polation, t, check;
    bool slider_on=false, X=false, last_is_x=false, breaked=false;
    struct timeval t1, t2, t3 , t4;
    unsigned int j=0;
    hit_object* a_object = new hit_object;
    hit_object* b_object = new hit_object;

    XKeyboardState board_state;
    KeyCode keys[4];

    if (!switch_to_osu(setts.debug_mode))   return false;

    a_object->fill(a_map.dumped_file[0]);
    a_object->fill_vector(a_map);

    first_stamp = a_object->gettime();
    if (setts.debug_mode) cout << "Defined 1st object" << a_object->gettime() <<  endl;

    get_window_focus(&display, root, setts.debug_mode);
    set_key_codes(setts, display, keys);
    dummy_press(setts,display, keys);

    if (setts.key_enum_start_way.compare("mouse")==0)       mouse_event(setts, &t1);
    if (setts.key_enum_start_way.compare("keyboard")==0)    keyevent(setts,'x',&t1);
    if (setts.ui_helper_for_first_obj)                      ui_detect_first_object(setts,display,root,a_object->getx(),a_object->gety(),setts.debug_mode);
    if (setts.ui_helper_for_first_obj)                      wait_for_ar(setts,a_map.getAR(),&t1);

 /*-
  *M
 -*/

    for (unsigned int i=0; i<a_map.dumped_file.size()-1; i++)
    {
        a_object->fill(a_map.dumped_file[i]);
        b_object->fill(a_map.dumped_file[i+1]);
        new_stamp = a_object->gettime();
        next_stamp = b_object->gettime();

        if (i>0){
            relocate_to_left_orange(new_stamp,next_stamp,setts);
            make_error(new_stamp,next_stamp,setts,a_object->gettype(),j);
        }

        if (setts.debug_mode) cout << "---------------------------------------" << endl;
        if (setts.debug_mode) cout << "new: " << new_stamp/1000 << endl;
        if (setts.debug_mode) cout << "dis: " << (new_stamp - first_stamp)/1000 << endl;

        t=0;
        polation=256;
        while (t<((new_stamp-first_stamp))){
             gettimeofday(&t2, NULL);
             t = ((t2.tv_sec * 1000000) + t2.tv_usec) - ((t1.tv_sec * 1000000) + t1.tv_usec);
             nsleep((new_stamp-first_stamp)-t-polation);
             if (polation==64 || new_stamp-first_stamp<0) break;
             polation/=2;
        }
        if (setts.debug_mode)
            cout << "N: " << (new_stamp-first_stamp)/1000 << " Time Passed: " << t/1000 << endl;

        X=should_x(setts,*a_object,*b_object);
        if (last_is_x){ X=false; last_is_x=false;}


        gettimeofday(&t3, NULL);
        if (a_object->gettype()==1){
            if (X){
                XTestFakeKeyEvent(display, keys[1], True, 0);
                XFlush(display);
                nsleep(key_press_time_rand(setts,X));
                XTestFakeKeyEvent(display, keys[1], False, 0);
                XFlush(display);
            }
            else{
                XTestFakeKeyEvent(display, keys[0], True, 0);
                XFlush(display);
                nsleep(key_press_time_rand(setts,X));
                XTestFakeKeyEvent(display, keys[0], False, 0);
                XFlush(display);
            }
        }

        if (a_object->gettype()==2){
            slider_on=true;
            if (X)
                XTestFakeKeyEvent(display, keys[1], True, CurrentTime);
            else
                XTestFakeKeyEvent(display, keys[0], True, CurrentTime);
            XFlush(display);
        }


        if (a_object->gettype()==3){
            XTestFakeKeyEvent(display, keys[1], True, 0);
            XFlush(display);
            nsleep(next_stamp-new_stamp-10000);
            XTestFakeKeyEvent(display, keys[1], False, 0);
            XFlush(display);
        }

        if (slider_on){
            check = a_object->calculate_slider_duration();
            int step=((b_object->gettime()-a_object->gettime())+1000)/check;

            step--;
            //if (debug_mode)     cout << "S: " << step << endl;
            check*=step;

            if (check>b_object->gettime()-a_object->gettime()-50000)
                nsleep(b_object->gettime()-a_object->gettime()-9658);

            else
                nsleep(check);

            slider_on=false;
            if (X)
                XTestFakeKeyEvent(display, keys[1], False, 0);
            else
                XTestFakeKeyEvent(display, keys[0], False, 0);
            XFlush(display);
        }

        if (X) last_is_x =true;

        if (num_lock_replay(i,setts,board_state,display)){
            breaked=true;
            break;
        }

        if (setts.debug_mode)
        {
            gettimeofday(&t4, NULL);
            t = ((t4.tv_sec * 1000000) + t4.tv_usec) - ((t3.tv_sec * 1000000) + t3.tv_usec);
            cout << "Press Z " << " -took- "  << t/1000 << "K" << endl;
            cout << "----------------------------------------------------" << endl;
        }

     }

     delete a_object;
     delete b_object;

     if (breaked){
         XTestFakeKeyEvent(display, keys[2], True, 0);
         XFlush(display);
         XTestFakeKeyEvent(display, keys[2], False, 136);
         XFlush(display);

         nsleep(200000);

         XTestFakeKeyEvent(display, keys[3], True, 0);
         XFlush(display);
         XTestFakeKeyEvent(display, keys[3], False, 917);
         XFlush(display);
         breaked =false;
     }

     XCloseDisplay(display);
     return true;
}

bool switch_to_osu(bool debug_modes)
{
    ostringstream ossCmd;
    long wid=0;
    char buffer[128];
    string result;

    ossCmd << "xdotool search --name \"osu!\"";
    FILE* pipe = popen(ossCmd.str().c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    }catch (...) {
         pclose(pipe);
         throw;
    }
    pclose(pipe);

    if (debug_modes) cout << "Cant find osu!" << result;
    try{
         wid = stoi(result);
    }catch (...){
         return false;
    }

    ossCmd.str("");
    ossCmd << "xdotool windowactivate " << wid;
    //if (debug_mode)
        cout << ossCmd.str().c_str() << endl;
    if (system(ossCmd.str().c_str())==-1)
    {
        cout << "IGN: Some command passing error" << endl;
        return false;
    }
    ossCmd.str("");
    return true;
}

void get_window_focus(Display** dsp, Window& root, bool debug_mode)
{
    nsleep(200000);
    if (debug_mode) cout << "Display Opened " << endl;
    *dsp = XOpenDisplay(NULL);
    root = DefaultRootWindow(*dsp);
}

void dummy_press(globals& setts, Display* display, KeyCode* keys){
    XTestFakeKeyEvent(display, keys[1], True, 40);
    XSync(display,false);
    XTestFakeKeyEvent(display, keys[1], False, 40);
    XSync(display,false);

    XTestFakeKeyEvent(display, keys[0], True, 40);
    XSync(display,false);
    XTestFakeKeyEvent(display, keys[0], False, 40);
    XSync(display,false);

    if (setts.debug_mode)   cout << "Dummy Press Done" << endl;
}

bool num_lock_replay(unsigned int i,globals& setts,XKeyboardState& board_state, Display* display){
    if (i%setts.n_lock_timer == 0 && i!=0){
        XGetKeyboardControl(display, &board_state);
        if (setts.debug_mode ) printf("led_mask=%lx\n", board_state.led_mask);
        if (setts.debug_mode)  printf("NumLock is %s\n", (board_state.led_mask & 2) ? "On" : "Off");
        if (board_state.led_mask==0)
            return true;
        else
            return false;

    }
    return false;
}

void set_key_codes(globals& setts, Display* display, KeyCode* key_array)
{
    key_array[0] = XKeysymToKeycode(display, XStringToKeysym("z"));
    key_array[1] = XKeysymToKeycode(display, XStringToKeysym("x"));
    key_array[2] = XKeysymToKeycode(display, XK_Num_Lock);
    key_array[3] = XKeysymToKeycode(display, XStringToKeysym(setts.osu_replay_key.c_str()));

}

void relocate_to_left_orange(long& new_stamp,long& next_stamp,globals& setts){
    new_stamp-=(setts.currentODtable[3]*1000);

}

