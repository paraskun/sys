#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/// @brief Print error and return.
/// @param path error point
static int error(const char* path)
{
    fprintf(stderr, "error: %s: %s\n", path, strerror(errno));
    return -1;
}

/// @brief Determine if there is directory at the specified path.
/// @param path exploration point
static int is_dir(const char* path)
{
    struct stat s;

    if (stat(path, &s) == -1)
        return -1;

    return S_ISDIR(s.st_mode) ? 1 : 0;
}

int main(int argc, char** argv)
{
    char path[257] = ".";

    if (argc > 1)
        strncpy(path, argv[1], sizeof(path));

    DIR* odir = opendir(path);

    if (!odir)
        return error(path);

    int i = strlen(path); // outer dir path offset
    int j = 0;            // inner dir path offset

    struct dirent* ent = 0;

    while ((ent = readdir(odir)))
    {
        if (!strcmp(ent->d_name, "..") || !strcmp(ent->d_name, "."))
            continue;

        j = i + sprintf(path + i, "/%s", ent->d_name);

        if (!is_dir(path))
            continue;

        DIR* idir = opendir(path);

        if (!idir)
        {
            error(path);
            continue;
        }

        while ((ent = readdir(idir)))
        {
            if (!strcmp(ent->d_name, "..") || !strcmp(ent->d_name, "."))
                continue;

            sprintf(path + j, "/%s", ent->d_name);

            if (is_dir(path))
            {
                path[j + 1] = '\0';
                printf("%s\n", path);
                break;
            }
        }

        closedir(idir);
    }

    closedir(odir);

    return 0;
}