#include "GUI.h"
#include <iostream>
#include <functional>

#define SINGLE 0

using namespace std;
using namespace std::placeholders;

GUI::GUI()
{
    mainWindow = new Fl_Window(430, 275, "Look at this glorious little window");

    patchSizeSlider = new Fl_Value_Slider(15, 15, 400, 25, "Patch size");
    patchSizeSlider->type(FL_HOR_NICE_SLIDER);
    patchSizeSlider->bounds(3, 39);
    patchSizeSlider->value(3);
    patchSizeSlider->slider_size(0.15);
    patchSizeSlider->precision(0);

    resultSizeSlider = new Fl_Value_Slider(15, 75, 400, 25, "Result size");
    resultSizeSlider->type(FL_HOR_NICE_SLIDER);
    resultSizeSlider->bounds(128, 512);
    resultSizeSlider->value(128);
    resultSizeSlider->slider_size(0.15);
    resultSizeSlider->precision(0);

    saveOptionButton = new Fl_Check_Button(15, 125, 25, 25, "Save result" );

    saveFileNameInput = new Fl_Input(15, 175, 400, 25 ,"");

    /* Start Button */
    synthButton = new Fl_Return_Button(15, 225, 150, 25, "Synthesize");
    synthButton->callback(synthButtonCallback);
    //bind(GUI::synthButtonCallback, this, _1, _2)

    mainWindow->end();

}

GUI::~GUI()
{
    delete (mainWindow);
    delete (patchSizeSlider);
    delete (resultSizeSlider);
    delete (synthButton);
    delete (saveOptionButton);
    delete (saveFileNameInput);
}

void GUI::synthButtonCallback(Fl_Widget* w, void* v)
{
    cout << "in callback function\n";
    w->window()->hide();
}

char* GUI::run()
{
    mainWindow->show();
    char* file = fl_file_chooser("Texture sample", "*", "../assets/");
    Fl::run();
    return file;
}
