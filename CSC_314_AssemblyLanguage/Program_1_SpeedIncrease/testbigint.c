#include <bigint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  bigint a;
  bigint b;
  bigint c;
  bigint d;
  char *s;

  printf("using bigint_from_int to create a = 10\n");
  a = bigint_from_int(10);
  s = bigint_to_str(a);
  printf("bigint_to_str: a = %s\n",s);
  free(s);
  printf("bigint_to_int: a = %d\n",bigint_to_int(a));

  printf("using bigint_from_int to create b = 18934004\n");
  b = bigint_from_int(18934004);
  s = bigint_to_str(b);
  printf("bigint_to_str: b = %s\n",s);
  free(s);
  printf("bigint_to_int: b = %d\n",bigint_to_int(b));

    printf("using bigint_from_int to create c = -757593\n");
  c = bigint_from_int(-757593);
  s = bigint_to_str(c);
  printf("bigint_to_str: c = %s\n",s);
  free(s);
  printf("bigint_to_int: c = %d\n",bigint_to_int(c));


  bigint_free(a);
  bigint_free(b);
  bigint_free(c);

  a = bigint_from_str("10");
  s = bigint_to_str(a);
  printf("a = %s\n",s);
  free(s);
  printf("a = %d\n",bigint_to_int(a));

  b = bigint_from_str("18934004");
  s = bigint_to_str(b);
  printf("b = %s\n",s);
  free(s);
  printf("b = %d\n",bigint_to_int(b));

  c = bigint_from_str("-757593");
  s = bigint_to_str(c);
  printf("c = %s\n",s);
  free(s);
  printf("c = %d\n",bigint_to_int(c));

  d = bigint_negate(c);
  s = bigint_to_str(d);
  printf("-c = %s\n",s);
  free(s);
  printf("-c = %d\n",bigint_to_int(d));
  bigint_free(d);

  d = bigint_add(a,b);
  s = bigint_to_str(d);
  printf("a + b = %s\n",s);
  free(s);
  bigint_free(d);

  if(bigint_le(a,b))
    {
      printf("less or equal\n");
    }

  d = bigint_mul(b,c);
  s = bigint_to_str(d);
  printf("c x b = %s\n",s);
  free(s);
  bigint_free(d);

  d = bigint_mul(c,b);
  s = bigint_to_str(d);
  printf("c x b = %s\n",s);
  free(s);
  bigint_free(d);

  d = bigint_div(b,a);
  s = bigint_to_str(d);
  printf("b / a = %s\n",s);
  free(s);
  bigint_free(d);
  
  d = bigint_div(b,c);
  s = bigint_to_str(d);
  printf("b / c = %s\n",s);
  free(s);
  bigint_free(d);
  
  d = bigint_div(c,b);
  s = bigint_to_str(d);
  printf("c / b = %s\n",s);
  free(s);
  bigint_free(d);
  
  
  
  bigint_free(a);
  bigint_free(b);
  bigint_free(c);



  return 0;
}



