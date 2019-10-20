#include "connections.h"
#include <functional>
#include <maya/MGlobal.h>
#include <maya/MPlugArray.h>

using namespace cmds;

namespace {
	void EnumerateConnections_(const MFnDependencyNode& mfn, bool source, bool destination, MFn::Type node_type, std::function<void(MPlug)> callback) {
		MPlugArray connections;
		auto status = mfn.getConnections(connections);
		if (status.error()) {
			MGlobal::displayError(status.errorString());
			return;
		}

		for (uint i = 0; i < connections.length(); ++i) {
			auto& plug = connections[i];
			if (source && plug.isDestination()) {
				callback(plug.source());
			} else if (destination && plug.isSource()) {
				MPlugArray destinations;
				plug.destinations(destinations);
				for (uint j = 0; j < destinations.length(); ++j) {
					callback(destinations[j]);
				}
			}
		}
	}
}

std::vector<MObject> cmds::ListNodeConnections(const MFnDependencyNode& mfn, bool source, bool destination, MFn::Type node_type) {
	std::vector<MObject> result;
	EnumerateConnections_(mfn, source, destination, node_type, [&result](auto mplug) { result.push_back(mplug.node()); });
	return std::move(result);
}

std::vector<MPlug> cmds::ListPlugConnections(const MFnDependencyNode& mfn, bool source, bool destination, MFn::Type node_type) {
	std::vector<MPlug> result;
	EnumerateConnections_(mfn, source, destination, node_type, [&result](auto mplug) { result.push_back(mplug); });
	return std::move(result);
}
