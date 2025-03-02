#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int error(const char* path)
{
  fprintf(stderr, "error: %s: %s\n", path, strerror(errno));
  return -1;
}

int isDir(const char* path)
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

  struct dirent* ent = 0;

  int i = strlen(path);
  int j = 0;

  while ((ent = readdir(odir)))
  {
    if (!strcmp(ent->d_name, "..") || !strcmp(ent->d_name, "."))
      continue;

    j = i + sprintf(path + i, "/%s", ent->d_name);

    if (!isDir(path))
      continue;

    DIR* idir = opendir(path);

    if (idir)
    {
      unsigned char has = 0;

      while ((ent = readdir(idir)))
      {
        if (!strcmp(ent->d_name, "..") || !strcmp(ent->d_name, "."))
          continue;

        sprintf(path + j, "/%s", ent->d_name);

        if (isDir(path))
        {
          has = 1;
          break;
        }
      }

      if (has)
      {
        path[j + 1] = '\0';
        printf("%s\n", path);
      }
    }
    else
    {
      error(path);
    }

    closedir(idir);
  }

  closedir(odir);

  return 0;
}