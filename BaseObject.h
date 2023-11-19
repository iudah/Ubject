#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#ifdef _WIN32

#ifdef BASEOBJECT_EXPORTS
#define BASEOBJECTAPI __declspec(dllexport)
#else
#define BASEOBJECTAPI __declspec(dllimport)
#endif
#define BASEOBJECTCALL __cdecl

#else

#define BASEOBJECTAPI
#define BASEOBJECTCALL

#endif


/**
 * @brief Allocate and initialize a new object of the given class.
 *
 * This function allocates memory for a new object based on the provided class
 * and initializes it.
 *
 * @param class_ A pointer to the class descriptor.
 * @param ... Variable arguments passed to the object's constructor.
 * @return A pointer to the newly created object.
 */
BASEOBJECTAPI void BASEOBJECTCALL *init(const void *class_, ...);

/**
 * @brief Get the class descriptor of an object.
 *
 * This function returns a pointer to the class descriptor of the given object.
 *
 * @param self_ A pointer to the object.
 * @return A pointer to the class descriptor.
 */
BASEOBJECTAPI const void *classOf(const void *self_);

extern BASEOBJECTAPI const struct Ubject_err_disp__ {
  void (*error)(const char *fmt, ...);
  void (*warn)(const char *fmt, ...);
} UbjectError;

#endif