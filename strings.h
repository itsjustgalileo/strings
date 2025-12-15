#ifndef STRINGS_H_
#define STRINGS_H_ 1

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const char *str;
    size_t len;
} StringView;

bool string_view_from_cstr(StringView *sv, const char *str);
bool string_view_from_range(StringView *sv, const char *str, size_t len);
bool string_view_from_span(StringView *sv, const char *start, const char *end);

bool string_view_equals(const StringView *a, const StringView *b);
bool string_view_slice(const StringView *sv, size_t start, size_t end, StringView *out);

bool string_view_starts_with(const StringView *sv, const char *prefix);
bool string_view_ends_with(const StringView *sv, const char *suffix);

bool string_view_find(const StringView *sv, char c, size_t *index);

bool string_view_trim_left(StringView *sv);
bool string_view_trim_right(StringView *sv);
bool string_view_trim(StringView *sv);

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuilder;
    
void string_builder_clear(StringBuilder *sb);

bool string_builder_append_char(StringBuilder *sb, char c);
bool string_builder_append_cstr(StringBuilder *sb, const char *str);
bool string_builder_append_view(StringBuilder *sb, const StringView *sv);

#endif /* STRINGS_H_ */
