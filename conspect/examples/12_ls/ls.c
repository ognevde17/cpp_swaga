#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static char type_char(mode_t m) {
  if (S_ISREG(m)) return '-';
  if (S_ISDIR(m)) return 'd';
  if (S_ISLNK(m)) return 'l';
  if (S_ISCHR(m)) return 'c';
  if (S_ISBLK(m)) return 'b';
  if (S_ISFIFO(m)) return 'p';
  if (S_ISSOCK(m)) return 's';
  return '?';
}

int main(int argc, char **argv) {
  const char *path = (argc == 2) ? argv[1] : ".";
  DIR *d = opendir(path);
  if (!d) {
    perror("opendir");
    return 1;
  }

  int dfd = dirfd(d);
  errno = 0;
  for (;;) {
    struct dirent *e = readdir(d);
    if (!e) break;
    struct stat st;
    if (fstatat(dfd, e->d_name, &st, AT_SYMLINK_NOFOLLOW) != 0) {
      dprintf(2, "stat %s: %s\n", e->d_name, strerror(errno));
      continue;
    }
    dprintf(1, "%c %s\n", type_char(st.st_mode), e->d_name);
  }
  if (errno != 0) {
    perror("readdir");
    closedir(d);
    return 1;
  }

  closedir(d);
  return 0;
}

