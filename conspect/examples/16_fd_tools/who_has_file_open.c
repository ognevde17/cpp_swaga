#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <limits.h>
#include <unistd.h>

static void die_usage(const char *argv0) {
  dprintf(2, "usage: %s <path>\n", argv0);
  exit(2);
}

static int same_path(const char *a, const char *b) {
  return strcmp(a, b) == 0;
}

int main(int argc, char **argv) {
  if (argc != 2) die_usage(argv[0]);

  char wanted[PATH_MAX];
  if (!realpath(argv[1], wanted)) {
    dprintf(2, "realpath(%s): %s\n", argv[1], strerror(errno));
    return 1;
  }

  DIR *proc = opendir("/proc");
  if (!proc) {
    dprintf(2, "opendir(/proc): %s\n", strerror(errno));
    return 1;
  }

  struct dirent *pe = NULL;
  while ((pe = readdir(proc)) != NULL) {
    char *end = NULL;
    long pid_l = strtol(pe->d_name, &end, 10);
    if (!end || *end != '\0' || pid_l <= 0) continue;
    int pid = (int)pid_l;

    char fd_dir[64];
    snprintf(fd_dir, sizeof(fd_dir), "/proc/%d/fd", pid);
    DIR *fds = opendir(fd_dir);
    if (!fds) continue; // no permission / process exited

    struct dirent *fe = NULL;
    while ((fe = readdir(fds)) != NULL) {
      if (strcmp(fe->d_name, ".") == 0 || strcmp(fe->d_name, "..") == 0) continue;

      char link_path[PATH_MAX];
      snprintf(link_path, sizeof(link_path), "%s/%s", fd_dir, fe->d_name);

      char target[PATH_MAX];
      ssize_t n = readlink(link_path, target, sizeof(target) - 1);
      if (n < 0) continue;
      target[n] = '\0';

      char resolved[PATH_MAX];
      if (!realpath(target, resolved)) continue; // e.g. deleted files, sockets, pipes

      if (same_path(resolved, wanted)) {
        dprintf(1, "pid %d has fd %s open (%s)\n", pid, fe->d_name, resolved);
      }
    }
    closedir(fds);
  }

  closedir(proc);
  return 0;
}

