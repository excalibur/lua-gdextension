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
#ifndef __LUA_SCRIPT_LANGUAGE_EXTENSION_HPP__
#define __LUA_SCRIPT_LANGUAGE_EXTENSION_HPP__

#include <godot_cpp/classes/script.hpp>
#include <godot_cpp/classes/script_language_extension.hpp>

#include "../LuaParser.hpp"
#include "../LuaState.hpp"

using namespace godot;

namespace luagdextension {

class LuaScriptLanguage : public ScriptLanguageExtension {
	GDCLASS(LuaScriptLanguage, ScriptLanguageExtension);

public:
	String _get_name() const override;
	void _init() override;
	String _get_type() const override;
	String _get_extension() const override;
	void _finish() override;
	PackedStringArray _get_reserved_words() const override;
	bool _is_control_flow_keyword(const String &p_keyword) const override;
	PackedStringArray _get_comment_delimiters() const override;
	PackedStringArray _get_doc_comment_delimiters() const override;
	PackedStringArray _get_string_delimiters() const override;
	Ref<Script> _make_template(const String &p_template, const String &p_class_name, const String &p_base_class_name) const override;
	TypedArray<Dictionary> _get_built_in_templates(const StringName &p_object) const override;
	bool _is_using_templates() override;
	Dictionary _validate(const String &p_script, const String &p_path, bool p_validate_functions, bool p_validate_errors, bool p_validate_warnings, bool p_validate_safe_lines) const override;
	String _validate_path(const String &p_path) const override;
	Object *_create_script() const override;
	bool _has_named_classes() const override;
	bool _supports_builtin_mode() const override;
	bool _supports_documentation() const override;
	bool _can_inherit_from_file() const override;
	int32_t _find_function(const String &p_function, const String &p_code) const override;
	String _make_function(const String &p_class_name, const String &p_function_name, const PackedStringArray &p_function_args) const override;
	bool _can_make_function() const override;
	Error _open_in_external_editor(const Ref<Script> &p_script, int32_t p_line, int32_t p_column) override;
	bool _overrides_external_editor() override;
	ScriptLanguage::ScriptNameCasing _preferred_file_name_casing() const override;
	Dictionary _complete_code(const String &p_code, const String &p_path, Object *p_owner) const override;
	Dictionary _lookup_code(const String &p_code, const String &p_symbol, const String &p_path, Object *p_owner) const override;
	String _auto_indent_code(const String &p_code, int32_t p_from_line, int32_t p_to_line) const override;
	void _add_global_constant(const StringName &p_name, const Variant &p_value) override;
	void _add_named_global_constant(const StringName &p_name, const Variant &p_value) override;
	void _remove_named_global_constant(const StringName &p_name) override;
	void _thread_enter() override;
	void _thread_exit() override;
	String _debug_get_error() const override;
	int32_t _debug_get_stack_level_count() const override;
	int32_t _debug_get_stack_level_line(int32_t p_level) const override;
	String _debug_get_stack_level_function(int32_t p_level) const override;
	String _debug_get_stack_level_source(int32_t p_level) const override;
	Dictionary _debug_get_stack_level_locals(int32_t p_level, int32_t p_max_subitems, int32_t p_max_depth) override;
	Dictionary _debug_get_stack_level_members(int32_t p_level, int32_t p_max_subitems, int32_t p_max_depth) override;
	void *_debug_get_stack_level_instance(int32_t p_level) override;
	Dictionary _debug_get_globals(int32_t p_max_subitems, int32_t p_max_depth) override;
	String _debug_parse_stack_level_expression(int32_t p_level, const String &p_expression, int32_t p_max_subitems, int32_t p_max_depth) override;
	TypedArray<Dictionary> _debug_get_current_stack_info() override;
	void _reload_all_scripts() override;
	void _reload_tool_script(const Ref<Script> &p_script, bool p_soft_reload) override;
	PackedStringArray _get_recognized_extensions() const override;
	TypedArray<Dictionary> _get_public_functions() const override;
	Dictionary _get_public_constants() const override;
	TypedArray<Dictionary> _get_public_annotations() const override;
	void _profiling_start() override;
	void _profiling_stop() override;
	void _profiling_set_save_native_calls(bool p_enable) override;
	int32_t _profiling_get_accumulated_data(ScriptLanguageExtensionProfilingInfo *p_info_array, int32_t p_info_max) override;
	int32_t _profiling_get_frame_data(ScriptLanguageExtensionProfilingInfo *p_info_array, int32_t p_info_max) override;
	void _frame() override;
	bool _handles_global_class_type(const String &p_type) const override;
	Dictionary _get_global_class_name(const String &p_path) const override;

	PackedStringArray get_lua_keywords() const;
	PackedStringArray get_lua_member_keywords() const;

	LuaState *get_lua_state();
	LuaParser *get_lua_parser() const;

	static LuaScriptLanguage *get_singleton();
	static LuaScriptLanguage *get_or_create_singleton();
	static void delete_singleton();

protected:
	static void _bind_methods();

	Ref<LuaState> lua_state;
	Ref<LuaParser> lua_parser;

private:
	static LuaScriptLanguage *instance;
};

}

#endif  // __LUA_SCRIPT_LANGUAGE_EXTENSION_HPP__
