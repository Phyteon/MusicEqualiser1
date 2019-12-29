#include "stdafx.h"
#include "Wnd.h"


void Wnd::ReadUserInput(Uint8 ptr, Event& event)
{
	// filter ASCII characters, if backspace pressed, delete last letter from string
	// If string is empty, backspace does nothing
}

void Wnd::MakeAppearance()
{
	if (!this->window_instance.isOpen())
	{
		this->window_instance.create(VideoMode(800, 800), "MusicEqualiser ver. 1.0.0");
		this->window_instance.setVerticalSyncEnabled(true);
	}
		
}

void Wnd::BeginListeningForEvents()
{
	while (this->window_instance.isOpen())
	{
		Event event;
		while (window_instance.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window_instance.close();
			case Event::TextEntered:
				

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
