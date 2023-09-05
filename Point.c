/**
 * @file Point.c
 * @brief Implementation of Point ADT
 * @author Jude (iudah)
 */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#include "Point.h"
#include "Point.r.h"

static void *Point_ctor(void *self_, va_list *arg)
{
    struct Point *self = super_ctor(Point, self_, arg);

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
void draw(const void *self_)
{
    const struct PointClass *class = classOf(self_);

    assert(class->draw);
    return class->draw(self_);
}
static void *PointClass_ctor(void *self_, va_list *arg)
{
    struct PointClass *self = super_ctor(PointClass, self, arg);
    typedef void (*voidf)();
    voidf selector;
    va_list arg_ = *arg;
    while ((selector = va_arg(arg_, voidf)))
    {
        voidf method = va_arg(arg_, voidf);
        if (selector == (voidf)draw)
            *(voidf *)&self->draw = method;
    }
    return self;
}

const void *Point = 0, *PointClass = 0;

void initPoint()
{
    if (!PointClass)
        PointClass = new (TypeClass, //"PointClass",
                          TypeClass,
                          sizeof(struct PointClass),
                          ctor, PointClass_ctor, 0);
    if (!Point)
        Point = new (PointClass,
                     Ubject, sizeof(struct Point),
                     ctor, Point_ctor,
                     draw, Point_draw, className, "Point",
                     0);
}