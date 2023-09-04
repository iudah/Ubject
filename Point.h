/**
 * @file Point.h
 * @brief Prototype file of Point ADT
 * @author Jude (iudah)
 */
#ifndef POINT_H
#define POINT_H

#include "Ubject.h"

extern const void *Point;

void draw(const void *self);
void move(void *self, int dx, int dy);

extern const void *PointClass;
void initPoint();
#endif
