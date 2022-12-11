#pragma once
#include <Arduino_JSON.h>
namespace YGV{
  class JsonDB{
  public:
    JsonDB(const String& filename);

    JsonDB(const JsonDB&) = delete;

    JsonDB(JsonDB&&) = delete;

    JsonDB& operator=(const JsonDB&) = delete;

    JsonDB& operator=(JsonDB&&) = delete;

    static bool begin();

    template<typename ValueType>
    bool get(const char* key,ValueType& value){
      if(!m_json.hasOwnProperty(key))return false;
      value = (ValueType)m_json[key];
      return true;
    }

    template<typename ValueType>
    bool set(const char* key,const ValueType& value){
      m_json[key] = value;
      update();
      return true;
    }

  private:
    void init();

    size_t update()const;

  private:
    String m_filename;
    JSONVar m_json;
  };
}