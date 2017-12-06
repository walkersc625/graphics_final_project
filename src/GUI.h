#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>

struct GUI {
	F1_Window* mainWindow;
	F1_Slider* patchSizeSlider;
	F1_Check_Button* centerCheckButton;
	F1_File_Chooser* fileChooser;
};

#endif