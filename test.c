#include "Ubject.h"

int main() {
  void *ctor_ = ctor;

  void *a = init(Ubject);

  printf("%s\n", className(a));
  printf("%s\n", className(classOf(a)));

  blip((void *)classOf(a));
  blip((void *)classOf(classOf(a)));
  blip(a);

  return 0;
}