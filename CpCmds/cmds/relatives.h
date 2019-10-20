#pragma once
#include <vector>
#include <maya/MFnDagNode.h>
#include "MayaObject.h"

namespace cmds {

	std::vector<MObject> ListParents(const MFnDagNode& mfn, MFn::Type node_type = MFn::kDagNode);
	std::vector<MObject> ListChildren(const MFnDagNode& mfn, MFn::Type node_type = MFn::kDagNode);
	std::vector<MObject> ListAnscestors(const MFnDagNode& mfn, MFn::Type node_type = MFn::kDagNode);
	std::vector<MObject> ListDescendents(const MFnDagNode& mfn, MFn::Type node_type = MFn::kDagNode);

	inline std::vector<MObject> ListParents(MObject node, MFn::Type node_type = MFn::kDagNode) {
		return std::move(ListParents(MFnDagNode(node), node_type));
	}
	inline std::vector<MObject> ListChildren(MObject node, MFn::Type node_type = MFn::kDagNode) {
		return std::move(ListChildren(MFnDagNode(node), node_type));
	}
	inline std::vector<MObject> ListAnscestors(MObject node, MFn::Type node_type = MFn::kDagNode) {
		return std::move(ListAnscestors(MFnDagNode(node), node_type));
	}
	inline std::vector<MObject> ListDescendents(MObject node, MFn::Type node_type = MFn::kDagNode) {
		return std::move(ListDescendents(MFnDagNode(node), node_type));
	}


}// namespace cmds

