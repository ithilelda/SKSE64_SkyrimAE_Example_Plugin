#include "plugin.hpp"
#include "versionlibdb.h"

extern "C"
{
	__declspec(dllexport) SKSEPluginVersionData SKSEPlugin_Version
	{
		SKSEPluginVersionData::kVersion,
		PLUGIN_VERSION_MAJOR,
		"Animatron",
		"ithilelda",
		"",
		0,	// not version independent (extended field)
		0,	// not version independent
		{ RUNTIME_VERSION_1_6_640, 0 },	// compatible with 1.6.640. for more versions, add the macros before 0.
		0,	// works with any version of the script extender. you probably do not need to put anything here
	};

	__declspec(dllexport) bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
		_MESSAGE("[MESSAGE] example loaded");
		VersionDb db;
		db.Load();
		db.Dump("offsets.txt");

		return true;
	};
};