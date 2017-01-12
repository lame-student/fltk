#include <stdio.h>
#include <math.h>
#include <string>
#include <utility>

#include "fltkopt.h"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Draw.H>
//vmALfmFb
class Fl_Draw_Box : public Fl_Double_Window{
	
	public: 
	float X,Y,R;
	int w,h;
	int dy;
	bool red;
	Fl_Draw_Box(int w, int h, const char* test) : Fl_Double_Window(w,h,test) 
	{
		this->w = w;
		this->h = h;
		X = w/2;
		Y = h/2;
		R = 20;
		dy=5;
		red = true;
	}

	virtual void draw() {
		Fl_Double_Window::draw();

		
		uchar  rgb[] = {255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0};
		fl_draw_image(rgb, 0, 0,2, 2, 3, 0);
		
		if (Y +dy < 0+R)
		{
			dy =-dy;
		}	

		if (Y +dy > h-R)
		{
			dy =-dy;
		}	
		Y+=dy;
		if (red) {
		fl_color(255,0,0);
		} else {
		fl_color(0,255,255);
		}

		//spring from 200, 10, to 200
		int x1 = 200, y1 = 10, x2 = 200, y2 = Y/2, count = 11;
		int xi = x1, yi = y1;
		for (int i = 0; i < count-1 ; i ++)
		{
			int sign;
			if (i % 2)
				sign = 1;
			else
				sign = -1;
			int x = x1 + (x2 - x1)*(i+1)/count;
			int y = y1 + (y2 - y1)*(i+1)/count;

			int x_tmp = x + ( (-1) * sign * (100)/count);
			int y_tmp = y + sign * (x2 - x1)/count;
			x = x_tmp;
			y = y_tmp;

			//fl_line(xi,yi,x + ( (-1) * sign * (yi - y)),y + sign * (xi - x) );
			fl_line(xi,yi,x ,y);
			xi = x;
			yi = y;
		}
		fl_line(xi,yi,x2 ,y2);
		
		fl_circle(X,Y,R);
	};

	virtual int handle(int ev)
	{
	  switch(ev) {
		case FL_KEYDOWN:
		  if (Fl::event_key() == 'x') {
			red = false;
			redraw();
			return 1;
		  } else {
			return 0;
		  }
		case FL_KEYUP:
		  if (Fl::event_key() == 'x') {
			red = true;
			redraw();
			return 1;
		  } else {
			return 0;
		  }
		default:
		  return Fl_Double_Window::handle(ev);
	  }
	}
	
};


void callback(void* winp)
{
Fl_Draw_Box * win=(Fl_Draw_Box *)winp;

win->redraw();

Fl::repeat_timeout(0.04,callback, win);
//Fl::repeat_timeout(1,callback, win);
}

class Pair {
public:
	Fl_Input* input;
	Fl_Button* button;
	
	Pair(Fl_Input* i, Fl_Button* b)
	{
		input = i;
		button = b;
	}
};


void button_callback(Fl_Widget* widget, void* data) {
	Pair* pair = (Pair *) data;
	Fl_Button* button = pair->button;
	Fl_Input* input = pair->input;
	button->label(input->value());
	
	printf(input->value());
	
}




/*int main(int argc, char * argv[]) 
{
	Fl_Draw_Box* window = new Fl_Draw_Box(600, 400, "test");

	Fl_Button* button = new Fl_Button (20,20, 100, 30, "PUSH ME");
	Fl_Button* button2 = new Fl_Button (20,60, 100, 30, 0);
	button2->label("Hi! Test!");
	Fl_Input* input = new Fl_Input (20,100, 100, 30, 0);
	button2->label(input->value());
	
	Pair * pair = new Pair(input, button2);
	button->callback(button_callback, pair); 
	
	window->show(argc, argv);
	Fl::add_timeout(1.0, callback, window);
	Fl::run();

	printf("Hello");
	return 0;
}
*/


void b_callback(Fl_Widget* b, void* data)
{
	Fl_Input* i = (Fl_Input*)data;
	i->value(b->label());
}
int main(int argc, char** argv)
{
	Fl_Window* f = new Fl_Window(100, 200, "CALC");
	Fl_Input* inp = new Fl_Input(10, 10, 60, 20, NULL);
	int n = 1;
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
		{
			char* c = new char[2];
			c[0] = '0' + n++;
			c[1] = '\0';
			Fl_Button *b = new Fl_Button (10 + j*30, 40 + i*30,20,20,c);
			b->callback(b_callback, (void*)inp);
		}
	f->show(argc, argv);
	return Fl::run();
}
