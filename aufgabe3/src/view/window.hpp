#pragma once
#include <string>
namespace view {

class Window {
public:
	Window(size_t width, size_t height, const std::string& name);
	virtual ~Window();
	unsigned int width() const { return _width; }
	unsigned int height() const { return _height; }
	// request window redisplay
	void invalidate();
protected:
	virtual bool display();

	virtual void reshape();
	virtual void keyboard(unsigned char key, int x, int y);
private:
	// make sure this Window is the current GLUT Window
	void ensureCurrent() const;

	static void glutDisplay();
	static void glutReshape(int width, int height);
	static void glutKeyboard(unsigned char key, int x, int y);

	std::string _name;
	size_t _width;
	size_t _height;
	int _glut_win_id;
};

}
