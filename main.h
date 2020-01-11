#ifndef MAIN_H
#define MAIN_H

#include <opencv4/opencv2/highgui.hpp> //leave when needed
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include <math.h>

#include <X11/X.h>
#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>

#include "mymap.h"
#include "hit_object.h"
#include "key_events.h"
#include "globals.h"
#include "utility.h"
#include "profiles.h"
#include "file_operations.h"

#define slider_error_frec 5
#define n_sleep_multipler 1000
#define true_strike_chance 10
#define wait_step 1024

bool emulate(globals& ,mymap& ,Display* , Window& );
bool switch_to_osu(bool );
int get_stamp(hit_object* ,mymap& ,short ,bool& );
void get_window_focus(Display** , Window& ,bool );
void set_key_codes(globals& ,Display*, KeyCode* );
void set_stamp(int ,int& ,int );
void set_new_stamp(int& ,bool ,int& ,int& );
void interpolasion(int& ,int& ,int& ,struct timeval* ,struct timeval* );
void dummy_press(globals& , Display* , KeyCode* );
bool num_lock_replay(unsigned int ,globals& ,XKeyboardState& , Display* );
void relocate_to_left_orange(long& ,long& ,globals& );
#endif // MAIN_H
