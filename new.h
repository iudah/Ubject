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
 * @param descriptor discriptor of ADT
 * @param ... extra arguments for instance initialization
 * @return pointer to new ADT instance
*/
void *new(const void *descriptor, ...);

/**
 * @brief Recycle created ADT instance resources.
 * 
 * @param item pointer orighinally produced by new
*/
void delete(void *item);
#endif