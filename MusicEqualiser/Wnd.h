#pragma once
#include "SFML/Graphics.hpp"
#include "WavFile.h"
using namespace sf;
class Wnd
{
protected:
	RenderWindow window_instance;
	Mouse mouse;
	Text input_file; // Need to assign indices to in/out in order to distinguish between two textboxes
	Text output_file; // Remember about defining font and size !!!
	String user_input;
	void ReadUserInput(Uint8, Event&);
public:
	void MakeAppearance();
	void BeginListeningForEvents();
	Wnd();
	~Wnd();
};

