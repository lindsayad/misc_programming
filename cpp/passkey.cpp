class Assembly {
public:
  class PassKey {
    friend class SAMNodeFaceConstraint;
    PassKey() = default;
    ~PassKey() = default;
  };

  void JxWNeighbor(PassKey = PassKey()) {}
};

class SAMNodeFaceConstraint {
public:
  void foo() {
    Assembly a;
    a.JxwNeighbor();
  }
};

int main() {
  Assembly a;
  a.JxWNeighbor();
}
