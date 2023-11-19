#ifndef BASECLASS_H
#define BASECLASS_H

#ifdef _WIN32

#ifdef BASECLASS_EXPORTS
#define BASECLASSAPI __declspec(dllexport)
#else
#define BASECLASSAPI __declspec(dllimport)
#endif
#define BASECLASSCALL __cdecl

#else

#define BASECLASSAPI
#define BASECLASSCALL

#endif

#include <stdarg.h>
#include <stddef.h>

/**
 * @brief Invoke the constructor of an object.
 *
 * This function invokes the constructor of the object based on its class.
 *
 * @param self_ A pointer to the object.
 * @param arg Variable arguments passed to the constructor.
 * @return A pointer to the initialized object.
 */
BASECLASSAPI void *ctor(void *self_, va_list *arg);

/**
 * @brief Get the superclass of a class.
 *
 * This function returns a pointer to the superclass descriptor of the given
 * class.
 *
 * @param class_ A pointer to the class.
 * @return A pointer to the superclass descriptor.
 */
BASECLASSAPI const void *super(const void *class_);

/**
 * @brief Invoke the superclass constructor.
 *
 * This function invokes the superclass constructor.
 *
 * @param class_ Pointer to the class descriptor.
 * @param self Pointer to the object.
 * @param arg_ Variable argument list.
 * @return Pointer to the initialized object.
 */
BASECLASSAPI void *super_ctor(const void *class_, void *self, va_list *arg_);

/**
 * @brief Get the size of an object.
 *
 * This function returns the size of the given object.
 *
 * @param self_ A pointer to the object.
 * @return The size of the object in bytes.
 */
BASECLASSAPI size_t sizeOf(const void *self_);
#endif