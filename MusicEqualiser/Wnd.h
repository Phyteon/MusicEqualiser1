#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Wnd
{
protected:
	RenderWindow window_instance;
public:
	void MakeAppearance();
	Wnd();
	~Wnd();
};

