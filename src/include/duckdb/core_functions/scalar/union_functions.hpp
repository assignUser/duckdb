//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/core_functions/scalar/union_functions.hpp
//
//
//===----------------------------------------------------------------------===//
// This file is generated by scripts/generate_functions.py

#pragma once

#include "duckdb/function/function_set.hpp"

namespace duckdb {

struct UnionExtractFun {
	static constexpr const char *Name = "union_extract";
	static constexpr const char *Parameters = "union,tag";
	static constexpr const char *Description = "Extract the value with the named tags from the union. NULL if the tag is not currently selected";
	static constexpr const char *Example = "union_extract(s, 'k')";

	static ScalarFunction GetFunction();
};

struct UnionTagFun {
	static constexpr const char *Name = "union_tag";
	static constexpr const char *Parameters = "union";
	static constexpr const char *Description = "Retrieve the currently selected tag of the union as an Enum.";
	static constexpr const char *Example = "union_tag(union_value(k := 'foo'))";

	static ScalarFunction GetFunction();
};

struct UnionValueFun {
	static constexpr const char *Name = "union_value";
	static constexpr const char *Parameters = "tag";
	static constexpr const char *Description = "Create a single member UNION containing the argument value. The tag of the value will be the bound variable name.";
	static constexpr const char *Example = "union_value(k := 'hello')";

	static ScalarFunction GetFunction();
};

} // namespace duckdb
