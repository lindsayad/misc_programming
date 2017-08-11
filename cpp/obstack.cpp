#include <obstack.h>
#include <memory>

#define obstack_chunk_alloc malloc
#define obstack_chunk_free free

int main()
{
  struct obstack *myobstack_ptr
    = (struct obstack *) malloc (sizeof (struct obstack));

  obstack_init (myobstack_ptr);

  obstack_free (myobstack_ptr, NULL);
  // free (myobstack_ptr);

  int *i = (int *) malloc (sizeof(int));
}
