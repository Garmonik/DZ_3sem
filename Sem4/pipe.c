#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFSIZE 4096

int main (int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf (stderr, "Usage: %s <name_of_file> or %s\n", argv[0], argv[0]);
        exit (EXIT_FAILURE);
    }     

    char buf[BUFSIZE] = {};

    if (argc == 1)
    {
        int fd = open ("file.fifo", O_RDONLY);

        if (fd == -1)
        {
            perror ("Can't open file.fifo:");
            exit (EXIT_FAILURE);
        }

        while (1)
        {
            ssize_t bytes_count = read (fd, buf, BUFSIZE);

            if (bytes_count == -1)
            {
                perror ("Can't read from file.fifo:");
                exit (EXIT_FAILURE);
            }

            if (!bytes_count)
                exit (EXIT_SUCCESS);

            bytes_count = write (1, buf, bytes_count);

            if (bytes_count == -1)
            {
                perror ("Can't write to stdout:");
                exit (EXIT_FAILURE);
            }
        }
    }
    else
    {
        int fd_fifo = open ("file.fifo", O_WRONLY);

        if (fd_fifo == -1)
        {
            perror ("Can't open file.fifo:");
            exit (EXIT_FAILURE);
        }

        int fd_file = open (argv[1], O_RDONLY);

        if (fd_file == -1)
        {
            perror ("Can't open input file:");
            exit (EXIT_FAILURE);
        }

        while (1)
        {
            ssize_t bytes_count = read (fd_file, buf, BUFSIZE);

            if (bytes_count == -1)
            {
                perror ("Can't read from input file:");
                exit (EXIT_FAILURE);
            }

            if (!bytes_count)
                exit (EXIT_SUCCESS);

            bytes_count = write (fd_fifo, buf, bytes_count);

            if (bytes_count == -1)
            {
                perror ("Can't write to file.fifo:");
                exit (EXIT_FAILURE);
            }
        }
    }
}
