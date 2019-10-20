#include "relatives.h"
#include <queue>

using namespace cmds;

std::vector<MObject> cmds::ListParents(const MFnDagNode& mfn, MFn::Type node_type) {
	std::vector<MObject> result;
	for (uint i = 0; i < mfn.parentCount(); ++i) {
		auto parent = mfn.parent(i);
		if (!parent.hasFn(node_type)) {
			continue;
		}
		result.push_back(parent);
	}
	return std::move(result);
}

std::vector<MObject> cmds::ListChildren(const MFnDagNode& mfn, MFn::Type node_type) {
	std::vector<MObject> result;
	for (uint i = 0; i < mfn.childCount(); ++i) {
		auto child = mfn.child(i);
		if (!child.hasFn(node_type)) {
			continue;
		}
		result.push_back(child);
	}
	return std::move(result);
}

std::vector<MObject> cmds::ListAnscestors(const MFnDagNode& mfn, MFn::Type node_type) {
	std::vector<MObject> result;

	std::queue<MObject> queue;
	queue.push(mfn.object());

	MFnDagNode tmp_mfn;

	while (!queue.empty()) {
		auto node = queue.front();
		queue.pop();

		tmp_mfn.setObject(node);
		for (uint i = 0; i < tmp_mfn.parentCount(); ++i) {
			auto parent = tmp_mfn.parent(i);
			if (parent.hasFn(MFn::kWorld)) {
				continue;
			}
			if (parent.hasFn(node_type)) {
				result.push_back(parent);
			}
			queue.push(parent);
		}
	}

	return std::move(result);
}

std::vector<MObject> cmds::ListDescendents(const MFnDagNode& mfn, MFn::Type node_type) {
	std::vector<MObject> result;

	std::queue<MObject> queue;
	queue.push(mfn.object());

	MFnDagNode tmp_mfn;

	while (!queue.empty()) {
		auto node = queue.front();
		queue.pop();

		tmp_mfn.setObject(node);
		for (uint i = 0; i < tmp_mfn.childCount(); ++i) {
			auto child = tmp_mfn.child(i);
			if (child.hasFn(MFn::kWorld)) {
				continue;
			}
			if (child.hasFn(node_type)) {
				result.push_back(child);
			}
			queue.push(child);
		}
	}

	return std::move(result);
}

