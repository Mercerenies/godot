
#ifndef LISP_HPP
#define LISP_HPP

#include "core/script_language.h"

class GDLispScript : public Script {
private:
  GDCLASS(GDLispScript, Script);
  RES_BASE_EXTENSION("lisp");

  bool tool;
  bool valid;

  Ref<Script> base;
  StringName native; // TODO Uhhhh, yeah... let's actually make this a class at some point

  String source;

#ifdef TOOLS_ENABLED
  bool source_changed;
#endif

public:
  virtual bool can_instance() const;
  virtual Ref<Script> get_base_script() const;
  virtual StringName get_instance_base_type() const;
  virtual ScriptInstance* instance_create(Object*);
  virtual bool instance_has(const Object*) const;
  virtual bool has_source_code() const;
  virtual String get_source_code() const;
  virtual void set_source_code(const String&);
  virtual Error reload(bool);
  virtual bool has_method(const StringName&) const;
  virtual MethodInfo get_method_info(const StringName&) const;
  virtual ScriptLanguage* get_language() const;
  virtual bool has_script_signal(const StringName&) const;
  virtual void get_script_signal_list(List<MethodInfo>*) const;
  virtual bool get_property_default_value(const StringName&, Variant&) const;
  virtual void get_script_method_list(List<MethodInfo>*) const;
  virtual void get_script_property_list(List<PropertyInfo>*) const;

  virtual bool is_tool() const {
    return tool;
  }
  virtual bool is_valid() const {
    return valid;
  }

};

class GDLispScriptLanguage : public ScriptLanguage {
private:

  Map<StringName, Variant> globals;

public:

  static GDLispScriptLanguage instance;

  virtual String get_name() const;
  virtual void init();
  virtual String get_type() const;
  virtual String get_extension() const;
  virtual Error execute_file(const String&);
  virtual void finish();
  virtual void get_reserved_words(List<String>*) const;
  virtual void get_comment_delimiters(List<String>*) const;
  virtual void get_string_delimiters(List<String>*) const;
  virtual Ref<Script> get_template(const String&, const String&) const;
  virtual bool validate(const String&, int&, int&, String&, const String&, List<String>*, List<ScriptLanguage::Warning>*, Set<int>*) const;
  virtual Script* create_script() const;
  virtual bool has_named_classes() const;
  virtual bool supports_builtin_mode() const;
  virtual int find_function(const String&, const String&) const;
  virtual String make_function(const String&, const String&, const PoolStringArray&) const;
  virtual void auto_indent_code(String&, int, int) const;
  virtual void add_global_constant(const StringName&, const Variant&);
  virtual String debug_get_error() const;
  virtual int debug_get_stack_level_count() const;
  virtual int debug_get_stack_level_line(int) const;
  virtual String debug_get_stack_level_function(int) const;
  virtual String debug_get_stack_level_source(int) const;
  virtual void debug_get_stack_level_locals(int, List<String>*, List<Variant>*, int, int);
  virtual void debug_get_stack_level_members(int, List<String>*, List<Variant>*, int, int);
  virtual void debug_get_globals(List<String>*, List<Variant>*, int, int);
  virtual String debug_parse_stack_level_expression(int, const String&, int, int);
  virtual void reload_all_scripts();
  virtual void reload_tool_script(const Ref<Script>&, bool);
  virtual void get_recognized_extensions(List<String>*) const;
  virtual void get_public_functions(List<MethodInfo>*) const;
  virtual void get_public_constants(List<Pair<String, Variant>>*) const;
  virtual void profiling_start();
  virtual void profiling_stop();
  virtual int profiling_get_accumulated_data(ScriptLanguage::ProfilingInfo*, int);
  virtual int profiling_get_frame_data(ScriptLanguage::ProfilingInfo*, int);

private:
  GDLispScriptLanguage() = default;

};

class GDLispInstance : public ScriptInstance {
private:
  Object* owner;
  Ref<GDLispScript> script;
public:

  virtual Object* get_owner() { return owner; }
  virtual bool set(const StringName&, const Variant&);
  virtual bool get(const StringName&, Variant&) const;
  virtual void get_property_list(List<PropertyInfo>*) const;
  virtual Variant::Type get_property_type(const StringName&, bool*) const;
  virtual void get_method_list(List<MethodInfo>*) const;
  virtual bool has_method(const StringName&) const;
  virtual Variant call(const StringName&, const Variant**, int, Variant::CallError&);
  virtual void notification(int);
  virtual Ref<Script> get_script() const;
  virtual MultiplayerAPI::RPCMode get_rpc_mode(const StringName&) const;
  virtual MultiplayerAPI::RPCMode get_rset_mode(const StringName&) const;
  virtual ScriptLanguage* get_language();

  GDLispInstance(Object* owner, Ref<GDLispScript> script);

};

#endif // LISP_HPP
