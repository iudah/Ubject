/**
 * @file any.c
 * @brief Test driver
 */
#include "Ubject.h"
static int Any_differ(const void *self, const void *b)
{
    return 0;
}

int main()
{
    void *o = new (Ubject);
    const void *Any = new (Class, "Any", Ubject, sizeOf(o), differ, Any_differ, 0);
    void *a = new (Any);
    puto(Any, stdout);
    puto(o, stdout);
    puto(a, stdout);

    if (differ(o, o) == differ(a, a))
        puts("OK");
    if (differ(o, a) != differ(a, o))
        puts("NOT COMMUNICATIVE");

    delete (o);
    delete (a);
    delete (Any);

    return 0;
}