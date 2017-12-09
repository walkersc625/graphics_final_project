#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Box.H>

struct GUI {
 	Fl_Window* mainWindow;
   	Fl_Value_Slider* patchSizeSlider;
   	Fl_Value_Slider* resultSizeSlider;
   	Fl_Return_Button* synthButton;
   	Fl_Check_Button* saveOptionButton;
   	Fl_Input* saveFileNameInput;
        Fl_Box* seedPlacementLabel;
        Fl_Round_Button* centerOptionButton;
        Fl_Round_Button* cornerOptionButton;
        Fl_Box* seedTypeLabel;
        Fl_Round_Button* randomPatchSeedButton;
        Fl_Round_Button* wholeImageSeedButton;


 	GUI();
 	~GUI();
 	static void synthButtonCallback(Fl_Widget* w, void* v);
        static void centerOptionButtonCallback(Fl_Widget* w, void* v);
        static void cornerOptionButtonCallback(Fl_Widget* w, void* v);
        static void randomPatchSeedCallback(Fl_Widget* w, void* v);
        static void wholeImageSeedCallback(Fl_Widget* w, void* v);
 	char* run();

        bool centerSeed();
        bool usePatchAsSeed();
};

#endif
