
#ifndef C4LL_CGL_INC
#define C4LL_CGL_INC

#include <stdint.h>
#include <memory>

class Cgl
{
public:
  Cgl(void);
  ~Cgl(void);
  Cgl(const Cgl&) = delete;

  void clear(void);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
