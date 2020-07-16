#include <iostream>
#include <memory>
#include <unordered_map>

class UserObject {
public:
  UserObject() = default;
};

class Material {
public:
  Material(unsigned int subdomain);

private:
  static std::unordered_map<unsigned int, std::unique_ptr<UserObject>>
      _sub_to_uo;
};

std::unordered_map<unsigned int, std::unique_ptr<UserObject>>
    Material::_sub_to_uo;

Material::Material(unsigned int subdomain) {
  if (!_sub_to_uo[subdomain])
    _sub_to_uo[subdomain] = std::make_unique<UserObject>();
}

int main() { Material mat(0); }
