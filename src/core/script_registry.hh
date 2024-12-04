#pragma once
#include "scriptable.hh"

namespace Parrot {
	// ScriptRecord
	using ScriptRecord = Pair<usize, function<UniquePtr<Script>()>>;
	// (global) script_registry
	inline Map<string, ScriptRecord> g_script_registry;
}