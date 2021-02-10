#include <iostream>
#include <map>
#include <string>
#include <functional>

class Elem
{
};
class FaceInfo
{
};
class Variable
{
  double _x;

public:
  Variable(const double x) : _x(x) {}
  double operator()(const Elem & elem) const { return _x; }
  double operator()(const FaceInfo & fi) const { return _x; }
  double operator()(const unsigned int qp) const { return _x; }
};

class MaterialProperty
{
public:
  using ElemFn = std::function<double(const Elem &)>;
  using FiFn = std::function<double(const FaceInfo &)>;
  using QpFn = std::function<double(const unsigned int &)>;

  template <typename PolymorphicLambda>
  MaterialProperty & operator=(PolymorphicLambda my_lammy)
  {
    elem_functor = my_lammy;
    fi_functor = my_lammy;
    qp_functor = my_lammy;
    return *this;
  }

  double operator()(const Elem & elem) const { return elem_functor(elem); }

  double operator()(const FaceInfo & fi) const { return fi_functor(fi); }

  double operator()(const unsigned int qp) const { return qp_functor(qp); }

private:
  ElemFn elem_functor;
  FiFn fi_functor;
  QpFn qp_functor;
};

class Material
{
public:
  Material() : _u(2)
  {
    _mat_props["u2"] = [this](const auto & geom_entity) -> double {
      return _u(geom_entity) * _u(geom_entity);
    };
    _mat_props["u3"] = [this](const auto & geom_entity) -> double {
      return _u(geom_entity) * _u(geom_entity) * _u(geom_entity);
    };
  }

  const MaterialProperty & getMatProp(const std::string & name) const
  {
    return _mat_props.at(name);
  }

private:
  std::map<std::string, MaterialProperty> _mat_props;
  Variable _u;
};

class ResidualObject
{
public:
  void assignMatProp(const MaterialProperty & prop) { _mat_prop = &prop; }

protected:
  const MaterialProperty * _mat_prop;
};

class Kernel : public ResidualObject
{
public:
  void computeResidual(const Elem & elem) { std::cout << (*_mat_prop)(elem) << std::endl; }
};

class FVFluxKernel : public ResidualObject
{
public:
  void computeResidual(const FaceInfo & fi) { std::cout << (*_mat_prop)(fi) << std::endl; }
};

int
main()
{
  Material mat;
  Kernel kern;
  kern.assignMatProp(mat.getMatProp("u2"));
  FVFluxKernel fv;
  fv.assignMatProp(mat.getMatProp("u3"));

  kern.computeResidual(Elem());
  fv.computeResidual(FaceInfo());
}
