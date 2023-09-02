/**
 * @file new.h
 * @brief Memory management prototype.
 *
 * @author Jude (iudah)
 */
#ifndef NEW_H
#define NEW_H

/**
 * @brief Allocate ADT instance.
 *
 * @param descriptor descriptor of ADT
 * @param ... extra arguments for instance initialization
 * @return pointer to new ADT instance
 */
void *new(const void *descriptor, ...);

/**
 * @brief Recycle created ADT instance resources.
 *
 * @param self pointer originally produced by new
 */
void delete(void *self);

/**
 * @brief Create copy of an instance.
 *
 * @param self pointer to original instance
 * @return created copy of self
 */
void *clone(const void *self);

/**
 * @brief Compares class instance.
 * @param a a class instance
 * @param b a class instance
 * @return 1 if a and b are different, else 0
 */
int differ(const void *self, const void *b);

/** @brief Get size of created instance
 * @param self pointer to item originally created by @ref new
 * @return size of self
 */
size_t sizeOf(const void *self);
#endif