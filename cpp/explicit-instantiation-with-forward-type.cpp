template <class T>
class A : public T
{
};

int
main()
{
}

class B;
template class A<B>;
