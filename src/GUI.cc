#include "GUI.h"
#include <iostream>
#include <functional>

#define SINGLE 0

using namespace std;
using namespace std::placeholders;

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

    synthButton = new Fl_Return_Button(15, 125, 150, 25, "Synthesize");
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
