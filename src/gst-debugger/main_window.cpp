/*
 * main_window.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: mkolny
 */

#include "main_window.h"
#include "sigc++lambdahack.h"

#include "controller/controller.h"

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: IMainView(cobject),
  builder(builder),
  dispatcher(std::make_shared<Glib::Dispatcher>()),
  log_module(std::make_shared<GstLogModule>(builder)),
  event_module(std::make_shared<GstEventModule>(builder)),
  query_module(std::make_shared<GstQueryModule>(builder)),
  message_module(std::make_shared<GstMessageModule>(builder)),
  buffer_module(std::make_shared<GstBufferModule>(builder)),
  properties_module(std::make_shared<GstPropertiesModule>(builder))
{
	graph_module = std::make_shared<GraphModule>(builder);

	builder->get_widget("connectionPropertiesMenuItem", connection_properties);
	connection_properties->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::connectionPropertiesMenuItem_activate_cb));

	builder->get_widget("remoteEnumTypesMenuitem", remote_enum_types);
	remote_enum_types->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::remoteEnumTypesMenuitem_activate_cb));

	builder->get_widget("connectMenuItem", connect_menu_item);
	connect_menu_item->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::connectMenuItem_activate_cb));

	builder->get_widget_derived("connectionPropertiesDialog", connection_properties_dialog);
	builder->get_widget("mainStatusbar", main_statusbar);

	builder->get_widget_derived("remoteEnumTypesDialog", enums_dialog);
	builder->get_widget("mainStatusbar", main_statusbar);

	connection_status_changed(false);

	signal_show().connect([this] {
		graph_module->update_model_();
	});

	signal_delete_event().connect([this](GdkEventAny*){
		graph_module->free_graph();
		return false;
	});
}

void MainWindow::set_controller(const std::shared_ptr<Controller> &controller)
{
	this->controller = controller;

	controller->on_connection_status_changed(sigc::mem_fun(*this, &MainWindow::connection_status_changed));

	log_module->set_controller(controller);
	event_module->set_controller(controller);
	query_module->set_controller(controller);
	message_module->set_controller(controller);
	buffer_module->set_controller(controller);
	graph_module->set_controller(controller);
	properties_module->set_controller(controller);

	enums_dialog->set_controller(controller);
	enums_dialog->set_transient_for(*this);

	connection_properties_dialog->set_transient_for(*this);
}

void MainWindow::connectionPropertiesMenuItem_activate_cb()
{
	connection_properties_dialog->show();
}

void MainWindow::connectMenuItem_activate_cb()
{
	if (controller->is_connected())
		controller->disconnect();
	else
		controller->connect(
			connection_properties_dialog->get_ip_address(),
			connection_properties_dialog->get_port());
}

void MainWindow::remoteEnumTypesMenuitem_activate_cb()
{
	enums_dialog->show();
}

void MainWindow::connection_status_changed(bool connected)
{
	auto id = main_statusbar->get_context_id("connection-status");
	if (connected)
	{
		main_statusbar->push("Connected", id);
		((Gtk::Label*)connect_menu_item->get_child())->set_text("Disconnect");
	}
	else
	{
		main_statusbar->push("Disconnected", id);
		((Gtk::Label*)connect_menu_item->get_child())->set_text("Connect");
	}
}

