#include "GUI.h"

GUI::GUI(){
	mainWindow = new Fl_Window(300, 200, "Look at this glorious little window");
	
}

int GUI::run()
{
	mainWindow->show();
	return Fl::run();
}
