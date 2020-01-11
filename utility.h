#ifndef UTILITY_H
#define UTILITY_H
#include <vector>
#include <cstdint>

#include "main.h"
#include "globals.h"

using namespace std;

float make_float(int );
void nsleep(long );
long float_to_long(float );
bool should_x(globals& ,hit_object ,hit_object );

void set_global_hash(int ,int );
void ImageFromDisplay2(std::vector<uint8_t>& , int& , int& , int& ,Display* display, Window& root, struct OD& ,int ,int );
void ImageFromDisplay3(std::vector<uint8_t>& , int& , int& , int& ,Display* display, Window& root, struct OD&);
int getdifferance(std::vector<uint8_t>& , std::vector<uint8_t>& ,struct OD& );
void calculate_exact_photo_position(globals& ,short& ,short& );
void wait_for_ar(globals& ,float ,struct timeval*);
int key_press_time_rand(globals& ,bool );
void make_error(long& ,long& ,globals& ,short ,unsigned int& );
void initializer_zero(vector<int>& );
void clear_hash(vector<int>& );

#endif // UTILITY_H
