/*
 * gst_model.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: loganek
 */

/*
 * gst_pipeline_model.h
 *
 *  Created on: Jul 16, 2015
 *      Author: loganek
 */

#include "gst_pipeline_model.h"


void ElementModel::add_child(const std::shared_ptr<ElementModel> &child)
{
	children.push_back(child);
	child->set_parent(shared_from_this());
}

void ElementModel::add_pad(const std::shared_ptr<PadModel> &pad)
{
	if (get_pad(pad->get_name()))
		return;
	pads.push_back(pad);
	pad->set_parent(shared_from_this());
}

std::shared_ptr<ElementModel> ElementModel::get_root()
{
	static std::shared_ptr<ElementModel> root = std::make_shared<ElementModel>("", "", true);

	return root;
}

std::shared_ptr<PadModel> ElementModel::get_pad(const std::string &pad_name)
{
	auto it = std::find_if(pads.begin(), pads.end(), [pad_name](const std::shared_ptr<PadModel>& pad) {
		return pad->get_name() == pad_name;
	});

	return (it != pads.end()) ? *it : std::shared_ptr<PadModel>();
}

std::shared_ptr<ElementModel> ElementModel::get_child(const std::string &child_name)
{
	auto it = std::find_if(children.begin(), children.end(), [child_name](const std::shared_ptr<ElementModel>& element) {
		return element->get_name() == child_name;
	});

	return (it != children.end()) ? *it : std::shared_ptr<ElementModel>();
}

void ElementModel::add_property(const std::string &name, const std::shared_ptr<GValueBase>& gvalue)
{
	properties[name] = gvalue;
}

