#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "./strings.h"

/***************
 * STRING VIEW *
 ***************/

bool string_view_from_cstr(StringView *sv, const char *str)
{
    assert(sv && str);
    sv->str = str;
    sv->len = strlen(str);
    return true;
}

bool string_view_from_range(StringView *sv, const char *str, size_t len)
{
    assert(sv && str);
    sv->str = str;
    sv->len = (size_t) len;
    return true;
}

bool string_view_from_span(StringView *sv, const char *start, const char *end)
{
    assert(sv && start && end);
    if (start > end) {
        return false;
    }
    sv->str = start;
    sv->len = (size_t)(end - start);
    return true;
}

bool string_view_equals(const StringView *a, const StringView *b)
{
    assert(a && b);
    if (a->len != b->len) {
        return false;
    }
    return strncmp(a->str, b->str, a->len) == 0;
}

bool string_view_slice(const StringView *sv, size_t start, size_t end, StringView *out)
{
    assert(sv && out);
    if (start > end || end > sv->len) return false;
    out->str = sv->str + start;
    out->len = end - start;
    return true;
}

bool string_view_starts_with(const StringView *sv, const char *prefix)
{
    assert(sv && prefix);
    size_t prefix_len = strlen(prefix);
    if (sv->len < prefix_len) {        
        return false;
    }
    return memcmp(sv->str, prefix, prefix_len) == 0;    
}

bool string_view_ends_with(const StringView *sv, const char *suffix)
{
    assert(sv && suffix);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > sv->len) {        
        return false;
    }
    return strncmp(sv->str + (sv->len - suffix_len), suffix, suffix_len) == 0;
}

bool string_view_find(const StringView *sv, char c, size_t *index)
{
    assert(sv && index);
    for (*index = 0; *index < sv->len; ++(*index)) {
        if (sv->str[*index] == c) {
            return true;
        }
    }
    return false;
}

bool string_view_trim_left(StringView *sv)
{
    assert(sv);
    size_t i = 0;
    while (i < sv->len && isspace((unsigned char)sv->str[i])) {
        i++;
    }
    sv->str += i;
    sv->len -= i;
    return true;
}

bool string_view_trim_right(StringView *sv)
{
    assert(sv);
    while (sv->len > 0 && isspace((unsigned char)sv->str[sv->len - 1])) {
        sv->len--;
    }
    return true;
}

bool string_view_trim(StringView *sv)
{
    assert(sv);
    return string_view_trim_left(sv) && string_view_trim_right(sv);
}

/******************
 * STRING BUILDER *
 ******************/

void string_builder_clear(StringBuilder *sb)
{
    assert(sb);
    sb->length = 0;
    return;
}

static bool string_builder_ensure_capacity(StringBuilder *sb, size_t needed)
{
    assert(sb);
    if (needed <= sb->capacity) return true;

    size_t new_capacity = sb->capacity ? sb->capacity * 2 : 16;
    while (new_capacity < needed) {
        new_capacity *= 2;
    }

    char *new_data = realloc(sb->data, new_capacity);
    if (!new_data) {
        return false;
    }

    sb->data = new_data;
    sb->capacity = new_capacity;
    return true;
}

bool string_builder_append_char(StringBuilder *sb, char c)
{
    assert(sb);
    if (!string_builder_ensure_capacity(sb, sb->length + 2)) {
        return false;
    }

    sb->data[sb->length] = c;
    sb->length++;
    sb->data[sb->length] = '\0';
    return true;
}

bool string_builder_append_cstr(StringBuilder *sb, const char *str)
{
    assert(sb && str);
    size_t str_len = strlen(str);
    if (!string_builder_ensure_capacity(sb, sb->length + str_len + 1)) {
        return false;
    }
    memcpy(sb->data + sb->length, str, str_len);
    sb->length += str_len;
    sb->data[sb->length] = '\0';
    return true;
}

bool string_builder_append_view(StringBuilder *sb, const StringView *sv)
{
    assert(sb && sv);
    if (!string_builder_ensure_capacity(sb, sb->length + sv->len + 1)) {
        return false;
    }
    memcpy(sb->data + sb->length, sv->str, sv->len);
    sb->length += sv->len;
    sb->data[sb->length] = '\0';
    return true;
}

bool string_builder_read_entire_file(StringBuilder *sb, const char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (NULL == fp) {
        return false;  
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    if (len <= 0) {
        fclose(fp);
        return false;
    }

    char *buffer = malloc(len + 1);
    if (NULL == buffer) {
        fclose(fp);
        return false;
    }

    fread(buffer, 1, len, fp);
    buffer[len] = '\0';

    bool ok = string_builder_append_cstr(sb, buffer);
    if (!ok) {
        free(buffer);
        fclose(fp);
        return false;
    }
    
    free(buffer);
    fclose(fp);

    return ok;
}
