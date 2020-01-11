#ifndef KEY_EVENTS_H
#define KEY_EVENTS_H

#include "main.h"
#include "hit_object.h"
#include "utility.h"
#include "globals.h"
#include "profiles.h"

XKeyEvent createKeyEvent(Display*, Window& ,Window&, bool ,
                           int , int );
bool mouse_event(globals& ,struct timeval* );
int GrabKey(Display* ,Window ,int );
bool keyevent(globals& ,char ,struct timeval* );
void set_mouse(hit_object* ,hit_object* );
bool listen_for_refresh();
bool touch_start(profiles& , struct timeval* );
bool ui_detect_first_object(globals& ,Display* , Window& ,short ,short , bool debug_mode);
void ImageFromDisplay(std::vector<uint8_t>& , int& , int& , int& ,Display* , Window& ,short ,short );

void just_shit();

#endif // KEY_EVENTS_H
