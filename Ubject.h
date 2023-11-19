/**
 * @file Ubject.h
 * @brief Ubject interface
 */
#ifndef UBJECT_H
#define UBJECT_H

#ifdef _WIN32

#ifdef UBJECT_EXPORTS
#define UBJECTAPI __declspec(dllexport)
#else
#define UBJECTAPI __declspec(dllimport)
#endif
#define UBJECTCALL __cdecl

#else

#define UBJECTAPI
#define UBJECTCALL

#endif

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "BaseClass.h"
#include "BaseObject.h"
#include "TypeClass.h"

/**@brief Ubject descriptor */
extern UBJECTAPI const void *Ubject;

/**
 * @brief Free the memory associated with an object.
 *
 * This function deallocates the memory occupied by an object and invokes its
 * destructor if defined.
 *
 * @param self_ A pointer to the object to be deleted.
 */
UBJECTAPI void blip(void *self);

/**
 * @brief Increment reference count of object.
 *
 * This function increments the reference counter of the given object.
 *
 * @param self_ A pointer to the object.
 * @return Current number of references made.
 */
UBJECTAPI const int reference(void *self_);
UBJECTAPI const int getReference(void *self_);

/**
 * @brief Check if two objects are different.
 *
 * This function compares two objects and returns 1 if they are different, 0 if
 * they are the same.
 *
 * @param self_ A pointer to the first object.
 * @param b A pointer to the second object.
 * @return 1 if different, 0 if the same.
 */
UBJECTAPI int differ(const void *self, const void *b);

/**
 * @brief Print the object's representation to a file.
 *
 * This function prints the object's representation to the specified file.
 *
 * @param self_ A pointer to the object.
 * @param f The file stream to write to.
 * @return The number of characters written to the file.
 */
UBJECTAPI int puto(const void *self, FILE *f);

#endif