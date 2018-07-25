#include <iostream>
#include <vector>

class ADReal {
public:
  ADReal(double d) : _value(d), _derivatives(5, 0) {}
  ADReal() : _value(), _derivatives(5, 0) {}

  double value() { return _value; }
  double derivatives(unsigned i) { return _derivatives[i]; }

private:
  double _value;
  std::vector<double> _derivatives;
};

template <typename T> class MatProp {
protected:
  std::vector<T> _data;

public:
  template <typename U = T> U operator[](unsigned i) { return _data[i]; }
  template <typename U = T> const U &operator[](unsigned i) const {
    return _data[i];
  }
  void resize(unsigned n) { this->_data.resize(n); }

  MatProp() : _data() {}
};

class ADMatProp : public MatProp<double> {
protected:
  std::vector<ADReal> _data;

public:
  ADMatProp() : MatProp<double>(), _data() {}

  ADReal operator[](unsigned i) { return _data[i]; }
  const ADReal &operator[](unsigned i) const { return _data[i]; }
  // void resize(unsigned n) { _data.resize(n); }
};

// class ADMatProp : public MatProp<double> {
// private:
//   std::vector<ADReal> _ad_data;

// public:
//   ADMatProp() : MatProp<double>(), _ad_data() {}

//   ADReal operator[](unsigned i) { return _ad_data[i]; }
//   const ADReal &operator[](unsigned i) const { return _ad_data[i]; }
//   void resize(unsigned n) { _ad_data.resize(n); }
// };

int main() {
  ADMatProp ad_mat_prop;
  MatProp<double> mat_prop;
  ad_mat_prop.resize(5);
  mat_prop.resize(5);
  std::cout << ad_mat_prop[4].value() << std::endl;
  std::cout << mat_prop[4] << std::endl;
}
