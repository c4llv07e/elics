
#ifndef C4LL_CSHADER_INC
#define C4LL_CSHADER_INC

#include <stdint.h>
#include <memory>

class Cshader
{
public:
  Cshader(void);
  ~Cshader(void);
  Cshader(const Cshader&) = delete;

  void link(void);
  void use(void);
  void bindAttr(unsigned int ind, const char* name);
  void setFloat(const char* name, float value);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
