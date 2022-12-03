#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d,w,width,
            height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

    cmap=DefaultColormap(d,DefaultScreen(d));
    for(int i=0; i < 10; ++i) {
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }

    XSetForeground(d,gc,colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);

    // Make sure we don't race against the Window being shown
    XEvent ev;
    while(1) {
        XNextEvent(d, &ev);
        if(ev.type == Expose) break;
    }
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

// void Xwindow::drawString(int x, int y, string msg) {
//     XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
// }
void Xwindow::drawString(int x, int y, std::string msg, int colour) {
  XFontStruct * f = XLoadQueryFont(d, "6x13");
	
	printMessage(x, y, msg, colour, *f); 

	delete f;
}

void Xwindow::fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour) {
    XSetForeground(d, gc, colours[colour]);
	XFillArc(d, w, gc, x-width/2, y-height/2, width, height, angle1 * 64, angle2 * 64);
	XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawCircle(int x, int y, int di, int colour) {
	fillArc(x, y, di, di, 0, 360, colour);
}

void Xwindow::printMessage(int x, int y, const string& msg, int colour, XFontStruct& f){
    XSetForeground(d, gc, colours[colour]);
    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f.fid;
    XDrawText(d, w, gc, x, y, &ti, 1);
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);
}

void Xwindow::drawBiggerString(int x, int y, string msg, int colour) {
  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
    ostringstream name;
    name << "-*-helvetica-bold-r-*-*-*-240-" << 100 << "-" << 90 << "-*-*-*-*";

    XFontStruct * f = XLoadQueryFont(d, name.str().c_str());

    if (f == nullptr) {
        f = XLoadQueryFont(d, "6x13");
    }
    printMessage(x, y, msg, colour, *f);
    delete f;
}