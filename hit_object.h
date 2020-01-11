#ifndef HIT_OBJECT_H
#define HIT_OBJECT_H

#include "mymap.h"

using namespace std;

class hit_object{
private:
    short x;
    short y;
    int t_stamp;
    int type_str;
    short type;                         //1=Circle  //2=Slider  //3=Spinner
    int hitsound;
    int spinner_end_time;
    char slider_type;
    int slider_bpm;
    int slider_recursive;

    short combo1;
    short combo2;

    int slide_last;
    float map_slider_diff;
    int first_sd;

public:
    vector<vector<int> > times;
    short getx(){return x;}
    short gety(){return y;}
    int gettime(){return t_stamp;}
    short gettype(){return type;}
    void setsliderdiff(float k){map_slider_diff = k;}
    int getsliderbpm(){return slider_bpm;}
    int getrec(){return slider_recursive;}
    bool fill(string );
    bool fill_vector(mymap& );

    float calculate_slider_duration();
};

#endif // HIT_OBJECT_H
