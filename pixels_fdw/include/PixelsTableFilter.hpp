/* #include <cstdint>
#include <memory>
#include <map>

enum class TableFilterType : uint8_t {
	CONSTANT_COMPARISON = 0, // constant comparison (e.g. =C, >C, >=C, <C, <=C)
	IS_NULL = 1,
	IS_NOT_NULL = 2,
	CONJUNCTION_OR = 3,
	CONJUNCTION_AND = 4,
	STRUCT_EXTRACT = 5
};

//! TableFilter represents a filter pushed down into the table scan.
class TableFilter {
public:
	explicit TableFilter(TableFilterType filter_type_p) : filter_type(filter_type_p) {
	}
	virtual ~TableFilter() {
	}

	TableFilterType filter_type;

public:
	virtual unique_ptr<TableFilter> Copy() const = 0;
	virtual bool Equals(const TableFilter &other) const {
		return filter_type != other.filter_type;
	}
	virtual std::unique_ptr<Expression> ToExpression(const Expression &column) const = 0;

	virtual void Serialize(Serializer &serializer) const;
	static std::unique_ptr<TableFilter> Deserialize(Deserializer &deserializer);

public:
	template <class TARGET>
	TARGET &Cast() {
		if (filter_type != TARGET::TYPE) {
			throw InternalException("Failed to cast table to type - table filter type mismatch");
		}
		return reinterpret_cast<TARGET &>(*this);
	}

	template <class TARGET>
	const TARGET &Cast() const {
		if (filter_type != TARGET::TYPE) {
			throw InternalException("Failed to cast table to type - table filter type mismatch");
		}
		return reinterpret_cast<const TARGET &>(*this);
	}
};

class TableFilterSet {
public:
	std::unordered_map<uint64_t, std::unique_ptr<TableFilter>> filters;

public:
	void PushFilter(uint64_t column_index, std::unique_ptr<TableFilter> filter);

	bool Equals(TableFilterSet &other) {
		if (filters.size() != other.filters.size()) {
			return false;
		}
		for (auto &entry : filters) {
			auto other_entry = other.filters.find(entry.first);
			if (other_entry == other.filters.end()) {
				return false;
			}
			if (!entry.second->Equals(*other_entry->second)) {
				return false;
			}
		}
		return true;
	}
	static bool Equals(TableFilterSet *left, TableFilterSet *right) {
		if (left == right) {
			return true;
		}
		if (!left || !right) {
			return false;
		}
		return left->Equals(*right);
	}

	void Serialize(Serializer &serializer) const;
	static TableFilterSet Deserialize(Deserializer &deserializer);
};

class DynamicTableFilterSet {
public:
	void ClearFilters(const PhysicalOperator &op);
	void PushFilter(const PhysicalOperator &op, idx_t column_index, unique_ptr<TableFilter> filter);

	bool HasFilters() const;
	unique_ptr<TableFilterSet> GetFinalTableFilters(const PhysicalTableScan &scan,
	                                                optional_ptr<TableFilterSet> existing_filters) const;

private:
	mutable mutex lock;
	reference_map_t<const PhysicalOperator, unique_ptr<TableFilterSet>> filters;
};
 */