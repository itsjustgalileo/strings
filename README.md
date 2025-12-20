# STRINGS

---

## PRESENTATION

String View and String Builder implementation in C.

---

## PREREQUISITES

- C99 compiler.

---

## EXAMPLE

```c
#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

int main(void) {
    // --- StringView Examples ---
    printf("=== StringView Demo ===\n");

    StringView sv;
    string_view_from_cstr(&sv, "   Hello, C World!   ");
    printf("Original: '%.*s'\n", (int)sv.len, sv.str);

    string_view_trim(&sv);
    printf("Trimmed:  '%.*s'\n", (int)sv.len, sv.str);

    // Slice the first 5 characters
    StringView slice;
    if (string_view_slice(&sv, 0, 5, &slice)) {
        printf("Slice (first 5): '%.*s'\n", (int)slice.len, slice.str);
    }

    // Check starts_with and ends_with
    printf("Starts with 'Hello': %s\n",
           string_view_starts_with(&sv, "Hello") ? "yes" : "no");
    printf("Ends with 'World!': %s\n",
           string_view_ends_with(&sv, "World!") ? "yes" : "no");

    // Find a character
    size_t idx;
    if (string_view_find(&sv, 'C', &idx)) {
        printf("Character 'C' found at index %zu\n", idx);
    }

    // --- StringBuilder Examples ---
    printf("\n=== StringBuilder Demo ===\n");

    StringBuilder sb = {0}; // zero-initialize
    if (!string_builder_append_cstr(&sb, "Hello")) return 1;
    if (!string_builder_append_char(&sb, ',')) return 1;
    if (!string_builder_append_cstr(&sb, " StringBuilder!")) return 1;
    printf("Built string: '%s'\n", sb.data);

    // Append a StringView
    string_view_from_cstr(&slice, " Appending via slice.");
    string_builder_append_view(&sb, &slice);
    printf("After appending slice: '%s'\n", sb.data);

    // Clear the builder
    string_builder_clear(&sb);
    printf("After clearing: '%s'\n", sb.data);

    // --- Read entire file ---
    const char *demo_file = "demo.txt";
    FILE *fp = fopen(demo_file, "w");
    if (fp) {
        fputs("This is a demo file.\nIt has multiple lines.\n", fp);
        fclose(fp);
    }

    if (string_builder_read_entire_file(&sb, demo_file)) {
        printf("\nContents of '%s':\n%s\n", demo_file, sb.data);
    } else {
        printf("Failed to read file '%s'\n", demo_file);
    }

    // Clean up
    free(sb.data);
    remove(demo_file); // clean demo file

    return 0;
}
```

---
