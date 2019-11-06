#include "duckdb/storage/table/persistent_segment.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/types/vector.hpp"
#include "duckdb/common/vector_operations/vector_operations.hpp"
#include "duckdb/common/types/null_value.hpp"
#include "duckdb/storage/checkpoint/table_data_writer.hpp"
#include "duckdb/storage/meta_block_reader.hpp"

#include "duckdb/storage/numeric_segment.hpp"
#include "duckdb/storage/string_segment.hpp"

using namespace duckdb;
using namespace std;

PersistentSegment::PersistentSegment(BufferManager &manager, block_id_t id, index_t offset, TypeId type, index_t start,
                                     index_t count)
    : ColumnSegment(type, ColumnSegmentType::PERSISTENT, start, count), manager(manager), block_id(id), offset(offset) {
	assert(offset == 0);
	if (type == TypeId::VARCHAR) {
		data = make_unique<StringSegment>(manager, start, id);
		data->max_vector_count = count / STANDARD_VECTOR_SIZE + (count % STANDARD_VECTOR_SIZE == 0 ? 0 : 1);
	} else {
		data = make_unique<NumericSegment>(manager, type, start, id);
	}
	data->tuple_count = count;
}

void PersistentSegment::InitializeScan(ColumnScanState &state) {
	data->InitializeScan(state);
}

void PersistentSegment::Scan(Transaction &transaction, ColumnScanState &state, index_t vector_index, Vector &result) {
	data->Scan(transaction, state, vector_index, result);
}

void PersistentSegment::IndexScan(ColumnScanState &state, Vector &result) {
	data->IndexScan(state, state.vector_index, result);
}

void PersistentSegment::Fetch(ColumnScanState &state, index_t vector_index, Vector &result) {
	data->Fetch(state, vector_index, result);
}

void PersistentSegment::FetchRow(ColumnFetchState &state, Transaction &transaction, row_t row_id, Vector &result) {
	data->FetchRow(state, transaction, row_id - this->start, result);
}

void PersistentSegment::Update(ColumnData &column_data, Transaction &transaction, Vector &updates, row_t *ids) {
	// update of persistent segment: check if the table has been updated before
	if (block_id == data->block_id) {
		// data has not been updated before! convert the segment from one that refers to an on-disk block to one that
		// refers to a in-memory buffer
		data->ToTemporary();
	}
	data->Update(column_data, stats, transaction, updates, ids, this->start);
}
