#include <stdio.h>
#include <stdlib.h>
#include <cxxabi.h>

int
main()
{
  const char * mangled_name = "__ZNK19RankFourTensorTemplIdEmlIiEENSt3__19enable_"
                              "ifIXsr12ScalarTraitsIT_EE5valueES_IDTmlcvd_EcvS4__EEEE4typeERKS4_";
  char * demangled_name;
  int status = -1;
  demangled_name = abi::__cxa_demangle(mangled_name, NULL, NULL, &status);
  printf("Demangled: %s\n", demangled_name);
  free(demangled_name);
  return 0;
}
