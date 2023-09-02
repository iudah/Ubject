/**
 * @file Point.c
 * @brief Implementation of Point ADT
 * @author Jude (iudah)
 */
#include <stdarg.h>
#include <stdio.h>

#include "new.h"
#include "new.r.h"

struct Point
{
    const struct Class *class;
    int x, y;
};
static void *Point_ctor(void *self_, va_list *arg)
{
    struct Point *self = self_;

    self->x = va_arg(*arg, int);
    self->y = va_arg(*arg, int);

    return self;
}
static void Point_draw(const void *self_)
{
    const struct Point
        *self = self_;
    printf("\".\" at %d, %d\n", self->x, self->y);
}
void move(void *self_, int dx, int dy)
{
    struct Point *self = self_;
    self->x += dx;
    self->y += dy;
}
static const struct Class Point_ = {
    sizeof(struct Point), Point_ctor, 0, Point_draw};
const void *Point = &Point_;