#include "key_events.h"

using namespace std;
using namespace cv;

XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press,
                           int keycode, int modifiers){
   XKeyEvent event;
   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}

bool mouse_event(globals& setts, struct timeval* t1){
  int fd;
  struct input_event ie;
  Display *dpy;
  Window root, child;
  int rootX, rootY, winX, winY;
  unsigned int mask;

  dpy = XOpenDisplay(NULL);
  XQueryPointer(dpy,DefaultRootWindow(dpy),&root,&child,
              &rootX,&rootY,&winX,&winY,&mask);

  if((fd = open(setts.event_id.c_str(), O_RDONLY)) == -1) {
    perror("opening device");
    exit(EXIT_FAILURE);
  }

  while(read(fd, &ie, sizeof(struct input_event))) {
   /*if (ie.type == 2) {
        if (ie.code == 0) { rootX += ie.value; }
        else if (ie.code == 1) { rootY += ie.value; }
        printf("time%ld.%06ld\tx %d\ty %d\n",
            ie.time.tv_sec, ie.time.tv_usec, rootX, rootY);
    }*/

    if (ie.type == 1) {
        if (ie.code == 272 ){
            printf("Mouse button");

            if (ie.value == 0){
                 printf("released!!\n");
                 return true;
            }

            if (ie.value == 1){
                gettimeofday(t1, NULL);
                return true;
            }
        }
    }

    /*else {
        printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
            ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
    }*/
  }
  return false;
}

bool keyevent(globals& setts, char start, struct timeval* t1){
    int fd;
    struct input_event ie;

    start=45;
    if((fd = open(setts.event_id.c_str(), O_RDONLY)) == -1) {
      perror("opening device");
      exit(EXIT_FAILURE);
    }

    while(read(fd, &ie, sizeof(struct input_event))) {
      if (ie.type == 1) {
            if (ie.code==start && ie.value==1){                             //     0=release,
                 gettimeofday(t1, NULL);
                 return true;
            }
      }
    }

    return false;
}

bool ui_detect_first_object(globals& setts, Display* display, Window& root, short x, short y, bool debug_mode)
{

      int pxcounter=0;
      int pxtotal=0;
      int single_color_avarage;

      short this_x=x;
      short this_y=y;

      calculate_exact_photo_position(setts, this_x, this_y);
      int Width = setts.res1920_1080.hit_box_of_note;
      int Height =setts.res1920_1080.hit_box_of_note;
      int Bpp = 24;
      std::vector<std::uint8_t> Pixels;

      while (true)
      {
          pxcounter=0;
          pxtotal=0;

          ImageFromDisplay(Pixels, Width, Height, Bpp, display, root,this_x,this_y);

          if (Width && Height)
          {
               if (setts.debug_mode){
                   cout << "Take a sshot success: " << Pixels.size()/4 << "pixel "<< endl;
               }
               Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]);

               for (int i=0; i<Pixels.size()/4;i++)
               {
                   pxtotal+=Pixels[pxcounter];
                   pxcounter+=4;
               }
               single_color_avarage = pxtotal/(Pixels.size()/4) ;
               if (setts.debug_mode) cout << "R color avarage: " << single_color_avarage << endl;

               if (single_color_avarage>setts.ui_avarage_color_breaker)
               {
                   break;
               }

               if (setts.draw_ui_sshot)
               {
                   namedWindow("WindowTitle", WINDOW_AUTOSIZE);
                   imshow("Display window", img);

                   waitKey(0);
                   break;
               }

          }

          else{
              if (setts.debug_mode){
                  cout << "Take a sshot failed" << endl;
              }
              break;
          }
          nsleep(setts.ui_gap_beetwen_sshots);
      }

}

void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel, Display* display, Window& root,short x, short y)
{

    XImage* img = XGetImage(display, root, x-(Width/2), y-(Height/2) , Width, Height, AllPlanes, ZPixmap);
    BitsPerPixel = img->bits_per_pixel;
    Pixels.resize(Width * Height * 4);
    memcpy(&Pixels[0], img->data, Pixels.size());
    XDestroyImage(img);
}
