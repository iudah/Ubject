/**
 * @file Ubject.h
 * @brief The prototype file for ADT, Ubject.
 *
 * @author Jude (iudah)
 */
#ifndef UBJECT_H
#define UBJECT_H
/**
 * @brief Represention of ADT Ubject.
 */
extern const void *Ubject;

/**
 * @brief Compares ubjects.
 * @param a an ubject
 * @param b an ubject
 * @return 1 if a and b are different, else 0
 */
int differ(const void *a, const void *b);
#endif