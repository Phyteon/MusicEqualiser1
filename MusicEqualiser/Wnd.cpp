#include "stdafx.h"
#include "Wnd.h"


void Wnd::MakeAppearance()
{
	this->window_instance.create(VideoMode(800, 800), "MusicEqualiser ver. 1.0.0");
}

Wnd::Wnd()
{
}


Wnd::~Wnd()
{
}
