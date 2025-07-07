#ifndef QUEST_STRING_H_
#define QUEST_STRING_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern QUEST_API void *QUEST_DECL my_memchr(const void *str, int c, size_t n);
    extern QUEST_API int QUEST_DECL my_memcmp(const void *dst, const void *src, size_t n);
    extern QUEST_API void *QUEST_DECL my_memcpy(void *dst, const void *src, size_t n);
    extern QUEST_API void *QUEST_DECL my_memmove(void *dst, const void *src, size_t n);
    extern QUEST_API void *QUEST_DECL my_memset(void *m, int c, size_t n);
    
    extern QUEST_API char *QUEST_DECL my_strcat(char *restrict dst, const char *restrict src);
    extern QUEST_API char *QUEST_DECL my_strncat(char *restrict dst, const char *restrict src, size_t n);
    extern QUEST_API int QUEST_DECL my_strcmp(const char *restrict str1, const char *restrict str2);
    extern QUEST_API int QUEST_DECL my_strncmp(const char *restrict str1, const char *restrict str2, size_t n);
    extern QUEST_API int QUEST_DECL my_strcoll(const char *restrict str1, const char *restrict str2);
    extern QUEST_API char *QUEST_DECL my_strcpy(char *restrict dst, const char *restrict src);
    extern QUEST_API char *QUEST_DECL my_strncpy(char *restrict dst, const char *restrict src, size_t capacity);
    extern QUEST_API size_t QUEST_DECL my_strspn(const char *restrict str, const char *restrict accept);
    extern QUEST_API size_t QUEST_DECL my_strcspn(const char *restrict str, const char *restrict reject);
    extern QUEST_API char *QUEST_DECL my_strerror(int errnum);
    extern QUEST_API size_t QUEST_DECL my_strlen(const char *restrict str);
    extern QUEST_API char *QUEST_DECL my_strpbrk(const char *restrict str1, const char *restrict str2);
    extern QUEST_API char *QUEST_DECL my_strchr(const char *str, int c);
    extern QUEST_API char *QUEST_DECL my_strrchr(const char *str, int c);
    extern QUEST_API size_t QUEST_DECL my_strspn(const char *restrict str1, const char *restrict str2);
    extern QUEST_API char *QUEST_DECL my_strstr(const char *haystack, const char *needle);
    extern QUEST_API char *QUEST_DECL my_strtok(char *restrict str, const char *restrict delim);
    extern QUEST_API size_t QUEST_DECL my_strxfrm(char *restrict dst, const char *restrict src, size_t n);

#define QUEST_MAX_STR_LEN ((size_t)0x100)
    
    typedef struct {
        char str[QUEST_MAX_STR_LEN];
        size_t len;
    } string_t;

    extern QUEST_API bool QUEST_DECL string_init(string_t *s, const char *str);
    extern QUEST_API bool QUEST_DECL string_clear(string_t *s);
    extern QUEST_API bool QUEST_DECL string_set(string_t *s, const char *restrict src);
    extern QUEST_API bool QUEST_DECL string_append(string_t *s, const char *restrict fmt);
    extern QUEST_API bool QUEST_DECL string_equals(const string_t *s1, const string_t *s2);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <quest/quest_footer.h>

#endif /* QUEST_STRING_H_ */
