#pragma once
#include <vector>
#include <maya/MObject.h>
#include <maya/MDagPath.h>
#include <maya/MPlug.h>

namespace cmds {

	static MObject MObjectDefault;

	struct MayaObject final {
		MObject mobject;
		MDagPath mdagpath;
		MPlug mplug;

		MayaObject() {}
		~MayaObject() {}

		MayaObject(const MayaObject& other) : mobject(other.mobject) {
			if (other.mobject.hasFn(MFn::kComponent)) {
				mdagpath = other.mdagpath;
			} else if (other.mobject.hasFn(MFn::kAttribute)) {
				mplug = other.mplug;
			}
		}
	};

	struct Component final {
		MDagPath mdagpath;
		MObject mobject;

		Component() {}
		Component(MDagPath mdagpath, MObject mobject) : mdagpath(mdagpath), mobject(mobject) {}
	};

}// namespace cmds

