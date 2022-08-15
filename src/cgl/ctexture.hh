
#ifndef C4LL_CTEXTURE_INC
#define C4LL_CTEXTURE_INC

#include <memory>

class Ctexture
{
public:
  Ctexture(const char* path);
  ~Ctexture(void);
  Ctexture(const Ctexture&) = delete;

private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
