#include "duckdb/planner/operator/logical_copy_database.hpp"
#include "duckdb/parser/parsed_data/create_schema_info.hpp"
#include "duckdb/parser/parsed_data/create_table_info.hpp"

namespace duckdb {

CopyDatabaseInfo::CopyDatabaseInfo(Catalog &from_database, Catalog &to_database) :
	from_database(from_database), to_database(to_database) {}

CopyDatabaseInfo::~CopyDatabaseInfo() {}

LogicalCopyDatabase::LogicalCopyDatabase(unique_ptr<CopyDatabaseInfo> info_p)
	: LogicalOperator(LogicalOperatorType::LOGICAL_COPY_DATABASE), info(std::move(info_p)) {
}

LogicalCopyDatabase::~LogicalCopyDatabase() {}

void LogicalCopyDatabase::Serialize(FieldWriter &writer) const {
	throw NotImplementedException(LogicalOperatorToString(type));
}

unique_ptr<LogicalOperator> LogicalCopyDatabase::Deserialize(LogicalDeserializationState &state, FieldReader &reader) {
	throw NotImplementedException(LogicalOperatorToString(state.type));
}

void LogicalCopyDatabase::ResolveTypes() {
	types.emplace_back(LogicalType::BOOLEAN);
}

} // namespace duckdb
