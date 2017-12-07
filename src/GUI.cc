#include "GUI.h"
#include <iostream>
#include <functional>

#define SINGLE 0

using namespace std;

GUI::GUI()
{
	mainWindow = new Fl_Window(180, 165, "Look at this glorious little window");

        patchSizeSlider = new Fl_Value_Slider(15, 15, 150, 25, "Patch size");
        patchSizeSlider->type(FL_HOR_NICE_SLIDER);
        patchSizeSlider->bounds(3, 39);
        patchSizeSlider->value(3);
        patchSizeSlider->slider_size(0.15);
        patchSizeSlider->precision(0);

        resultSizeSlider = new Fl_Value_Slider(15, 75, 150, 25, "Result size");
        resultSizeSlider->type(FL_HOR_NICE_SLIDER);
        resultSizeSlider->bounds(128, 512);
        resultSizeSlider->value(128);
        resultSizeSlider->slider_size(0.15);
        resultSizeSlider->precision(0);

        synthButton = new Fl_Return_Button(15, 125, 150, 25, "Do Nothing :(");
        //synthButton->callback( std::bind(synthButtonCallback, mainWindow) );

        mainWindow->end();
	
}

GUI::~GUI()
{
        delete (mainWindow);
        delete (patchSizeSlider);
        delete (resultSizeSlider);
        delete (synthButton);
}

// static void GUI::synthButtonCallback(Fl_Window& fw)
// {
//         fw->hide();
// }

char* GUI::run()
{
	mainWindow->show();
        char* file = fl_file_chooser("Texture sample", "*", "../assets/");
	Fl::run();
        return file;
}
