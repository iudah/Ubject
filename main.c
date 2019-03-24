/**
 * @file main.c
 * @brief An application implementation.
 *
 * This  file is an implementation file for an application
 * that makes use of the ADTs.
 * @author Jude (iudah)
 */
#include <stdio.h>

#include "new.h"
#include "Ubject.h"
#include "Set.h"

int main()
{
    void *set = new (Set);

    void *a = add(set, new (Ubject));
    void *b = add(set, new (Ubject));
    void *c = new (Ubject);

    if (contains(set, a) && contains(set, b))
        puts("OK");
    if (contains(set, c))
        puts("OK");
    if (differ(a, add(set, a)))
        puts("differ?");
    if (contains(set, drop(set, a)))
        puts("drop?");

    delete (drop(set, b));
    delete (drop(set, c));

    return 0;
}