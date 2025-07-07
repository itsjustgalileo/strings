#include <assert.h>

#include <quest/quest_todo.h>

#include "./quest_string.h"

void *my_memchr(const void *str, int c, size_t n) {
    assert(str);
    const int8 *c_str = quest_reinterpret_cast(const int8 *, str);
    size_t i;
    for (i = 0; i < n; ++i) {
        if (c_str[i] == quest_static_cast(int8, c)) {
            return quest_reinterpret_cast(void *, (c_str + i));
        }
    }
    return NULL;
}

int my_memcmp(const void *dst, const void *src, size_t n) {
    assert(dst && src);
    const uint8 *c_dst;
    c_dst = quest_reinterpret_cast(const uint8 *, dst);
    const uint8 *c_src;
    c_src = quest_reinterpret_cast(const uint8 *, src);
    size_t i;
    for (i = 0; i < n; i++) {
        if (c_dst[i] != c_src[i]) {
            break;
        }
    }
    if (i == n) {
        return 0;
    }
    return quest_static_cast(int, c_dst[i]) - quest_static_cast(int, c_src[i]);
}

void *my_memcpy(void *dst, const void *src, size_t n) {
    assert(dst && src);
    size_t s;
    int8 *c_dst = quest_reinterpret_cast(int8 *, dst);
    const int8 *c_src = quest_reinterpret_cast(const int8 *, src);
    for (s = 0; s < n; ++s) {
        c_dst[s] = c_src[s];
    }
    return dst;
}

void *my_memmove(void *dst, const void *src, size_t n) {
    assert(dst && src);
    ssize_t s;
    int8 *c_dst = quest_reinterpret_cast(int8 *, dst);
    int8 *c_src = quest_reinterpret_cast(int8 *, src);
    if (n == 0) {
        return dst;
    }
    if (c_dst < c_src || c_dst >= c_src + n) {
        for (s = 0; s < n; ++s)
            c_dst[s] = c_src[s];
    } else {
        for (s = (ssize_t)n - 1; s >= 0; --s)
            c_dst[s] = c_src[s];
    }
    return dst;    
}

void *my_memset(void *m, int c, size_t n) {
    assert(m);
    uint8 *c_m = quest_reinterpret_cast(uint8 *, m);
    size_t s;
    for (s = 0; s < n; s++) {
        c_m[s] = quest_static_cast(uint8, c);
    }
    return m;
}

char *my_strcpy(char *restrict dst, const char *restrict src) {
    assert(dst && src);
    char *ret = dst;
    while ((*dst++ = *src++));
    return ret;
}

char *my_strncpy(char *restrict dst, const char *restrict src, size_t capacity) {
    assert(dst && src);
    size_t i = 0;
    for (; i < capacity && src[i]; ++i)
        dst[i] = src[i];
    for (; i < capacity; ++i)
        dst[i] = '\0';
    return dst;
}

char *my_strcat(char *restrict dst, const char *restrict src) {
    assert(dst && src);
    char *p = dst;
    while (*p) p++;
    while ((*p++ = *src++));
    return dst;
}

int my_strcmp(const char *restrict str1, const char *restrict str2) {
    assert(str1 && str2);
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return quest_static_cast(int, (uint8)(*str1)) - quest_static_cast(int, (uint8)(*str2));
}

int my_strncmp(const char *restrict str1, const char *restrict str2, size_t n) {
    assert(str1 && str2);
    size_t i;
    for (i = 0; i < n; ++i) {
        if (str1[i] == '\0' || str1[i] != str2[i]) {
            return quest_static_cast(int, (uint8)str1[i]) - quest_static_cast(int, (uint8)str2[i]);            
        }
    }
    return 0;
}

int my_strcoll(const char *restrict str1, const char *restrict str2) {
    assert(str1 && str2);
    quest_todo("Not implemented!");
    return 0;
}

size_t my_strspn(const char *restrict str, const char *restrict accept) {
    assert(str && accept);
    quest_todo("Not implemented!");
    return 0;
}

size_t my_strcspn(const char *restrict str, const char *restrict reject) {
    assert(str && reject);
    quest_todo("Not implemented!");
    return 0;
}

char *my_strerror(int errnum) {
    quest_todo("Not implemented!");
    return NULL;
}

size_t my_strlen(const char *restrict str) {
    assert(str);
    size_t len;
    len = 0;
    for (; str[len] != '\0'; len++);
    return len;
}

char *my_strpbrk(const char *restrict str1, const char *restrict str2) {
    assert(str1 && str2);
    quest_todo("Not implemented!");
    return NULL;
}

char *my_strchr(const char *str, int c) {
    assert(str);
    do {
        if (*str == (char)c)
            return (char *)str;
    } while (*str++);
    return NULL;
}

char *my_strrchr(const char *str, int c) {
    assert(str);
    char *last;
    last = NULL;
    for (; *str; ++i) {
        if (*str == (char)c) {
            last = (char *)str;
        }
        ++str;
    }
    return last;
}

char *my_strstr(const char *haystack, const char *needle) {
    assert(haystack && needle);
    size_t haystack_len = my_strlen(haystack);
    size_t needle_len = my_strlen(needle);
    if (needle_len == 0) {
        return quest_reinterpret_cast(int8 *, (haystack));
    }

    if (needle_len > haystack_len) {
        return NULL;
    }
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {        
        size_t j = 0;
        while (j < needle_len && haystack[i + j] == needle[j]) {
            j++;
        }
        if (j == needle_len) {
            return quest_reinterpret_cast(int8 *, (haystack + i));
        }
    }
    return NULL;
}

char *my_strtok(char *restrict str, const char *restrict delim) {
    assert(str && delim);
    quest_todo("Not implemented!");
    return NULL;
}

size_t my_strxfrm(char *restrict dst, const char *restrict src, size_t n) {
    assert(dst && src);
    quest_todo("Not implemented!");
    return 0;
}

bool string_init(string_t *s, const char *str) {
    assert(s && src);
    return string_clear(s) && string_set(s, str);
}

bool string_clear(string_t *s) {
    assert(s);
    s->len = 0;
    s->str[s->len] = '\0';
    return true;
}

bool string_set(string_t *s, const char *restrict src) {
    assert(s && src);
    size_t len;
    len = my_strlen(src);
    if (len >= QUEST_MAX_STR_LEN) {
        return false;
    }
    if (my_strcpy(s->str, src) == NULL) {
        return false;
    }
    s->len = len;
    return true;
}

bool string_append(string_t *s, const char *restrict fmt) {
    assert(s && fmt);
    size_t len;
    len = my_strlen(fmt);
    if (len + s->len >= QUEST_MAX_STR_LEN) {
        return false;
    }
    if (my_strcat(s->str, fmt) == NULL) {
        return false;
    }
    s->len += len;
    return true;
}

bool string_equals(const string_t *s1, const string_t *s2) {
    assert(s1 && s2);
    return my_strcmp(s1->str, s2->str) == 0;
}
