#pragma once
#include "engine.hpp"

namespace controller {

class GlutEngine : public Engine {
public:
	GlutEngine();
	virtual ~GlutEngine();
	virtual void init(int argc, char** argv);
	virtual void run();
private:
	bool initialized = false;
};


}

