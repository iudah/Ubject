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

/**
 * @brief Get the index of the given object in the object table.
 *
 * This function returns the index of the given object in the object table.
 *
 * @param self_ A pointer to the object.
 * @return The index of the object in the object table.
 */
int ubjectIndex(const void *self_);

/**
 * @brief Structure containing function pointers for printing errors and
 * warnings
 *
 */
extern BASEOBJECTAPI const struct Ubject_err_disp__ {
  /**
   * @brief Function pointer for printing an error message
   * Call abort() after printing.
   * @param fmt The format string for the error message
   * @param ... Variable argument to be formatted according to the format string
   */
  void (*error)(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

  /**
   * @brief Function pointer for printing a warning message
   *
   * @param fmt The format string for the warning message
   * @param ... Variable arguments to be formatted according to the formatstring
   */
  void (*warn)(const char *fmt, ...);
} UbjectError;

#endif