/**
 * @file any.c
 * @brief Test driver
 */
#include "Point.h"
#include "Circle.h"

char seq_[] = " p c";
char *seq = seq_;

int main()
{
    initCircle();

    void *pt;
    while (*++seq)
    {
        switch (*seq)
        {
        case 'p':
            pt = new (Point, 1, 2);
            break;
        case 'c':
            pt = new (Circle, 1, 2, 3);
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