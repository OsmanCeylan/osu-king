#include "utility.h"
#include "main.h"

using namespace std;


bool should_x(globals& setts ,hit_object x ,hit_object y)
{
    if ((sqrt(((y.getx()-x.getx())*(y.getx()-x.getx())) +
    ((y.gety()-x.gety())*(y.gety()-x.gety())))*100)/100<=setts.x_break_distance)
    {
        if (setts.debug_mode)
            cout << "X In Distance" << endl;
        return true;
    }
    return false;
}

void nsleep(long us)
{
    static struct timespec wait;

    wait.tv_sec = us / (1000 * 1000);
    wait.tv_nsec = (us % (1000 * 1000)) * 1000;
    nanosleep(&wait, NULL);
}

void calculate_exact_photo_position(globals& setts, short& x, short& y)
{
    if (setts.mod_hr_on){
        y = ((setts.res1920_1080.osu_screen_h/2)-y) + (setts.res1920_1080.osu_screen_h/2);
    }
    float new_x = x*setts.res1920_1080.multipler + setts.res1920_1080.left_gap_x + 0.5;
    float new_y = y*setts.res1920_1080.multipler + setts.res1920_1080.up_gap_y + 0.5;
    x = (int)new_x;
    y = (int)new_y;

    if (setts.debug_mode){
        cout << "ui_hit_detector-> new X: " << x << " new Y: " << y << endl;
    }

}

void wait_for_ar(globals& setts, float AR,struct timeval* t1){

    int time;
    bool breaked=false;

    for (int i=0; i<setts.ARtable.size(); i++)
    {
        if (AR*10 == setts.ARtable[i][0]){
            time=setts.ARtable[i][1];
            breaked=true;
            break;
        }
    }

    if (!breaked && setts.debug_mode)
        cout << "Something go wrong when searhing for ARtable" << endl;
    if (breaked && setts.debug_mode)
        cout << "AR: " << AR << "-> " << time << endl;

    nsleep((time+setts.manual_ar_picking_time)*1000 + rand()%1000);
    gettimeofday(t1, NULL);
}

int key_press_time_rand(globals& setts, bool X){
    srand(time(NULL));
    if (!X){
        int a_rand=((rand()%4+3)*10000)+ ((rand()%2)*1000) + ((rand()%5)*87) +(rand()%13);

        if (setts.extracted_minimum_key_press_time>a_rand/1000){
            srand(time(NULL));
            a_rand=((rand()%4+3)*10000)+ ((rand()%11)*711) + ((rand()%11)*93) +(rand()%41);
        }

        if (setts.debug_mode)
            cout << "Returns: " << a_rand << endl;
        return a_rand;
    }

    else {
        int a_rand=((rand()%4+6)*10000)+ ((rand()%3)*1000) + ((rand()%7)*97) +(rand()%17);

        if (setts.extracted_minimum_key_press_time>a_rand/1000){
            srand(time(NULL));
            a_rand=((rand()%4+6)*10000)+ ((rand()%9)*1000) + ((rand()%13)*97) +(rand()%47);
        }

        if (setts.debug_mode)
            cout << "Returns: " << a_rand << endl;
        return a_rand;
    }

}

void make_error(long& new_stamp,long& next_stamp,globals& setts, short type, unsigned int& i){
    srand(time(NULL));
    int a_var,b_var;
    if (type==1){
        a_var = ((setts.currentODtable[3]-setts.currentODtable[1])*1000);
        new_stamp+=a_var;

        a_var=i%setts.circle_error_pattern_990.size();
        a_var=setts.circle_error_pattern_990[a_var];
        b_var=(setts.currentODtable[1]*2)*1000;
        a_var=b_var*a_var/100;
        new_stamp+=a_var + setts.post_error_fix+ rand()%1000;
        i++;

    }

    if (type==2){        
        a_var = ((setts.currentODtable[3]-setts.currentODtable[1])*1000);
        new_stamp+=a_var;

        a_var=i%setts.slider_error_pattern.size();
        a_var=setts.slider_error_pattern[a_var];
        b_var=(setts.currentODtable[1]*2)*1000;
        a_var=b_var*a_var/100;
        new_stamp+=a_var + setts.post_error_fix+ rand()%1000;


    }
}

void initializer_zero(vector<int>& error_hash){
    for (int i=0; i<error_hash.size(); i++){
        error_hash[i]=0;
    }
}

void clear_hash(vector<int>& error_hash){
    for (int i=0; i<error_hash.size(); i++){
        error_hash[i]=0;
    }
}


/*mb next time
 *
 * a_var=rand()%error_hash.size()+1;
        if (error_hash[a_var]==0){
            error_hash[a_var]++;

            a_var=(a_var*1000)+((rand()%10)*100)+rand()%97;
            new_stamp+=a_var;
        }

        else{
            b_var=0;
            while (error_hash[a_var]!=0){
                a_var=rand()%error_hash.size()+1;
                if (b_var>=error_hash.size()/2){
                    clear_hash(error_hash);
                    if (setts.debug_mode) cout << "Clear error hash" << endl;
                }
                b_var++;
            }

            a_var=(a_var*1000)+((rand()%10)*100)+rand()%97;
            new_stamp+=a_var;
        }*/

