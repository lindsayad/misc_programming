#include <map>


class FieldBase { };

template <typename T>
class Field : public FieldBase {
  private:
    T value;
    int type;
};

class Row {
  private:
    std::map<unsigned long,FieldBase*> column;
};
