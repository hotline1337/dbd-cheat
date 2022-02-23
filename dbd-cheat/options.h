#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "utils/libraries/xor.h"

#define A(s) _(#s)
#define OPTION(type, var, val) Var<type> var = {A(var), val}

template <typename T = bool>
class Var {
public:
	std::string name;
	std::shared_ptr<T> value;
	int32_t size;
	Var(const std::string name, T v) : name(name) 
	{
		value = std::make_shared<T>(v);
		size = sizeof(T);
	}

	operator T() { return *value; }
	operator T* () { return &*value; }
	operator T() const { return *value; }
};

class Options
{
public:
	/* survivor */
	OPTION(bool, survivor_name, false);
	OPTION(bool, survivor_skeleton, false);

	/* killer */
	OPTION(bool, killer_name, false);
	OPTION(bool, killer_skeleton, false);

	/* entities */
	OPTION(bool, generator, false);
	OPTION(bool, pallet, false);
	OPTION(bool, escape_door, false);
	OPTION(bool, chest, false);
	OPTION(bool, window, false);
	OPTION(bool, totem, false);
	OPTION(bool, hatch, false);
	OPTION(bool, bear_trap, false);
	
	/* misc */
	OPTION(bool, watermark, true);
};

inline Options settings;