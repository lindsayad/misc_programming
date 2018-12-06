template <typename T>
class DualNumberSurrogate;

template <typename T>
void
do_template_stuff(const DualNumberSurrogate<T> &)
{
}

template <typename T>
class DualNumberSurrogate
{
};

int
main()
{
  DualNumberSurrogate<int> dns;
  do_template_stuff(dns);
}
