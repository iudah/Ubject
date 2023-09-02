/**
 * @file main.c
 * @brief An application implementation.
 *
 * This  file is an implementation file for an application
 * that makes use of the ADTs.
 * @author Jude (iudah)
 */
#include <stdio.h>

#include "String.h"
#include "new.h"

int main()
{
    void *a = new (String, "Text A");
    void *a_copy = clone(a);
    void *b = new (String, "Text b");

    printf("size of 'a' == %u\n", sizeOf(a));
    if (differ(a, b))
        puts("OK");
    if (differ(a, a_copy))
        puts("differ?");
    if (a == a_copy)
        puts("clone?");

    delete (a);
    delete (a_copy);
    delete (b);

    return 0;
}