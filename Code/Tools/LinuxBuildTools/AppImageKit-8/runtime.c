/**************************************************************************

Copyright (c) 2005-10 Simon Peter
Copyright (c) 2007 Alexander Larsson

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

**************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

extern int ext2_main(int argc, char *argv[], void (*mounted) (void));
extern void ext2_quit(void);

static pid_t fuse_pid;
static int keepalive_pipe[2];

static void *
write_pipe_thread (void *arg)
{
  char c[32];
  int res;
//  sprintf(stderr, "Called write_pipe_thread");
  memset (c, 'x', sizeof (c));
  while (1) {
    /* Write until we block, on broken pipe, exit */
    res = write (keepalive_pipe[1], c, sizeof (c));
    if (res == -1) {
      kill (fuse_pid, SIGHUP);
      break;
    }
  }
  return NULL;
}

void
run_when_fuse_fs_mounted (void)
{

//    sprintf(stderr, "Called run_when_fuse_fs_mounted");
    pthread_t thread;
    int res;

    fuse_pid = getpid();
    res = pthread_create(&thread, NULL, write_pipe_thread, keepalive_pipe);
}

int
main (int argc, char *argv[])
{
  int dir_fd, res;
  char mount_dir[] = "/tmp/.mount_XXXXXX";  /* create mountpoint */
  char filename[100]; /* enough for mount_dir + "/AppRun" */
  pid_t pid;
  char **real_argv;
  int i;

  if (mkdtemp(mount_dir) == NULL) {
    exit (1);
  }

  if (pipe (keepalive_pipe) == -1) {
    perror ("pipe error: ");
    exit (1);
  }

  pid = fork ();
  if (pid == -1) {
    perror ("fork error: ");
    exit (1);
  }
  
  if (pid == 0) {
    /* in child */
    
    char *child_argv[5];

    /* close read pipe */
    close (keepalive_pipe[0]);


    char *dir = realpath( "/proc/self/exe", NULL );

    child_argv[0] = dir;
    child_argv[1] = mount_dir;
    child_argv[2] = "-o";
    child_argv[3] = "ro";
    child_argv[4] = NULL;
    
    ext2_main (4, child_argv, NULL);
  } else {
    /* in parent, child is $pid */
    int c;

    /* close write pipe */
    close (keepalive_pipe[1]);

    /* Pause until mounted */
    read (keepalive_pipe[0], &c, 1);


    dir_fd = open (mount_dir, O_RDONLY);
    if (dir_fd == -1) {
      perror ("open dir error: ");
      exit (1);
    }
    
    res = dup2 (dir_fd, 1023);
    if (res == -1) {
      perror ("dup2 error: ");
      exit (1);
    }
    close (dir_fd);
    
    strcpy (filename, mount_dir);
    strcat (filename, "/AppRun");

    real_argv = malloc (sizeof (char *) * (argc + 1));
    for (i = 0; i < argc; i++) {
      real_argv[i] = argv[i];
    }
    real_argv[i] = NULL;
    
    execv (filename, real_argv);
    /* Error if we continue here */
    perror ("execv error: ");
    exit (1);
  }
  
  return 0;
}
