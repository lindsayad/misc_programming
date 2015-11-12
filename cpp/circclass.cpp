#include <iostream>
using namespace std;

class FEProblem {
public:
  FEProblem(double r);
  FEProblem();

  bool boundaryRestricted() { return _boundary_restricted; }
  double getRadius() { return _radius; }
  void setRadius(double r) { _radius = r; }

protected:
  bool _boundary_restricted = false;

private:
  double _radius;
};

FEProblem::FEProblem(double r):
  _radius(r),
  _boundary_restricted(true) {}

FEProblem::FEProblem() {}

class BoundaryRestrictable {
public:
  BoundaryRestrictable(FEProblem fe_problem);
  double getActiveRadius() { return _active_radius; }

private:
  double _active_radius;
};

BoundaryRestrictable::BoundaryRestrictable(FEProblem fe_problem) :
  _active_radius(fe_problem.getRadius()) {}

int main () {
  FEProblem qip;
  qip.setRadius(1.0);
  BoundaryRestrictable br (qip);
  cout << "Active radius is " << br.getActiveRadius() << endl;
  qip.setRadius(2.0);
  cout << "Active radius is " << br.getActiveRadius() << endl;
  BoundaryRestrictable brnew (qip);
  cout << "Active radius is " << brnew.getActiveRadius() << endl;

  // FEProblem * pointQip = &qip;

  // cout << "Radius equals " << pointQip->getRadius() << endl;
  // if (!pointQip->boundaryRestricted()) {
  //   cout << "Boundary restrictable? " << pointQip->boundaryRestricted() << endl;
  //   cout << "Entered if statement." << endl;
  // }
  // else {
  //   cout << "Boundary restrictable? " << pointQip->boundaryRestricted() << endl;
  //   cout << "Entered else statement." << endl;
  // }

  return 0;
}
