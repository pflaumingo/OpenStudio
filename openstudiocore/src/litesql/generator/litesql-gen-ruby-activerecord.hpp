#ifndef litesql_gen_ruby_activerecord_hpp
#define litesql_gen_ruby_activerecord_hpp

#include "generator.hpp"

namespace xml {
class Object;
}  // namespace xml

namespace litesql {

class ObjectModel;

  class RubyActiveRecordGenerator : public CompositeGenerator {
  public:
    RubyActiveRecordGenerator();
  };

  class ActiveRecordClassGenerator : public CodeGenerator {
  public:
    ActiveRecordClassGenerator(): CodeGenerator("ruby-activerecord-class") { };
    bool generateCode(const ObjectModel* model);
  protected:   
    bool generate(xml::Object* const object);
  };

  class RubyMigrationsGenerator : public CodeGenerator {
  public:
    RubyMigrationsGenerator(): CodeGenerator("ruby-activerecord-migrations") { };
    bool generateCode(const ObjectModel* model);
  };

}

#endif
