
#include "lisp.hpp"
#include "parser.hpp"

#include <iostream>

bool GDLispScript::can_instance() const {

#ifdef TOOLS_ENABLED
  return is_valid() && (is_tool() || ScriptServer::is_scripting_enabled());
#else
  return is_valid();
#endif

}

Ref<Script> GDLispScript::get_base_script() const {
  return base;
}

StringName GDLispScript::get_instance_base_type() const {
  if (native != StringName())
    return native;
  else if (base.is_valid())
    return base->get_instance_base_type();
  else
    return StringName();
}

ScriptInstance* GDLispScript::instance_create(Object*) {
  // !!!
  return nullptr;
}

bool GDLispScript::instance_has(const Object*) const {
  return false; // ???
}

bool GDLispScript::has_source_code() const {
  return source != "";
}

String GDLispScript::get_source_code() const {
  return source;
}

void GDLispScript::set_source_code(const String& code) {
  if (source == code)
    return;
  source = code;
#ifdef TOOLS_ENABLED
  source_changed = true;
#endif
}

Error GDLispScript::reload(bool) {
  return OK; // ???
}

bool GDLispScript::has_method(const StringName&) const {
  return false; // ???
}

MethodInfo GDLispScript::get_method_info(const StringName&) const {
  return {}; // !!!
}

ScriptLanguage* GDLispScript::get_language() const {
  return &GDLispScriptLanguage::instance;
}

bool GDLispScript::has_script_signal(const StringName&) const {
  return false; // ???
}

void GDLispScript::get_script_signal_list(List<MethodInfo>*) const {
  // ???
}

bool GDLispScript::get_property_default_value(const StringName&, Variant&) const {
  return false; // ???
}

void GDLispScript::get_script_method_list(List<MethodInfo>*) const {
  // ???
}

void GDLispScript::get_script_property_list(List<PropertyInfo>*) const {
  // ???
}

GDLispScriptLanguage GDLispScriptLanguage::instance;

String GDLispScriptLanguage::get_name() const {
  return "GDLisp";
}

void GDLispScriptLanguage::init() {}

String GDLispScriptLanguage::get_type() const {
  return "GDLisp";
}

String GDLispScriptLanguage::get_extension() const {
  return "lisp";
}

Error GDLispScriptLanguage::execute_file(const String&) {
  return OK; // ???
}

void GDLispScriptLanguage::finish() {}

void GDLispScriptLanguage::get_reserved_words(List<String>* words) const {
  // TODO Fill in reserved words
}

void GDLispScriptLanguage::get_comment_delimiters(List<String>* list) const {
  list->push_back(";");
}

void GDLispScriptLanguage::get_string_delimiters(List<String>* list) const {
  list->push_back("\" \"");
  list->push_back("\"\"\" \"\"\"");
}

Ref<Script> GDLispScriptLanguage::get_template(const String& cls_name, const String& base_cls_name) const {
  Ref<GDLispScript> script;
  script.instance();
  return script;
}

bool GDLispScriptLanguage::validate(const String& script,
                                    int& error_line, int& error_column,
                                    String& error_message, const String& path,
                                    List<String>* functions,
                                    List<ScriptLanguage::Warning>* warnings,
                                    Set<int>* safe_lines) const {

  auto result = parse_lisp(script);
  if (result.error != OK) {
    // Ahhhhh it's all one-indexed!
    error_line = result.error_pos.first + 1;
    error_column = result.error_pos.second + 1;
    error_message = String(result.error_text);
    return false;
  }
  // TODO Add functions and warnings (maybe safe lines? idk)
  return true;

}

Script* GDLispScriptLanguage::create_script() const {
  return memnew(GDLispScript);
}

bool GDLispScriptLanguage::has_named_classes() const {
  return true;
}

bool GDLispScriptLanguage::supports_builtin_mode() const {
  return true;
}

int GDLispScriptLanguage::find_function(const String&, const String&) const {
  return -1; // ???
}

String GDLispScriptLanguage::make_function(const String&, const String&, const PoolStringArray&) const {
  return String(); // ???
}

void GDLispScriptLanguage::auto_indent_code(String&, int, int) const {
  // ???
}

void GDLispScriptLanguage::add_global_constant(const StringName&, const Variant&) {
  // ???
}

String GDLispScriptLanguage::debug_get_error() const {
  return ""; // ???
}

int GDLispScriptLanguage::debug_get_stack_level_count() const {
  return 0; // ???
}

int GDLispScriptLanguage::debug_get_stack_level_line(int) const {
  return 0; // ???
}

String GDLispScriptLanguage::debug_get_stack_level_function(int) const {
  return ""; // ???
}

String GDLispScriptLanguage::debug_get_stack_level_source(int) const {
  return ""; // ???
}

void GDLispScriptLanguage::debug_get_stack_level_locals(int, List<String>*, List<Variant>*, int, int) {
  // ???
}

void GDLispScriptLanguage::debug_get_stack_level_members(int, List<String>*, List<Variant>*, int, int) {
  // ???
}

void GDLispScriptLanguage::debug_get_globals(List<String>*, List<Variant>*, int, int) {
  // ???
}

String GDLispScriptLanguage::debug_parse_stack_level_expression(int, const String&, int, int) {
  return ""; // ???
}

void GDLispScriptLanguage::reload_all_scripts() {
  // ???
}

void GDLispScriptLanguage::reload_tool_script(const Ref<Script>&, bool) {
  // ???
}

void GDLispScriptLanguage::get_recognized_extensions(List<String>* ext) const {
  ext->push_back("lisp");
}

void GDLispScriptLanguage::get_public_functions(List<MethodInfo>*) const {
  // ???
}

void GDLispScriptLanguage::get_public_constants(List<Pair<String, Variant>>*) const {
  // ???
}

void GDLispScriptLanguage::profiling_start() {
  // ???
}

void GDLispScriptLanguage::profiling_stop() {
  // ???
}

int GDLispScriptLanguage::profiling_get_accumulated_data(ScriptLanguage::ProfilingInfo*, int) {
  return 0; // ???
}

int GDLispScriptLanguage::profiling_get_frame_data(ScriptLanguage::ProfilingInfo*, int) {
  return 0; // ???
}

bool GDLispInstance::set(const StringName&, const Variant&) {
  // ???
  return true;
}

bool GDLispInstance::get(const StringName&, Variant&) const {
  // ???
  return true;
}

void GDLispInstance::get_property_list(List<PropertyInfo>*) const {
  // ???
}

Variant::Type GDLispInstance::get_property_type(const StringName&, bool*) const {
  // ???
  return Variant::NIL;
}

void GDLispInstance::get_method_list(List<MethodInfo>*) const {
  // ???
}

bool GDLispInstance::has_method(const StringName& mthd) const {
  Ref<Script> ptr = script;
  while (ptr.is_valid()) {
    if (ptr->has_method(mthd))
      return true;
    ptr = ptr->get_base_script();
  }
  return false;
}

Variant GDLispInstance::call(const StringName&, const Variant**, int, Variant::CallError&) {
  // ???
  return Variant();
}

void GDLispInstance::notification(int) {
  // ???
}

Ref<Script> GDLispInstance::get_script() const {
  return script;
}

MultiplayerAPI::RPCMode GDLispInstance::get_rpc_mode(const StringName&) const {
  // ???
  return MultiplayerAPI::RPC_MODE_DISABLED;
}

MultiplayerAPI::RPCMode GDLispInstance::get_rset_mode(const StringName&) const {
  // ???
  return MultiplayerAPI::RPC_MODE_DISABLED;
}

ScriptLanguage* GDLispInstance::get_language() {
  return &GDLispScriptLanguage::instance;
}

GDLispInstance::GDLispInstance(Object* owner, Ref<GDLispScript> script)
  : owner(owner), script(script) {}
