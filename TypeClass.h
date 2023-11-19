#ifndef TYPECLASS_H
#define TYPECLASS_H

#ifdef _WIN32

#ifdef TYPECLASS_EXPORTS
#define TYPECLASSAPI __declspec(dllexport)
#else
#define TYPECLASSAPI __declspec(dllimport)
#endif
#define TYPECLASSCALL __cdecl

#else

#define TYPECLASSAPI
#define TYPECLASSCALL

#endif

/**
 * @brief Invoke the destructor of an object.
 *
 * This function invokes the destructor of the object based on its class.
 *
 * @param self_ A pointer to the object.
 * @return A pointer to the object after destruction.
 */
TYPECLASSAPI void *dtor(void *self_);

/**
 * @brief Get the name of class of object.
 *
 * This function returns the name of the class of the given object.
 *
 * @param self_ A pointer to the object.
 * @return The name of the class.
 */
TYPECLASSAPI const char *className(const void *self_);

TYPECLASSAPI const char *descName(const void *class_);
#endif