#pragma once
#include <string>
#include "window.hpp"

namespace view {

class DemoWindow : public Window {
public:
	DemoWindow(size_t width, size_t height, const std::string& name)
	: Window(width, height, name) {}
protected:
	virtual bool display();
};

}
