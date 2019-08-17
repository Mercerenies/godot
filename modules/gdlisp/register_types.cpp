
#include "register_types.h"
#include "lisp.hpp"
#include "sxp.hpp"

#include "core/class_db.h"

void register_gdlisp_types() {
  ScriptServer::register_language(&GDLispScriptLanguage::instance);
  ClassDB::register_class<GDLispScript>();
  ClassDB::register_class<Sxp>();
}

void unregister_gdlisp_types() {
  ScriptServer::unregister_language(&GDLispScriptLanguage::instance);
}
