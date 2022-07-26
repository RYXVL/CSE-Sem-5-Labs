#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    char c;
    int in, out;
    in = open("a.txt", O_RDONLY);
    out = open("b.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while (read(in, &c, 1) == 1)
        write(out, &c, 1);
    return 0;
}