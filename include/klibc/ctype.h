#ifndef CTYPE_H
#define CTYPE_H

#include <klibc/stdbool.h>

/**
 * @brief Checks if the character is alphanumeric.
 * @param c The character to check.
 * @return true if c is a digit or a letter, false otherwise.
 */
bool isalnum(char c);

/**
 * @brief Checks if the character is alphabetic.
 * @param c The character to check.
 * @return true if c is a letter (A-Z or a-z), false otherwise.
 */
bool isalpha(char c);

/**
 * @brief Checks if the character is a blank character (space or tab).
 * @param c The character to check.
 * @return true if c is ' ' or '\t', false otherwise.
 */
bool isblank(char c);

/**
 * @brief Checks if the character is a control character.
 * @param c The character to check.
 * @return true if c is a non-printing control character, false otherwise.
 */
bool iscntrl(char c);

/**
 * @brief Checks if the character is a decimal digit.
 * @param c The character to check.
 * @return true if c is between '0' and '9', false otherwise.
 */
bool isdigit(char c);

/**
 * @brief Checks if the character has a graphical representation.
 * @param c The character to check.
 * @return true if c is any printable character except space, false otherwise.
 */
bool isgraph(char c);

/**
 * @brief Checks if the character is a lowercase letter.
 * @param c The character to check.
 * @return true if c is between 'a' and 'z', false otherwise.
 */
bool islower(char c);

/**
 * @brief Checks if the character is printable.
 * @param c The character to check.
 * @return true if c is any character that occupies printing space (including ' '), false otherwise.
 */
bool isprint(char c);

/**
 * @brief Checks if the character is a punctuation mark.
 * @param c The character to check.
 * @return true if c is a graphic character that is not alphanumeric, false otherwise.
 */
bool ispunct(char c);

/**
 * @brief Checks if the character is a white-space character.
 * @param c The character to check.
 * @return true if c is ' ', '\t', '\n', '\v', '\f', or '\r', false otherwise.
 */
bool isspace(char c);

/**
 * @brief Checks if the character is an uppercase letter.
 * @param c The character to check.
 * @return true if c is between 'A' and 'Z', false otherwise.
 */
bool isupper(char c);

/**
 * @brief Checks if the character is a hexadecimal digit.
 * @param c The character to check.
 * @return true if c is 0-9, a-f, or A-F, false otherwise.
 */
bool isxdigit(char c);

/**
 * @brief Converts an uppercase letter to lowercase.
 * @param c The character to convert.
 * @return The lowercase equivalent if c was uppercase, otherwise returns c unchanged.
 */
char tolower(char c);

/**
 * @brief Converts a lowercase letter to uppercase.
 * @param c The character to convert.
 * @return The uppercase equivalent if c was lowercase, otherwise returns c unchanged.
 */
char toupper(char c);

#endif