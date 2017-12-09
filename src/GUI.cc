#include "GUI.h"
#include <iostream>
#include <functional>

#define SINGLE 0

using namespace std;
using namespace std::placeholders;

GUI::GUI()
{
    mainWindow = new Fl_Window(430, 290, "Look at this glorious little window");

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

    saveOptionButton = new Fl_Check_Button(15, 125, 25, 25, "Save result as:" );

    saveFileNameInput = new Fl_Input(150, 125, 265, 25 ,"");

    // Seed type options

    seedTypeLabel = new Fl_Box(15, 160, 100, 25, "Starting seed:\n");
    seedTypeLabel->align(FL_ALIGN_INSIDE);

    randomPatchSeedButton = new Fl_Round_Button(15, 185, 25, 25, "Random patch");
    randomPatchSeedButton->callback(randomPatchSeedCallback, this);
    randomPatchSeedButton->value(1);

    wholeImageSeedButton = new Fl_Round_Button(15, 210, 25, 25, "Whole image");
    wholeImageSeedButton->callback(wholeImageSeedCallback, this);
    wholeImageSeedButton->value(0);

    // Seed placement options

    seedPlacementLabel = new Fl_Box(230, 160, 150, 25, "Place starting seed at:\n");
    seedPlacementLabel->align(FL_ALIGN_INSIDE);

    centerOptionButton = new Fl_Round_Button(230, 185, 25, 25, "Center");
    centerOptionButton->callback(centerOptionButtonCallback, this);
    centerOptionButton->value(1);

    cornerOptionButton = new Fl_Round_Button(230, 210, 25, 25, "Corner");
    cornerOptionButton->callback(cornerOptionButtonCallback, this);
    cornerOptionButton->value(0);

    /* Start Button */
    synthButton = new Fl_Return_Button(15, 250, 150, 25, "Synthesize");
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

void GUI::centerOptionButtonCallback(Fl_Widget* w, void* v)
{  ((GUI*)v)->cornerOptionButton->value(0);  }

void GUI::cornerOptionButtonCallback(Fl_Widget* w, void* v)
{  ((GUI*)v)->centerOptionButton->value(0);  }

void GUI::randomPatchSeedCallback(Fl_Widget* w, void* v)
{  ((GUI*)v)->wholeImageSeedButton->value(0);  }

void GUI::wholeImageSeedCallback(Fl_Widget* w, void* v)
{  ((GUI*)v)->randomPatchSeedButton->value(0);  }

char* GUI::run()
{
    mainWindow->show();
    char* file = fl_file_chooser("Texture sample", "*", "../assets/");
    Fl::run();
    return file;
}

bool GUI::centerSeed() { return centerOptionButton->value(); }
bool GUI::usePatchAsSeed() { return randomPatchSeedButton->value(); }
