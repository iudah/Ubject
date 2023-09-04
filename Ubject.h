/**
 * @file Ubject.h
 * @brief Ubject interface
 */
#ifndef UBJECT_H
#define UBJECT_H

#include <stdio.h>

void *new(const void *class, ...);
void delete(void *self);

/**@brief Ubject descriptor */
extern const void *Ubject;

void *ctor(void *self_, va_list *arg);
void *dtor(void *self_);
int differ(const void *self, const void *b);
int puto(const void *self, FILE *f);

const void *classOf(const void *self_);

/** @brief Class descriptor*/
extern const void *Class;
size_t sizeOf(const void *self_);
const void *super(const void *self_);

#endif