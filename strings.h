#ifndef STRINGS_H_
#define STRINGS_H_ 1

#include <stdlib.h>
#include <stdbool.h>

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Non-owning view into a string.
     *
     * Holds a pointer to a character array and its length. Does not manage memory.
     */
    typedef struct {
        const char *str; /**< Pointer to the first character of the string */
        size_t len;      /**< Length of the string in bytes */
    } StringView;

    /**
     * @brief Initialize a StringView from a null-terminated C string.
     *
     * @param sv Pointer to the StringView to initialize.
     * @param str Null-terminated C string.
     *
     * @return true on success, false on failure.
     */
    extern bool string_view_from_cstr(StringView *sv, const char *str);

    /**
     * @brief Initialize a StringView from a character array and length.
     *
     * @param sv Pointer to the StringView to initialize.
     * @param str Pointer to the start of the string.
     * @param len Length of the string.
     *
     * @return true on success, false on failure.
     */
    extern bool string_view_from_range(StringView *sv, const char *str, size_t len);

    /**
     * @brief Initialize a StringView from a start and end pointer.
     *
     * @param sv Pointer to the StringView to initialize.
     * @param start Pointer to the first character.
     * @param end Pointer to one past the last character.
     *
     * @return true on success, false if start > end.
     */
    extern bool string_view_from_span(StringView *sv, const char *start, const char *end);

    /**
     * @brief Check if two StringViews are equal.
     *
     * @param a Pointer to the first StringView.
     * @param b Pointer to the second StringView.
     *
     * @return true if both StringViews have the same length and contents.
     */
    extern bool string_view_equals(const StringView *a, const StringView *b);

    /**
     * @brief Slice a StringView.
     *
     * @param sv Input StringView.
     * @param start Start index (inclusive).
     * @param end End index (exclusive).
     * @param out Pointer to the output StringView.
     *
     * @return true on success, false if indices are invalid.
     */
    extern bool string_view_slice(const StringView *sv, size_t start, size_t end, StringView *out);

    /**
     * @brief Check if a StringView starts with a given prefix.
     *
     * @param sv Input StringView.
     * @param prefix Null-terminated C string prefix.
     *
     * @return true if sv starts with prefix.
     */
    extern bool string_view_starts_with(const StringView *sv, const char *prefix);

    /**
     * @brief Check if a StringView ends with a given suffix.
     *
     * @param sv Input StringView.
     * @param suffix Null-terminated C string suffix.
     *
     * @return true if sv ends with suffix.
     */
    extern bool string_view_ends_with(const StringView *sv, const char *suffix);

    /**
     * @brief Find a character in a StringView.
     *
     * @param sv Input StringView.
     * @param c Character to search for.
     * @param index Pointer to store the index of the first occurrence.
     *
     * @return true if the character was found, false otherwise.
     */
    extern bool string_view_find(const StringView *sv, char c, size_t *index);

    /**
     * @brief Trim leading whitespace from a StringView.
     *
     * @param sv Pointer to the StringView to trim.
     *
     * @return true on success.
     */
    extern bool string_view_trim_left(StringView *sv);

    /**
     * @brief Trim trailing whitespace from a StringView.
     *
     * @param sv Pointer to the StringView to trim.
     *
     * @return true on success.
     */
    extern bool string_view_trim_right(StringView *sv);

    /**
     * @brief Trim leading and trailing whitespace from a StringView.
     *
     * @param sv Pointer to the StringView to trim.
     *
     * @return true on success.
     */
    extern bool string_view_trim(StringView *sv);

    /**
     * @brief Dynamically sized string builder.
     *
     * Manages a buffer with length and capacity. Can append characters, C strings, and StringViews.
     */
    typedef struct {
        char *data;      /**< Pointer to the buffer */
        size_t length;   /**< Current length of the string */
        size_t capacity; /**< Total allocated capacity */
    } StringBuilder;
    
    /**
     * @brief Clear the StringBuilder without freeing memory.
     *
     * @param sb Pointer to the StringBuilder to clear.
     */
    void string_builder_clear(StringBuilder *sb);

    /**
     * @brief Append a single character to the StringBuilder.
     *
     * @param sb Pointer to the StringBuilder.
     * @param c Character to append.
     *
     * @return true on success, false on allocation failure.
     */
    extern bool string_builder_append_char(StringBuilder *sb, char c);

    /**
     * @brief Append a null-terminated C string to the StringBuilder.
     *
     * @param sb Pointer to the StringBuilder.
     * @param str Null-terminated C string.
     *
     * @return true on success, false on allocation failure.
     */
    extern bool string_builder_append_cstr(StringBuilder *sb, const char *str);

    /**
     * @brief Append a StringView to the StringBuilder.
     *
     * @param sb Pointer to the StringBuilder.
     * @param sv StringView to append.
     *
     * @return true on success, false on allocation failure.
     */
    extern bool string_builder_append_view(StringBuilder *sb, const StringView *sv);

    /**
     * @brief Read an entire file into the StringBuilder.
     *
     * @param sb Pointer to the StringBuilder.
     * @param filepath Path to the file to read.
     *
     * @return true on success, false on failure.
     */
    extern bool string_builder_read_entire_file(StringBuilder *sb, const char *filepath);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* STRINGS_H_ */
