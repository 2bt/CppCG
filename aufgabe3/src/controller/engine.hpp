#pragma once
namespace controller {

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}
	virtual void init(int argc, char** argv) = 0;
	virtual void run() = 0;
};


}
