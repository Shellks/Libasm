#include <stdio.h>
#include <unistd.h>
#include <errno.h>

// libasm function
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dst, const char *src);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s);

int main(void) {
    printf("----------------------------------\n");
    // ----------> TEST for ft_strlen.s <---------- //
    {
        printf("TEST -- ft_strlen \n");
        printf("----\n");
        char str[13] = "Hello World!";
        printf(" | -> String \'%s\'\n", str);
        size_t len = ft_strlen(str);
        printf(" | -> len of the string is \'%lu\'\n", len);
    }
    printf("----------------------------------\n");
    // ----------> TEST for ft_strcpy.s <---------- //
    {
        printf("TEST -- ft_strcpy \n");
        printf("----\n");
        const char src[13] = "Hello";
        printf(" | -> Original string \'%s\'\n", src);
        char dst[13];
        printf(" | -> Copied string \'%s\'\n", ft_strcpy(dst, src));
    }
    printf("----------------------------------\n");
    // ----------> TEST for ft_strcmp.s <---------- //
    {
        printf("TEST -- ft_strcmp \n");
        printf("----\n");
        const char str1[1] = "";
        const char str2[2] = "l";
        printf(" | -> string 1 \'%s\'\n", str1);
        printf(" | -> string 2 \'%s\'\n", str2);
        int equal = ft_strcmp(str1, str2);
        if (equal < 0 || equal > 0) {
            printf(" | -> return \'%d\' - String is not equal\n", equal);
        } else {
            printf(" | -> return \'%d\' - String is equal\n", equal);
        }
    }
    printf("----------------------------------\n");
    // ----------> TEST for ft_write.s <---------- //
    {
        printf("TEST -- ft_write \n");
        printf("----\n");
        const char str1[5] = "Test";
        printf(" | -> Sending \'%s\' to ft_write\n", str1);
        int result = ft_write(1, "Test", 4);
        printf(" | -> result of ft_write is \'%d\'\n", result);
        printf(" | -> errno return is \'%d\'\n", errno);
    }
    printf("----------------------------------\n");
    // ----------> TEST for ft_read.s <---------- //
    {
        printf("TEST -- ft_read \n");
        printf("----\n");
        int size = 10;
        char str[size];
        printf(" | -> sending a buffer of \'%d\' to ft_read :\n", size);
        int result = ft_read(0, str, 4);
        printf(" | -> result of ft_read is \'%d\'\n", result);
        printf(" | -> errno return is \'%d\'\n", errno);
    }
    printf("----------------------------------\n");
    // ----------> TEST for ft_strdup.s <---------- //
    {
        printf("TEST -- ft_strdup \n");
        printf("----\n");
        const char str1[10] = "test";
        printf(" | -> Sending \'%s\' to ft_strdup\n", str1);
        char *str2 = ft_strdup(str1);
        printf(" | -> result of ft_strdup is \'%s\'\n", str2);
    }
    printf("----------------------------------\n");
    return 0;
}