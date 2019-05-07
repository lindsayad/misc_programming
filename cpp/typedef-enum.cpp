enum class ElementType
{
  Element,
  Neighbor,
  Lower
};

typedef ElementType MortarType;
// Below doesn't compile
// typedef ElementType::Element MortarType::Slave;

int
main()
{
}
