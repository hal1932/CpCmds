#pragma once
#include <vector>
#include <maya/MFnDagNode.h>
#include "MayaObject.h"

namespace cmds {

	std::vector<MObject> ListNodeConnections(const MFnDependencyNode& mfn, bool source = true, bool destination = true, MFn::Type node_type = MFn::kDependencyNode);
	std::vector<MPlug> ListPlugConnections(const MFnDependencyNode& mfn, bool source = true, bool destination = true, MFn::Type node_type = MFn::kDependencyNode);

	inline std::vector<MObject> ListSourceNodes(const MFnDependencyNode& mfn, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListNodeConnections(mfn, true, false, node_type));
	}
	inline std::vector<MObject> ListDestinationNodes(const MFnDependencyNode& mfn, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListNodeConnections(mfn, false, true, node_type));
	}

	inline std::vector<MPlug> ListSourcePlugs(const MFnDependencyNode& mfn, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListPlugConnections(mfn, true, false, node_type));
	}
	inline std::vector<MPlug> ListDestinationPlugs(const MFnDependencyNode& mfn, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListPlugConnections(mfn, false, true, node_type));
	}

	inline std::vector<MObject> ListNodeConnections(MObject node, bool source = true, bool destination = true, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListNodeConnections(MFnDependencyNode(node), source, destination, node_type));
	}
	inline std::vector<MObject> ListSourceNodes(MObject node, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListNodeConnections(MFnDependencyNode(node), true, false, node_type));
	}
	inline std::vector<MObject> ListDestinationNodes(MObject node, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListNodeConnections(MFnDependencyNode(node), false, true, node_type));
	}

	inline std::vector<MPlug> ListPlugConnections(MObject node, bool source = true, bool destination = true, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListPlugConnections(MFnDependencyNode(node), source, destination, node_type));
	}
	inline std::vector<MPlug> ListSourcePlugs(MObject node, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListPlugConnections(MFnDependencyNode(node), true, false, node_type));
	}
	inline std::vector<MPlug> ListDestinationPlugs(MObject node, MFn::Type node_type = MFn::kDependencyNode) {
		return std::move(ListPlugConnections(MFnDependencyNode(node), false, true, node_type));
	}

}// namespace cmds

