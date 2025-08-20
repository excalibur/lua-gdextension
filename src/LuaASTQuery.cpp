/**
 * Copyright (C) 2025 Gil Barbosa Reis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "LuaASTQuery.hpp"

#include "LuaASTNode.hpp"

#include "tree_sitter/api.h"
#include "utils/tree_sitter_lua.hpp"

namespace luagdextension {

LuaASTQuery::LuaASTQuery()
	: cursor(ts_query_cursor_new())
	, node({0})
{
}
LuaASTQuery::~LuaASTQuery() {
	if (cursor) {
		ts_query_cursor_delete(cursor);
	}
	if (query) {
		ts_query_delete(query);
	}
}

void LuaASTQuery::set_query(const String& query) {
	CharString query_chars = query.utf8();
	uint32_t error_offset;
	TSQueryError error;
	this->query = ts_query_new(tree_sitter_lua(), query_chars.ptr(), query_chars.length(), &error_offset, &error);
	if (error != TSQueryErrorNone) {
		int64_t newlines = query.count("\n", 0, error_offset);
		ERR_PRINT(String("Invalid query '%s' @ line %d") % Array::make(query, newlines + 1));
	}
}

void LuaASTQuery::set_node(LuaASTNode *node) {
	if (node) {
		this->node = node->get_node();
	}
	else {
		this->node = {0};
	}
}

bool LuaASTQuery::_iter_init(const Variant& iter) const {
	ERR_FAIL_COND_V_MSG(query == nullptr, false, "Cannot iterate without a query");
	ERR_FAIL_COND_V_MSG(ts_node_is_null(node), false, "Cannot iterate without a target node");

	ts_query_cursor_exec(cursor, query, node);
	Array arr = iter;
	arr[0] = Array();
	return _iter_next(iter);
}

bool LuaASTQuery::_iter_next(const Variant& iter) const {
	Array arr = iter;
	Array matches = arr[0];
	matches.clear();
	
	TSQueryMatch match;
	if (ts_query_cursor_next_match(cursor, &match)) {
		for (int i = 0; i < match.capture_count; i++) {
			matches.append(memnew(LuaASTNode(match.captures[i].node)));
		}
		return true;
	}
	else {
		return false;
	}
}

Variant LuaASTQuery::_iter_get(const Variant& iter) const {
	return iter;
}

void LuaASTQuery::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_query", "query"), &LuaASTQuery::set_query);
	ClassDB::bind_method(D_METHOD("set_node", "node"), &LuaASTQuery::set_node);

	ClassDB::bind_method(D_METHOD("_iter_init", "iter"), &LuaASTQuery::_iter_init);
	ClassDB::bind_method(D_METHOD("_iter_next", "iter"), &LuaASTQuery::_iter_next);
	ClassDB::bind_method(D_METHOD("_iter_get", "iter"), &LuaASTQuery::_iter_get);
}

String LuaASTQuery::_to_string() const {
	return String("[%s:%d]") % Array::make(get_class_static(), get_instance_id());
}

}
