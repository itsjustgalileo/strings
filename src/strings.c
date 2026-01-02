#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "strings/strings.h"

/***************
 * STRING VIEW *
 ***************/

StringView string_view_from_cstr(const char *str)
{
    StringView sv = {0};

    if (NULL == str) {
        return sv;
    }

    sv.str = str;
    sv.len = strlen(str);
    return sv;
}

StringView string_view_from_range(const char *str, size_t len)
{
    StringView sv = {0};

    if (NULL == str) {
        return sv;
    }

    sv.str = str;
    sv.len = (size_t) len;
    return sv;
}

StringView string_view_from_span(const char *start, const char *end)
{
    StringView sv = {0};
    
    if (NULL == start || NULL == end) {
        return sv;
    }

    if (start > end) {
        return sv;
    }

    sv.str = start;
    sv.len = (size_t)(end - start);
    return sv;
}

bool string_view_equals(const StringView *a, const StringView *b)
{
    if (NULL == a || NULL == b) {
        return false;
    }

    if (a->len != b->len) {
        return false;
    }
    return strncmp(a->str, b->str, a->len) == 0;
}

StringView string_view_slice(const StringView *sv, size_t start, size_t end)
{
    StringView out = {0};

    if (NULL == sv) {
        return out;
    }

    if (start > end || end > sv->len) {
        return out;
    }

    out.str = sv->str + start;
    out.len = end - start;
    return out;
}

bool string_view_starts_with(const StringView *sv, const char *prefix)
{
    if (NULL == sv || NULL == prefix) {
        return false;
    }

    size_t prefix_len = strlen(prefix);
    if (sv->len < prefix_len) {        
        return false;
    }
    return memcmp(sv->str, prefix, prefix_len) == 0;    
}

bool string_view_ends_with(const StringView *sv, const char *suffix)
{
    if (NULL == sv || NULL == suffix) {
        return false;
    }
    
    size_t suffix_len = strlen(suffix);
    if (suffix_len > sv->len) {        
        return false;
    }
    return strncmp(sv->str + (sv->len - suffix_len), suffix, suffix_len) == 0;
}

bool string_view_find(const StringView *sv, char c, size_t *index)
{
    if (NULL == sv || NULL == index) {
        return false;
    }
    
    for (*index = 0; *index < sv->len; ++(*index)) {
        if (sv->str[*index] == c) {
            return true;
        }
    }
    return false;
}

bool string_view_trim_left(StringView *sv)
{
    if (NULL == sv) {
        return false;
    }
    
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
    if (NULL == sv) {
        return false;
    }
    
    while (sv->len > 0 && isspace((unsigned char)sv->str[sv->len - 1])) {
        sv->len--;
    }
    return true;
}

bool string_view_trim(StringView *sv)
{
    if(NULL == sv) {
        return false;
    }
    
    return string_view_trim_left(sv) && string_view_trim_right(sv);
}

/******************
 * STRING BUILDER *
 ******************/

void string_builder_clear(StringBuilder *sb)
{
    if (NULL == sb) {
        return;
    }

    sb->length = 0;
    return;
}

void string_builder_free(StringBuilder *sb)
{
    if (NULL == sb) {
        return;
    }

    free(sb->data);
    return;
}

static bool string_builder_ensure_capacity(StringBuilder *sb, size_t needed)
{
    if (NULL == sb) {
        return false;
    }
    
    if (needed <= sb->capacity) {
        return true;
    }

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
    if (NULL == sb) {
        return false;
    }

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
    if (NULL == sb || NULL == str) {
        return false;
    }

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
    if (NULL == sb || NULL == sv) {
        return false;
    }
    
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
    if (NULL == sb || NULL == filepath) {
        return false;
    }


    FILE *fp = fopen(filepath, "rb");
    if (NULL == fp) {
        return false;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return false;
    }

    long file_size = ftell(fp);
    if (file_size < 0) {
        fclose(fp);
        return false;
    }

    rewind(fp);

    size_t len = (size_t)file_size;

    if (!string_builder_ensure_capacity(sb, sb->length + len + 1)) {
        fclose(fp);
        return false;
    }

    size_t read = fread(sb->data + sb->length, 1, len, fp);
    if (read != len) {
        fclose(fp);
        return false;
    }

    sb->length += len;
    sb->data[sb->length] = '\0';

    fclose(fp);
    return true;
}
