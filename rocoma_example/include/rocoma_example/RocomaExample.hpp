#pragma once

// rocomaex model
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

// rocoma
#include "rocoma/ControllerManager.hpp"

// Boost
#include <boost/thread.hpp>

// Stl
#include <memory>

namespace rocoma_example {

class RocomaExample{
public:
	RocomaExample(const double timestep);
	virtual ~RocomaExample();

	virtual void init();
	virtual void cleanup();
	virtual bool update();

private:
	rocoma::ControllerManager controllerManager_;
	std::shared_ptr<rocomaex_model::State> state_;
	std::shared_ptr<rocomaex_model::Command> command_;
	std::shared_ptr<boost::shared_mutex> mutexState_;
	std::shared_ptr<boost::shared_mutex> mutexCommand_;
};

}
