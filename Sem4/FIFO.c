#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSIZE 4096
#define NAMESIZE 64

#define __CHECK_ERROR(message, condition)\
    if (condition)\
    {\
        fprintf (stderr, "%s:%u: ", __FILE__, __LINE__);\
        perror (message);\
        exit (EXIT_FAILURE);\
    }

#define pairid_t unsigned long long 

int find_sender ();
int find_reciever ();
pairid_t mk_pair_id ();

int main (int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf (stderr, "Usage: %s <name_of_file> or %s\n", argv[0], argv[0]);
        exit (EXIT_FAILURE);
    }     

    char buf[BUFSIZE] = "";

    if (argc == 1) /* writer */
    {
        int fd_fifo = find_sender ();

        while (1)
        {
            ssize_t bytes_count = read (fd_fifo, buf, BUFSIZE);
            __CHECK_ERROR ("Can't read data from file", bytes_count == -1);

            if (!bytes_count)
                exit (EXIT_SUCCESS);

            bytes_count = write (STDOUT_FILENO, buf, bytes_count);
            __CHECK_ERROR ("Can't write data to fifo file", bytes_count == -1);
        }
    }
    else /* Reader */
    {
        int fd_input = open (argv[1], O_RDONLY);
        __CHECK_ERROR ("Can't open input file", fd_input == -1);

        int fd_fifo = find_reciever ();

        while (1)
        {
            ssize_t bytes_count = read (fd_input, buf, BUFSIZE);
            __CHECK_ERROR ("Can't read data from file", bytes_count == -1);

            if (!bytes_count)
                exit (EXIT_SUCCESS);

            bytes_count = write (fd_fifo, buf, bytes_count);
            __CHECK_ERROR ("Can't write data to fifo file", bytes_count == -1);
        }
    }
}

int find_reciever ()
{
    char fifo_name[NAMESIZE] = "";

    __CHECK_ERROR ("Can't make common fifo file", mkfifo (".file.fifo", S_IWUSR | S_IRUSR) && errno != EEXIST);

    int fd_common_fifo = open (".file.fifo", O_WRONLY);
    __CHECK_ERROR ("Can't open common fifo file", fd_common_fifo == -1);

    pairid_t id = mk_pair_id ();
    snprintf (fifo_name, NAMESIZE, ".file_%llu.fifo", id);

    __CHECK_ERROR ("Can't make fifo file", mkfifo (fifo_name, S_IWUSR | S_IRUSR) && errno != EEXIST);

    ssize_t bytes_count = write (fd_common_fifo, fifo_name, NAMESIZE);
    __CHECK_ERROR ("Can't write data to common fifo file", bytes_count == -1);

    int fd_fifo = open (fifo_name, O_WRONLY);
    __CHECK_ERROR ("Can't open fifo file", fd_fifo == -1);

    __CHECK_ERROR ("Can't close common fifo file", close (fd_common_fifo) == -1);

    return fd_fifo;
}

int find_sender ()
{
    char fifo_name[NAMESIZE] = "";

    __CHECK_ERROR ("Can't make common fifo file", mkfifo (".file.fifo", S_IWUSR | S_IRUSR) && errno != EEXIST);

    int fd_common_fifo = open (".file.fifo", O_RDONLY);
    __CHECK_ERROR ("Can't open common fifo file", fd_common_fifo == -1);

    ssize_t bytes_count = read (fd_common_fifo, fifo_name, NAMESIZE);
    while (!bytes_count)
    {
        bytes_count = read (fd_common_fifo, fifo_name, NAMESIZE);
        __CHECK_ERROR ("Can't read data from common fifo file", bytes_count == -1);
    }

    int fd_fifo = open (fifo_name, O_RDONLY);
    __CHECK_ERROR ("Can't open fifo file", fd_fifo == -1);

    __CHECK_ERROR ("Can't close common fifo file", close (fd_common_fifo) == -1);

    return fd_fifo;

}

pairid_t mk_pair_id ()
{
    int fd = open ("/dev/random", O_RDONLY);
    __CHECK_ERROR ("Can't open /dev/random", fd == -1);

    pairid_t id = 0;
    __CHECK_ERROR ("Can't read from /dev/random", read (fd, &id, sizeof (pairid_t) ) == -1);

    __CHECK_ERROR ("Can't close /dev/random", close (fd) == -1);
    return id;
}
