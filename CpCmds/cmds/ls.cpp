#include "ls.h"
#include <maya/MItDependencyNodes.h>
#include <maya/MSelectionList.h>
#include <maya/MGlobal.h>
#include <maya/MDagPath.h>
#include <maya/MPlug.h>
#include <maya/MFnDependencyNode.h>

using namespace cmds;

std::vector<MObject> cmds::ListNodes(MFn::Type node_type) {
	std::vector<MObject> result;

	MItDependencyNodes ite;
	while (!ite.isDone()) {
		auto mobj = ite.thisNode();
		if (mobj.hasFn(node_type)) {
			result.push_back(mobj);
		}
		ite.next();
	}

	return std::move(result);
}

std::vector<MObject> cmds::ListNodes(const MString& name, MFn::Type node_type) {
	std::vector<MObject> result;

	MItDependencyNodes ite;
	MFnDependencyNode tmp_mfn;

	while (!ite.isDone()) {
		auto mobj = ite.thisNode();

		if (mobj.hasFn(node_type)) {
			tmp_mfn.setObject(mobj);
			if (tmp_mfn.name() == name) {
				result.push_back(mobj);
			}
		}

		ite.next();
	}

	return std::move(result);
}

std::vector<MayaObject> cmds::ListSelectedObjects() {
	MSelectionList list;
	MGlobal::getActiveSelectionList(list);

	std::vector<MayaObject> result;
	if (list.length() == 0) {
		return result;
	}

	result.resize(list.length());

	MStatus status;
	MObject mobj;
	MDagPath mdagpath;
	MPlug mplug;

	for (uint i = 0; i < list.length(); ++i) {
		status = list.getDagPath(i, mdagpath, mobj);
		if (!status.error() && mobj.hasFn(MFn::kComponent)) {
			result[i].mdagpath = mdagpath;
			result[i].mobject = mobj;
			continue;
		}

		status = list.getPlug(i, mplug);
		if (!status.error()) {
			list.getDependNode(i, mobj);
			result[i].mobject = mobj;
			result[i].mplug = mplug;
			continue;
		}

		status = list.getDependNode(i, mobj);
		if (!status.error()) {
			result[i].mobject = mobj;
			continue;
		}
	}

	return std::move(result);
}

std::vector<MObject> cmds::ListSelectedNodes(MFn::Type node_type) {
	MSelectionList list;
	MGlobal::getActiveSelectionList(list);

	std::vector<MObject> result;
	if (list.length() == 0) {
		return result;
	}

	MStatus status;
	MObject mobj;

	for (uint i = 0; i < list.length(); ++i) {
		status = list.getDependNode(i, mobj);
		if (!status.error()) {
			result[i] = mobj;
			continue;
		}
	}

	return std::move(result);
}

std::vector<Component> cmds::ListSelectedComponents() {
	MSelectionList list;
	MGlobal::getActiveSelectionList(list);

	std::vector<Component> result;
	if (list.length() == 0) {
		return result;
	}

	MStatus status;
	MObject mobj;
	MDagPath mdagpath;

	for (uint i = 0; i < list.length(); ++i) {
		status = list.getDagPath(i, mdagpath, mobj);
		if (!status.error() && mobj.hasFn(MFn::kComponent)) {
			result.emplace_back(mdagpath, mobj);
			continue;
		}
	}

	return std::move(result);
}
