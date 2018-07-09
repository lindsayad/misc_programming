#include <string>

enum Type {Bool, Int};

template<typename T>
T return_things(Type t)
{
  if (t == Bool)
    return true;
  else
    return "shut_up";
}


int main()
{
  bool b = return_things<bool>(Bool);
  std::string s = return_things<std::string>(Int);
}
