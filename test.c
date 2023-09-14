#include "Ubject.h"

int main()
{
    void *ctor_ = ctor;

    void *a = new (Ubject);

    printf("%s\n", className(a));
    printf("%s\n", className(classOf(a)));

    delete ((void *)classOf(a));
    delete ((void *)classOf(classOf(a)));
    delete (a);

    return 0;
}