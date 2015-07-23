/*
 * controller.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: loganek
 */

#include "controller.h"

#include <gtkmm.h>

#include <boost/algorithm/string/split.hpp>

Controller::Controller(IMainView *view)
 : view(view)
{
	client->signal_frame_received.connect(sigc::mem_fun(*this, &Controller::process_frame));
}

int Controller::run(int &argc, char **&argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "gst.debugger.com");
	view->set_controller(shared_from_this());
	return app->run(*view);
}

void Controller::send_command(const Command& cmd)
{
	client->send_command(cmd);
}

void Controller::process_frame(const GstreamerInfo &info)
{
	switch (info.info_type())
	{
	case GstreamerInfo_InfoType_TOPOLOGY:
		process(info.topology());
		view->set_current_model(current_model);
		break;
	case GstreamerInfo_InfoType_DEBUG_CATEGORIES:
		process_debug_categories(info.debug_categories());
		break;
	default:
		break;
	}
}

void Controller::model_up()
{
	if (current_model == ElementModel::get_root())
		return;

	current_model = std::static_pointer_cast<ElementModel>(current_model->get_parent());
	view->set_current_model(current_model);
}

void Controller::model_down(const std::string &name)
{
	auto tmp = current_model->get_child(name);

	if (tmp && tmp->is_bin())
	{
		current_model = tmp;
		view->set_current_model(current_model);
	}
}

void Controller::process_debug_categories(const DebugCategoryList& debug_categories)
{
	std::vector<std::string> categories;
	boost::split(categories, debug_categories.list(), [](char c) { return c == ';'; });
	categories.erase(std::remove_if(categories.begin(), categories.end(),
			[](const std::string &s){return s.empty();}), categories.end());

	view->set_debug_categories(categories);
}
