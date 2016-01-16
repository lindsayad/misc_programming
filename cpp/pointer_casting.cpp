// virtual members
#include <iostream>
#include <memory>
// using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area ()
      { return 0; }
};

class Rectangle: public Polygon {
  public:
    int area ()
      { return width * height; }
};

class Triangle: public Polygon {
  public:
    int area ()
      { return (width * height / 2); }
};

int main () {
  // Rectangle rect;
  // Triangle trgl;
  // Polygon poly;
  // Polygon * ppoly1 = &rect;
  // Polygon * ppoly2 = &trgl;
  // Polygon * ppoly3 = &poly;

    // MooseSharedPointer<BoundaryCondition> bc = MooseSharedNamespace::static_pointer_cast<BoundaryCondition>(_factory.create(bc_name, name, parameters, tid));

  std::shared_ptr<Polygon> poly_wolly = std::static_pointer_cast<Polygon>(std::make_shared<Triangle>());
  std::shared_ptr<Rectangle> rect = std::dynamic_pointer_cast<Rectangle>(poly_wolly);
  std::shared_ptr<Triangle> tri = std::dynamic_pointer_cast<Triangle>(poly_wolly);
  std::shared_ptr<Polygon> poly_wolly_2 = std::dynamic_pointer_cast<Polygon>(poly_wolly);
  if (rect)
    std::cout << "It's a rectangle!" << std::endl;
  if (tri)
    std::cout << "It's a triangle!" << std::endl;
  if (poly_wolly_2)
    std::cout << "It's a polygon!" << std::endl;
  if (!rect && !tri && !poly_wolly_2)
    std::cout << "You're a big screw-up!" << std::endl;

  // ppoly1->set_values (4,5);
  // ppoly2->set_values (4,5);
  // ppoly3->set_values (4,5);
  // cout << ppoly1->area() << '\n';
  // cout << ppoly2->area() << '\n';
  // cout << ppoly3->area() << '\n';
  return 0;
}
