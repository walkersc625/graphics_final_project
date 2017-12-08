#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
// #include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
// #include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_File_Chooser.H>

struct GUI {
 	Fl_Window* mainWindow;
   	Fl_Value_Slider* patchSizeSlider;
   	Fl_Value_Slider* resultSizeSlider;
   	Fl_Return_Button* synthButton;
    //Fl_Check_Button* centerCheckButton;

 	GUI();
 	~GUI();
 	static void synthButtonCallback(Fl_Widget* w, void* v);
 	char* run();
};

#endif
