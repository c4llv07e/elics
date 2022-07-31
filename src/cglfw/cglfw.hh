
#ifndef C4LL_CGLFW_INC
#define C4LL_CGLFW_INC

#include <stdint.h>
#include <memory>

class Cglfw
{
public:
  Cglfw(void);
  ~Cglfw(void);
  void pollEvents(void);
  Cglfw(const Cglfw&) = delete;
};

#endif
