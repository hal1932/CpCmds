#pragma once
#include <vector>
#include "MayaObject.h"

namespace cmds {

	std::vector<MObject> ListNodes(MFn::Type node_type = MFn::kDependencyNode);
	std::vector<MObject> ListNodes(const MString& name, MFn::Type node_type = MFn::kDependencyNode);
	std::vector<MayaObject> ListSelectedObjects();
	std::vector<MObject> ListSelectedNodes(MFn::Type node_type = MFn::kDependencyNode);
	std::vector<Component> ListSelectedComponents();

}// namespace cmds

