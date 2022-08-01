
#ifndef C4LL_CVAO_INC
#define C4LL_CVAO_INC

#include <stdint.h>
#include <memory>
#include <vector>

class Cvao
{
public:
  Cvao(void);
  ~Cvao(void);
  Cvao(const Cvao&) = delete;

  void bind(void);
  void draw(void);
  void addEbo(const std::vector<unsigned int>& data);
  void addVbo(const std::vector<float>& data, size_t groupLen);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
