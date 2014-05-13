#pragma once
#include <string>
#include <chrono>
#include "window.hpp"

namespace view {

class DemoWindow : public Window {
public:
	DemoWindow(size_t width, size_t height, const std::string& name)
	: Window(width, height, name) {}
protected:
	virtual bool display();
private:
	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
};

}
