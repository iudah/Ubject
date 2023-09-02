/**
 * @file main.c
 * @brief An application implementation.
 *
 * This  file is an implementation file for an application
 * that makes use of the ADTs.
 * @author Jude (iudah)
 */
#include <stdio.h>

#include "Point.h"
#include "new.h"

char seq_[] = " p";
char *seq = seq_;

int main()
{
    void *pt;
    while (*++seq)
    {
        switch (*seq)
        {
        case 'p':
            pt = new (Point, 1, 2);
            break;
        default:
            continue;
        }
        draw(pt);
        move(pt, 10, 25);
        draw(pt);
        delete (pt);
    }
    return 0;
}