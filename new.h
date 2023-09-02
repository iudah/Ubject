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
 * @brief Display an instance.
 *
 * @param self pointer to original instance
 */
void draw(const void *self);
#endif