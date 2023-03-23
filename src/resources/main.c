#include <Crypt.h>

#undef main

int main(int, char **);
extern int __Crypt_main(int, char **);

int main(int argc, char * argv[]) {
    /* Reopens stdout and stderr to /dev/null so they won't attempt to pollute the terminal.
     * Could be changed in the future to debug files, or pipe to another process for better debugging.
     */
    freopen("/dev/null", "a+", stdout);
    freopen("/dev/null", "a+", stderr);

    return __Crypt_main(argc, argv);
}
