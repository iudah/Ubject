#include "Ubject.h"

int main()
{
    void *a = new (Ubject);

    printf("%s\n", className(a));
    printf("%s\n", className(classOf(a)));

    delete ((void *)classOf(a));
    delete ((void *)classOf(classOf(a)));
    delete (a);

    return 0;
}