#include "hit_object.h"
#include "main.h"

using namespace std;

bool hit_object::fill(string line){

    if (line[0]=='E'){          //Last
        x=0;
        y=0;
        t_stamp=1000000000;
        hitsound=0;
        type=2;
        cout << "Last Object" << endl;
        return false;
    }

    string comma=",";
    size_t found =0;
    size_t back_found =0;

    found = line.find(comma);

    string* int_str= new string;
    int_str->insert(0,line,back_found,found-back_found);
    x = stoi(*int_str);

    int_str->clear();
    back_found = found+1;

    found = line.find(comma,back_found);
    int_str->insert(0,line,back_found,found-back_found);
    y = stoi(*int_str);

    int_str->clear();
    back_found = found+1;

    found = line.find(comma, back_found);
    int_str->insert(0,line,back_found,found-back_found);
    t_stamp = stoi(*int_str);
    t_stamp*=1000;

    int_str->clear();
    back_found = found+1;

    found = line.find(comma, back_found);
    int_str->insert(0,line,back_found,found-back_found);
    type_str = stoi(*int_str);


    int_str->clear();
    back_found = found+1;

    found = line.find(comma, back_found);
    if (found!=std::string::npos){
        int_str->insert(0,line,back_found,found-back_found);
        hitsound = stoi(*int_str);
    }

    else{
        hitsound = 55;
    }

    if (type_str%2==1){
        type=1;
        /*cout << "X: " << x << " Y: " << y << " Time: " << t_stamp/1000 << " Type: "<< type << " Hs: "<< hitsound << endl;*/
    }

    if (type_str%2==0){
        type = 2;
        back_found=0;
        int i=0;

        found = line.find("|", back_found);
        if (found==std::string::npos){
            type=3;
        }

        else{
            slider_type = line[found-1];
            found = line.find(comma,found+1);
            back_found=found+1;
            found = line.find(comma,back_found);

            int_str->clear();
            int_str->insert(0,line,back_found,found-back_found);

            //if (debug_mode)  cout << int_str->c_str() << endl;
            slider_recursive = stoi(*int_str);

            back_found = found+1;

            char bppm[3];
            while (i<3){
                if (line[back_found+i]!= '.'  &&  line[back_found+i]!= ','){
                    bppm[i] = line[back_found+i];
                    i++;
                }
                else
                    break;
            }
            bppm[i]='\0';
            slider_bpm = stoi(bppm);

            /*cout << "X: " << x << " Y: " << y << " Time: " << t_stamp/1000 << " Type: "<< type << " Hs: "<< hitsound << " ST: " << slider_type << " Rec: " << slider_recursive << " Pxlen: " << slider_bpm << endl;*/
        }
    }

    delete int_str;
    return true;
}

bool hit_object::fill_vector(mymap& this_map){
    times = this_map.times;
    return true;
}

float hit_object::calculate_slider_duration(){
    unsigned int i=0;
    for (i=0; i<times.size(); i++){
        if (times[i][0]>(t_stamp/1000) ){
            break;
        }
    }

    //if (debug_mode) cout <<"Breaked timing: "  << i  << "-" << times[i][0] << " - " << t_stamp << endl;
    float carpim;
    float bd;

    int j=0;
    if (i==0 && times[i][0]>(t_stamp/1000))
    {
        carpim = (60*1000);
        carpim /= times[i][1];
        bd = 15000/carpim;
        return bd*1000;
    }

    if (times[i-1][1] < 0 )
    {
        for (j=i-2; j>=0; j--){
            if (times[j][1]>0){
                carpim = (60*1000);
                carpim/=times[j][1];
                bd = 15000/carpim;
                /*if (debug_mode){
                    cout << "C: " << times[j][1] << " - " << carpim << " - "  << bd*1000 << " - " << slider_bpm << endl;}*/
                return bd*1000;
            }
        }
    }

    else{
        carpim = (60*1000);
        carpim /= times[i-1][1];
        bd = 15000/carpim;
        /*if (debug_mode) cout << "C: " << times[i-1][1] << " - " << carpim << " - " << bd*1000 << " - " << slider_bpm << endl;*/

        return bd*1000;
    }
    return 0;
}
