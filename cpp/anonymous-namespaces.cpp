namespace {

void foo();

}

void bar() { foo(); }

namespace {

void foo() {}

} // namespace

int main() { bar(); }
