// generated by Fast Light User Interface Designer (fluid) version 1.0200

#include "HelloWorld.h"

Fl_Double_Window* HelloWorld::make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(132, 100);
    w = o;
    //o->user_data((void*)(this));
    new Fl_Box(25, 25, 25, 25, "Hello World!");
    o->end();
  }
  return w;
}
