/**
 * @file Ubject.h
 * @brief Ubject interface
 */
#ifndef UBJECT_H
#define UBJECT_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

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
void *new(const void *class, ...);

/**
 * @brief Free the memory associated with an object.
 *
 * This function deallocates the memory occupied by an object and invokes its
 * destructor if defined.
 *
 * @param self_ A pointer to the object to be deleted.
 */
void delete(void *self);

/**@brief Ubject descriptor */
extern const void *Ubject;

/**
 * @brief Invoke the constructor of an object.
 *
 * This function invokes the constructor of the object based on its class.
 *
 * @param self_ A pointer to the object.
 * @param arg Variable arguments passed to the constructor.
 * @return A pointer to the initialized object.
 */
void *ctor(void *self_, va_list *arg);

/**
 * @brief Invoke the destructor of an object.
 *
 * This function invokes the destructor of the object based on its class.
 *
 * @param self_ A pointer to the object.
 * @return A pointer to the object after destruction.
 */
void *dtor(void *self_);

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
int differ(const void *self, const void *b);

/**
 * @brief Print the object's representation to a file.
 *
 * This function prints the object's representation to the specified file.
 *
 * @param self_ A pointer to the object.
 * @param f The file stream to write to.
 * @return The number of characters written to the file.
 */
int puto(const void *self, FILE *f);

/**
 * @brief Get the class descriptor of an object.
 *
 * This function returns a pointer to the class descriptor of the given object.
 *
 * @param self_ A pointer to the object.
 * @return A pointer to the class descriptor.
 */
const void *classOf(const void *self_);

/**
 * @brief Get the name of class of object.
 *
 * This function returns the name of the class of the given object.
 *
 * @param self_ A pointer to the object.
 * @return The name of the class.
 */
const char *className(const void *self_);
const char *descName(const void *class_);
/**
 * @brief Get the size of an object.
 *
 * This function returns the size of the given object.
 *
 * @param self_ A pointer to the object.
 * @return The size of the object in bytes.
 */
size_t sizeOf(const void *self_);

/**
 * @brief Get the superclass of a class.
 *
 * This function returns a pointer to the superclass descriptor of the given class.
 *
 * @param self_ A pointer to the class.
 * @return A pointer to the superclass descriptor.
 */
const void *super(const void *self_);

#endif