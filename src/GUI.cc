#include "GUI.h"

#define SINGLE 0

GUI::GUI(){
	mainWindow = new Fl_Window(300, 200, "Look at this glorious little window");

        patchSizeSlider = new Fl_Value_Slider(15, 15, 150, 25, "Patch size");
        patchSizeSlider->type(FL_HOR_NICE_SLIDER);
        patchSizeSlider->bounds(3, 39);
        patchSizeSlider->slider_size(0.15);
        patchSizeSlider->precision(0);

        fileChooser = new Fl_File_Chooser("../assets/", "*", SINGLE, "Texture Sample");

        mainWindow->end();
	
}

int GUI::run()
{
	mainWindow->show();
	return Fl::run();
}
