#include <iostream>
#include <memory>
#include <vector>

class A {
public:
  void foo() {}

  void bar() const {
    auto method_scope = [this]() mutable
      {
        foo();
      };

    method_scope();
  }
};

// Per https://en.cppreference.com/w/cpp/language/lambda there is only ever one
// operator() method defined in a closure. If a lambda is marked as mutable,
// then operator() will be non-const...unless it seems as shown below it doesn't
// capture anything in which case operator() will still be const. If the lambda
// is not marked mutable then operator() is always const

template <typename ActionFunctor, typename DataType>
void push_parallel_packed_range(const ActionFunctor &act_on_data,
                                DataType &data) {
  std::cout << "const overload\n";
  act_on_data(data);
}

/**
 * Require this overload in order to compile
 *
 *     push_parallel_packed_range(mutable_lamb, from);
 *
 * and
 *
 *     push_parallel_packed_range(mutable_ref_captures, from);
 *
 */
template <typename ActionFunctor, typename DataType>
void push_parallel_packed_range(ActionFunctor &act_on_data, DataType &data) {
  std::cout << "non-const overload\n";
  act_on_data(data);
}

int main() {
  std::vector<std::unique_ptr<A>> to, from;
  from.emplace_back(std::make_unique<A>());

  A a, b;
  const A c;

  // Not marked mutable so operator() const is the method created in the closure
  const auto my_lamb = [a, &b, &c, &to](std::vector<std::unique_ptr<A>> &arg) {
    for (auto &value : arg)
      to.emplace_back(std::move(value));

    // Below causes program not to compile
    // Unless the lambda is specified mutable, things captured by copy are
    // const-qualified a.foo();

    b.foo();
    a.bar();

    // Below causes program not to compile.
    // c is const in the lambda enclosing scope
    // c.foo();
  };

  // We can mark this as const and the const ActionFunctor &
  // push_parallel_packed_range overload works fine because even though we've
  // marked this as mutable, we're not capturing any data and so the const operator()
  // method is the one present in the closure
  const auto mutable_no_captures =
      [](std::vector<std::unique_ptr<A>> &arg) mutable {};

  // This produces non-const operator() because it captures and is marked
  // mutable
  auto mutable_ref_captures =
      [&a](std::vector<std::unique_ptr<A>> &arg) mutable {};

  // If the below lambda is marked const, then the const ActionFunctor &
  // push_parallel_packed_range overload is selected and then compilation fails
  // because there is no operator() const method in the closure because we've
  // marked this lambda mutable and we are capturing
  /*const*/ auto mutable_lamb =
      [a](std::vector<std::unique_ptr<A>> &arg) mutable { a.foo(); };

  push_parallel_packed_range(my_lamb, from);
  push_parallel_packed_range(mutable_no_captures, from);
  push_parallel_packed_range(mutable_ref_captures, from);
  push_parallel_packed_range(mutable_lamb, from);

  // A general note: if we didn't mark my_lamb or mutable_lamb_no_captures as
  // const, then the non-const push_parallel_packed_range overload is the
  // overload that gets called, but everything is hunky-dory because even though
  // the lambda closures operator() method is const, non-const objects can of
  // course call const methods
}
