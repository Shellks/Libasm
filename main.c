#include <stdio.h>  // printf
#include <unistd.h> // write, read
#include <errno.h>  // errno
#include <string.h> // compare with original functions
#include <stdlib.h> // malloc, free

// Color codes for terminal output
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define PURPLE  "\033[0;35m"
#define CYAN    "\033[0;36m"
#define RESET   "\033[0m"

// ASM functions prototypes
size_t  ft_strlen(const char *s); 
char    *ft_strdup(const char *s);
char    *ft_strcpy(char *dst, const char *src);
ssize_t ft_read(int fd, void *buf, size_t count);
int     ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
// __attribute__((nonnull(1)))


// Function prototypes for tests
void test_ft_strlen(void);
void test_ft_strcpy(void);
void test_ft_strcmp(void);
void test_ft_write(void);
void test_ft_read(void);
void test_ft_strdup(void);

// Main function to run all tests
int main(void) {
    printf(PURPLE "\n======== LIBASM TESTS ========\n\n" RESET);

    test_ft_strlen();
    test_ft_strcpy();
    test_ft_strcmp();
    test_ft_write();
    test_ft_read();
    test_ft_strdup();

    printf(PURPLE "======== END OF TESTS ========\n\n" RESET);
    return 0;
}


// Test functions implementations
void test_ft_strlen(void) {
    printf(PURPLE "=== TESTING ft_strlen ===\n\n" RESET);
    const char *tests[] = {
        "",
        "a",
        "Hello World!",
        "This is a longer string with spaces.",
        "1234567890",
    };

    for (int i = 0; i < (int)(sizeof(tests)/sizeof(*tests)); i++) {
        size_t my_result = ft_strlen(tests[i]);
        size_t og_result = strlen(tests[i]);
        printf(CYAN"Test \"%s\" -> "RESET, tests[i]);
        printf(YELLOW"ft_strlen = %lu | strlen = %lu -> %s\n"RESET, my_result, og_result, (my_result == og_result) ? GREEN "OK" RESET : RED "FAIL" RESET);
    }
    printf("\n");
}

void test_ft_strcpy(void) {
    printf(PURPLE "=== TESTING ft_strcpy ===\n\n" RESET);

    const char *srcs[] = {
        "",
        "a",
        "Hello",
        "Copy this string",
        "1234567890",
    };

    char dest[100];
    for (int i = 0; i < (int)(sizeof(srcs)/sizeof(*srcs)); i++) {
        ft_strcpy(dest, srcs[i]);
        int cmp = strcmp(dest, srcs[i]);
        printf(CYAN"Copy \"%s\" -> "RESET, srcs[i]);
        printf(YELLOW"Result \"%s\" -> %s\n"RESET, dest, (cmp == 0) ? GREEN "OK" RESET : RED "FAIL" RESET);
    }
    printf("\n");
}

void test_ft_strcmp(void) {
    printf(PURPLE "=== TESTING ft_strcmp ===\n\n" RESET);

    struct {
        const char *a;
        const char *b;
    } tests[] = {
        {"", ""},
        {"a", "a"},
        {"a", "b"},
        {"abc", "abc"},
        {"abc", "abcd"},
        {"abcd", "abc"},
        {"Hello", "Hello"},
        {"Hello", "hello"},
    };

    for (int i = 0; i < (int)(sizeof(tests)/sizeof(*tests)); i++) {
        int my_result = ft_strcmp(tests[i].a, tests[i].b);
        int og_result = strcmp(tests[i].a, tests[i].b);

        int status = ((my_result == 0 && og_result == 0) ||
                  (my_result < 0 && og_result < 0) ||
                  (my_result > 0 && og_result > 0));

        printf(CYAN"Compare \"%s\" vs \"%s\" -> "RESET, tests[i].a, tests[i].b);
        printf(YELLOW"ft_strcmp = %d | strcmp = %d -> %s\n"RESET, my_result, og_result, status ? GREEN "OK" RESET : RED "FAIL" RESET);
    }
    printf("\n");
}

void test_ft_write(void) {
    printf(PURPLE "=== TESTING ft_write ===\n\n" RESET);
    const char *test_str = "Hello from ft_write!\n";
    ssize_t result = ft_write(STDOUT_FILENO, test_str, strlen(test_str));
    if (result == (ssize_t)strlen(test_str)) {
        printf(GREEN "ft_write wrote %zd bytes successfully\n" RESET, result);
    } else {
        printf(RED "ft_write wrote %zd bytes, expected %lu\n" RESET, result, strlen(test_str));
        perror("ft_write");
    }

    printf(PURPLE "\n=== with invalid fd ===\n\n" RESET);
    errno = 0;
    result = ft_write(-1, test_str, strlen(test_str));
    if (result == -1) {
        printf(GREEN "ft_write with invalid fd returned -1, errno = %d (%s)\n" RESET, errno, strerror(errno));
    } else {
        printf(RED "ft_write with invalid fd did not return error\n" RESET);
    }
    printf("\n");
}

void test_ft_read(void) {
    printf(PURPLE "=== TESTING ft_read ===\n\n" RESET);

    char buf[20];

    printf("Type some text and press Enter (max 19 chars):\n");
    ssize_t result = ft_read(STDIN_FILENO, buf, sizeof(buf) - 1);
    if (result >= 0) {
        buf[result] = '\0';
        printf(GREEN "ft_read read %zd bytes: \"%s\"\n" RESET, result, buf);
    } else {
        printf(RED "ft_read error: %zd\n" RESET, result);
        perror("ft_read");
    }

    printf(PURPLE "\n=== with invalid fd ===\n\n" RESET);
    errno = 0;
    result = ft_read(-1, buf, sizeof(buf));
    if (result == -1) {
        printf(GREEN "ft_read with invalid fd returned -1, errno = %d (%s)\n" RESET,
               errno, strerror(errno));
    } else {
        printf(RED "ft_read with invalid fd did not return error\n" RESET);
    }
    printf("\n");
}

void test_ft_strdup(void) {
    printf(PURPLE "=== TESTING ft_strdup ===\n\n" RESET);

    const char *tests[] = {
        "",
        "a",
        "Duplicate me!",
        "A longer string with spaces and numbers 1234567890",
    };

    for (int i = 0; i < (int)(sizeof(tests)/sizeof(*tests)); i++) {
        char *dup = ft_strdup(tests[i]);
        if (!dup) {
            printf(RED "ft_strdup failed to allocate memory\n" RESET);
            continue;
        }
        int cmp = strcmp(dup, tests[i]);
        printf(CYAN"Duplicate \"%s\" -> "RESET, tests[i]);
        printf(YELLOW"\"%s\" -> %s\n"RESET, dup, (cmp == 0) ? GREEN "OK" RESET : RED "FAIL" RESET);
        free(dup);
    }
    printf("\n");
}