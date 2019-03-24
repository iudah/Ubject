/**
 * @file Set.h
 * @brief The prototype file for ADT set.
 * 
 * This is based on ooc by Axel-Tobias Schreiner.
 * @author Jude
*/
#ifndef SET_H
#define SET_H

/**
 * @brief Represention of ADT Set.
*/
extern const void *Set;

/**
 * @brief Add an element to a set
 * @param set the set of interest
 * @param element an element to be added to set
 * @return added element
*/
void * add(void * set, const void *element);
/**
 * @brief Look up an element in a set
 * @param set the set of interest
 * @param element an element to be looked up
 * @return element if found, NULL otherwise
*/
void * find(const void *set, const void *element);
/**
 * @brief Remove an element from a set
 * @param set the set of interest
 * @param element an element to be removed
 * @return removed element or NULL if element is not found
*/
void * drop(void *set, const void *element);
/**
 * @brief Check an element is in a set
 * @param set the set of interest
 * @param element an element to be checked to set
 * @return 1 if found, 0 otherwise
*/
int contains(const void *set, const void *element);
#endif