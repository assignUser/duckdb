//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/common_table_expression_info.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/statement/select_statement.hpp"

namespace duckdb {

class SelectStatement;

enum class CTEMaterialize : uint8_t {
	CTE_MATERIALIZE_DEFAULT = 1,		/* no option specified */
	CTE_MATERIALIZE_ALWAYS = 2,		/* MATERIALIZED */
	CTE_MATERIALIZE_NEVER = 3			/* NOT MATERIALIZED */
};


struct CommonTableExpressionInfo {
	vector<string> aliases;
	unique_ptr<SelectStatement> query;
	CTEMaterialize materialized = CTEMaterialize::CTE_MATERIALIZE_DEFAULT;

	void FormatSerialize(FormatSerializer &serializer) const;
	static unique_ptr<CommonTableExpressionInfo> FormatDeserialize(FormatDeserializer &deserializer);
	unique_ptr<CommonTableExpressionInfo> Copy();
};

} // namespace duckdb
