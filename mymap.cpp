#include "mymap.h"
#include "hit_object.h"

mymap::mymap(string pass_name, bool debug_mode){
    open_error=false;
    map_file_name=pass_name;
    osu_map_file.open(map_file_name);
    if (!(osu_map_file.is_open()))  open_error=true;
    else{
        if (debug_mode)
            cout << "mymap creature complate" << endl;
    }

}

bool mymap::get_file_error(){
    if (open_error) cout << "Couldnt open map" << endl;
    return open_error;
}

bool mymap::fill_osu_file(bool debug_mode)
{
    string *line = new string;
    getline(osu_map_file, *line);

    size_t found = line->find("osu file format");
    if (found==std::string::npos){
         if (debug_mode){
             cout << line->c_str() <<  endl;
             cout << "osu file format" << endl;
             cout << "This might not be osu file <<@main, open_osu_file" << endl;
          }
        return false;
    }

    object_count=0;

    while ( !osu_map_file.eof()){
      osu_map_file >> *line;

      if (line->compare("[General]")==0){
          while (true){
              osu_map_file >> *line;
              if (line->compare("Countdown:")==0) break;
          }
          osu_map_file >> *line;
          countdown=stoi(*line);
      }

      else if (line->compare("[Metadata]")==0){
          getline(osu_map_file,*line);
          getline(osu_map_file,*line);
          title.insert(0,*line,sizeof("title"),(*line->end()-sizeof("title")));
          getline(osu_map_file,*line);
          artist.insert(0,*line,sizeof("artist"),(*line->end()-sizeof("artist")));
          getline(osu_map_file,*line);
          creator.insert(0,*line,sizeof("creator"),(*line->end()-sizeof("creator")));
          getline(osu_map_file,*line);
          version.insert(0,*line,sizeof("version"),(*line->end()-sizeof("version")));
      }

      else if (line->compare("[Difficulty]")==0){
          getline(osu_map_file,*line);
          getline(osu_map_file,*line);
          HP=stof(line->substr(sizeof("hpdrainrate"),(*line->end()-sizeof("hpdrainrate"))));
          getline(osu_map_file,*line);
          CS=stof(line->substr(sizeof("circlesize"),(*line->end()-sizeof("circlesize"))));
          getline(osu_map_file,*line);
          OD=stof(line->substr(sizeof("overalldifficulty"),(*line->end()-sizeof("overalldifficulty"))));
          getline(osu_map_file,*line);
          AR=stof(line->substr(sizeof("approachrate"),(*line->end()-sizeof("approachrate"))));
          getline(osu_map_file,*line);
          slider_multipler=stof(line->substr(sizeof("slidermultiplier"),(*line->end()-sizeof("slidermultiplier"))));
          getline(osu_map_file,*line);
          slider_tick_rate=stof(line->substr(sizeof("slidertickrate"),(*line->end()-sizeof("slidertickrate"))));

      }

    }
    delete line;

    printmapprops(debug_mode);
    return true;

}

bool mymap::dump_file_to_ram(bool debug_mode){
    string *line = new string;
    bool breaked=false;

    osu_map_file.clear();
    osu_map_file.seekg(0);

    while ( !osu_map_file.eof()){
        osu_map_file >> *line;
        if (line->compare("[HitObjects]")==0){
            breaked=true;
            break;
        }
    }

    if (!breaked && debug_mode){
        cout << "Missing hitobject <<@main, dump_file" << endl;
        return false;
    }


    while (getline(osu_map_file, *line)){
        object_count++;
    }

    osu_map_file.clear();
    osu_map_file.seekg(0);

    dumped_file.resize(object_count);

    breaked=false;
    while ( !osu_map_file.eof()){
        osu_map_file >> *line;
        if (line->compare("[HitObjects]")==0){
            breaked=true;
            break;
        }
    }

    if (!breaked && debug_mode){
        cout << "Missing hitobject <<@main, dump_file-2" << endl;
        return false;
    }


    getline(osu_map_file,*line);
    for (int i=0; i<object_count; i++){
        getline(osu_map_file,*line);
        dumped_file[i]=*line;
    }

    dumped_file[object_count-1]="E";    //End of Objects
    osu_map_file.clear();
    osu_map_file.seekg(0);

    printdumps(debug_mode);

    delete line;
    return true;
}

bool mymap::extract_timings(bool debug_mode)
{
    string* line = new string;
    string* comma = new string(",");
    string* int_str= new string;

    bool breaked=false;

    while ( !osu_map_file.eof()){
        osu_map_file >> *line;
        if (line->compare("[TimingPoints]")==0){
            breaked=true;
            break;
        }
    }
    getline(osu_map_file, *line);

    if (!breaked && debug_mode){
        cout << "Missing timing <<@main, extract_timins" << endl;
        return false;
    }


    times_count=0;
    while (getline(osu_map_file, *line)) {
        times_count++;
        if (line->size()==1){
            times_count-=2;
            break;
        }
    }

    osu_map_file.clear();
    osu_map_file.seekg(0);

    times.resize(times_count, std::vector<int>(2, 0));

    while ( !osu_map_file.eof()){
        osu_map_file >> *line;
        if (line->compare("[TimingPoints]")==0){
            break;
        }
    }
    getline(osu_map_file, *line);

    size_t back_found, found;
    for (int i=0; i<times_count; i++){
        back_found=0;
        getline(osu_map_file, *line);

        found = line->find_first_of(*comma);
        int_str->insert(0,*line,back_found,found-back_found);
        times[i][0] = stoi(*int_str);
        *int_str="";

        back_found = found+1;
        found = line->find(*comma,back_found);
        int_str->insert(0,*line,back_found,found-back_found);
        times[i][1] = stoi(*int_str);
        *int_str="";
        int_str->clear();
    }


    osu_map_file.clear();
    osu_map_file.seekg(0);

    printtimings(debug_mode);
    delete comma;
    delete line;
    delete int_str;
    return true;

}

bool mymap::apply_map_modes(globals& setts,bool debug_mode){

    if (OD<6){
        cout << "Im not play in low OD so wont allow bc its noticable" << endl;
        return false;
    }

    cout << "AR: " << AR << " OD: " << OD << endl;

    if (setts.mod_hr_on){
        if      (OD*10==60)       OD=8.4;
        else if (OD*10==65)       OD=9.1;
        else if (OD*10==70)       OD=9.8;
        else                      OD=10.0;

        if      (AR*10==60)       AR=8.4;
        else if (AR*10==70)       AR=9.8;
        else                      AR=10.0;

    }

    bool breaked=false;
    int i=0;
    for (i=0; i<setts.ODtable.size();i++){
        if (OD*10==(float)setts.ODtable[i][0]){
            breaked=true;
            break;
        }
    }
    setts.currentODtable.resize(4);
    setts.currentODtable[0]=setts.ODtable[i][0];
    setts.currentODtable[1]=setts.ODtable[i][1];
    setts.currentODtable[2]=setts.ODtable[i][2];
    setts.currentODtable[3]=setts.ODtable[i][3];

    if (!breaked && setts.debug_mode){
        cout << "Cant set current OD. Needs to check" << endl;
    }

    if (setts.debug_mode){
        cout << "Applied Modes" << endl;
        cout << "-------------------" << endl;
        if (setts.mod_hr_on)    cout << "HR ->" << "AR: " << AR << " OD:" << OD;
        if (setts.mod_hd_on)    cout << " HD" ;
        cout << endl;
        cout << setts.currentODtable[0] << "-" << setts.currentODtable[1] << "-" << setts.currentODtable[2] << "-" << setts.currentODtable[3] << endl;
    }

    return true;
}

void mymap::printtimings(bool debug_mode){
    if (debug_mode){
        cout << "Times exctracted" << endl;
        cout << "--------------------------------------" << endl ;
        for (int i=0; i<times.size(); i++){
            cout << i << ". " << times[i][0] << " - " << times[i][1] << endl;
        }
        cout << "Timing count: " << times_count << endl << endl;
    }
}

void mymap::printmapprops(bool debug_mode){
    if (debug_mode){
        cout << "Readed Map Props" << endl;
        cout << "--------------------------------" << endl;
        short countdown;
        cout << "Tittle: " << title << endl;
        cout << "Creator: "<< creator << endl;
        cout << "Version: "<< version << endl;
        cout << "Artist: " << artist << endl;

        cout << "HP: " << HP << " - CS: " << CS << " - OD: " << OD << " - AR: " << AR << "- SM: " << slider_multipler << "- STR: " << slider_tick_rate << endl;
    }

}

void mymap::printdumps(bool debug_mode){
    if (debug_mode){
        cout << "Dumping Done" << endl;
        cout << "-----------------------------------" << endl;
        for (int i=0; i<object_count; i++){
            cout << i << ". " << dumped_file[i].c_str() << endl;
        }
        cout << "Objects Count: " << object_count << endl;
    }
}

void mymap::close_file(){
    osu_map_file.close();
}

int mymap::least_press_time_gap(globals& setts){

    hit_object* a_object= new hit_object;
    hit_object* b_object= new hit_object;
    long new_stamp,next_stamp, least;

    a_object->fill(dumped_file[0]);
    b_object->fill(dumped_file[1]);

    new_stamp = a_object->gettime();
    next_stamp = b_object->gettime();
    least=next_stamp-new_stamp;

    for (unsigned int i=2; i<dumped_file.size()-1; i++)
    {
        a_object->fill(dumped_file[i]);
        b_object->fill(dumped_file[i+1]);

        new_stamp = a_object->gettime();
        next_stamp = b_object->gettime();

        if (next_stamp-new_stamp<least)
            least=next_stamp-new_stamp;
    }

    if (setts.debug_mode)
        cout << "Least key press-release gap shuld be minimum: " << least/1000 << "ms." << endl;
    setts.extracted_minimum_key_press_time=least/1000;

    delete a_object;
    delete b_object;
}
