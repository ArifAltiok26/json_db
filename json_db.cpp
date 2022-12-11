#include "JSONVar.h"
#include "json_db.h"
#include <LittleFS.h>

namespace YGV{
  static bool isLittleFSBegin = false;
  size_t readFile(const String& filename,String& buff){
    File file = LittleFS.open(filename,"r");
    if(!file)
      return -1;
    size_t size = file.size();
    std::unique_ptr<char[]> bf(new char[size]);
    if(file.readBytes(bf.get(), size) > 0){
      buff = bf.get();
      bf.release();
    }
    file.close();
    
    return -1;
  }

  size_t writeFile(const String& filename,const String& buff){
    File file = LittleFS.open(filename,"w");
    if(!file)
      return -1;
    size_t retval = file.write(buff.c_str());
    file.close();
    return retval;
  }

  size_t writeFile(const String& filename,const String& buff);

  JsonDB::JsonDB(const String& filename) : m_filename(filename){
    init();
  }

  bool JsonDB::begin(){
    if(isLittleFSBegin)
      return true;
    
    if(!LittleFS.begin()){
      return false;
    }
    isLittleFSBegin = true;
    return true;
  }

  void JsonDB::init(){
    String buff;
    size_t read_size = readFile(m_filename, buff);
    if(read_size > 0){
      m_json = JSON.parse(buff);
    }
  }

  size_t JsonDB::update()const{
    return writeFile(m_filename,JSON.stringify(m_json));
  }
}