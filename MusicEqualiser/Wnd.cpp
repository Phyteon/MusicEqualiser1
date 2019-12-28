#include "stdafx.h"
#include "Wnd.h"


void Wnd::MakeAppearance()
{
	this->window_instance.create(VideoMode(800, 800), "MusicEqualiser ver. 1.0.0");
}

void Wnd::BeginListeningForEvents()
{
	while (this->window_instance.isOpen())
	{
		Event test_event;
		while (window_instance.pollEvent(test_event))
		{
			switch (test_event.type)
			{
			case Event::Closed:
				window_instance.close();

				break;
			}
		}
	}
}

Wnd::Wnd()
{
}


Wnd::~Wnd()
{
}
