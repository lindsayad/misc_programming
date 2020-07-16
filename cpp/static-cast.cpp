#include <iostream>
#include <set>

class GhostingFunctorBase
{
};

template <typename T>
class GhostingFunctor : public GhostingFunctorBase
{
public:
  virtual void foo(const T &) const = 0;
};

template <typename T>
class DefaultCoupling : public GhostingFunctor<T>
{
public:
  void foo(const T &) const override
    {
      std::cout << "this is the default coupling class\n";
    }
};

template <typename T>
class GhostPointNeighbors : public GhostingFunctor<T>
{
public:
  void foo(const T &) const override
    {
      std::cout << "this is the ghost point neighbor class\n";
    }
};

class DofMap
{
public:
  void add_ghosting_functor(GhostingFunctorBase & gf)
    {
      _ghosting_functors.insert(&gf);
    }

  template <typename T>
  void merge_ghosting_functors_output(const T & elem)
    {
      for (const auto gf_base : _ghosting_functors)
      {
        const auto gf = static_cast<const GhostingFunctor<T> *>(gf_base);
        gf->foo(elem);
      }
    }

private:
  std::set<GhostingFunctorBase *> _ghosting_functors;
};

int main()
{
  DefaultCoupling<double> dc;
  GhostPointNeighbors<double> gp;
  DofMap dof_map;
  dof_map.add_ghosting_functor(dc);
  dof_map.add_ghosting_functor(gp);
  dof_map.merge_ghosting_functors_output(double(5));
}
