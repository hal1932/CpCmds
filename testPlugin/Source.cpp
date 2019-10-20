#include <maya/MFnPlugin.h>
#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnComponent.h>
#include <maya/MPlug.h>
#include <maya/MFnDagNode.h>
#include <cpcmds.h>

class PluginTestCommand final : public MPxCommand {
public:
	static void* creator(void) {
		return new PluginTestCommand();
	}

	MStatus doIt(const MArgList&) {
		//for (auto& obj : cmds::ListSelectedObjects()) {
		//	if (!obj.mplug.isNull()) {
		//		MGlobal::displayInfo(MString("[plug] ") + obj.mplug.name());
		//		continue;
		//	}

		//	if (obj.mobject.hasFn(MFn::kComponent)) {
		//		MFnComponent mfn(obj.mobject);
		//		MGlobal::displayInfo(MString("[comp] ") + obj.mdagpath.fullPathName());
		//		continue;
		//	}

		//	if (obj.mobject.hasFn(MFn::kDependencyNode)) {
		//		MFnDependencyNode mfn(obj.mobject);
		//		MGlobal::displayInfo(MString("[node] ") + mfn.name());
		//		continue;
		//	}
		//}

		for (auto& mobj : cmds::ListNodes("pCubeShape1")) {
			for (auto& r : cmds::ListPlugConnections(mobj)) {
				MGlobal::displayInfo(r.name());
			}
		}

		return MStatus::kSuccess;
	}
};

MStatus initializePlugin(MObject obj) {
	MFnPlugin plugin(obj, "@hal1932", "1.0", "any");

	plugin.registerCommand("testPlugin", PluginTestCommand::creator);

	return MStatus::kSuccess;
}

MStatus uninitializePlugin(MObject obj) {
	MFnPlugin plugin(obj);

	plugin.deregisterCommand("testPlugin");

	return MStatus::kSuccess;
}
