#include <iostream>
#include <memory>

template <typename T> class ElemTempl {};

template <typename T> class GhostingFunctor {
public:
  virtual void operator()(const ElemTempl<T> &) = 0;
};

template <typename T> class DefaultCoupling : public GhostingFunctor<T> {
public:
  virtual void operator()(const ElemTempl<T> &) override {
    std::cout << "I'm the default coupling functor\n";
  }
};

class GhostingFunctorContainer {
public:
  template <typename GF>
  GhostingFunctorContainer(GF & gf) : ghosting_functor(std::make_shared<
