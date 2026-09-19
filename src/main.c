#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ws/impl.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 1
#define VERSION_TAG "-dev"

void
usage (char *path)
{
  printf ("usage: %s [OPTIONS] <project>\n", path);
  printf ("project: the folder in your DEFAULT_WS that you will `cd' into\n");
  printf ("OPTIONS:\n");
  printf ("    -h             Prints usage\n");
  printf ("    -v             Prints the version\n");
  printf ("    -n <name>      Creates a new project with <name>\n");
  printf ("    --ls           List all projects in your DEFAULT_WS\n");
  printf (
      "    --ed           Opens your WS_EDITOR on the specified project\n");
  printf ("    --rm <name>    Deletes a project from your DEFAULT_WS\n");
}

void
print_version (void)
{
  printf ("ws v%d.%d.%d%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH,
          VERSION_TAG);
}

int
main (int argc, char **argv)
{
  if (argc == 1)
    {
      usage (argv[0]);
      return 0;
    }

  if (!getenv ("DEFAULT_WS"))
    {
      fprintf (stderr, "Error: you must set your DEFAULT_WS variable!\n");
      exit (EXIT_FAILURE);
    }

  char *exe_path = argv[0];
  int editor = 0;
  char *project = NULL;

  static struct option long_options[] = { { "rm", required_argument, 0, 'd' },
                                          { "ls", no_argument, 0, 'l' },
                                          { "ed", no_argument, 0, 'e' },
                                          { 0, 0, 0, 0 } };

  int opt;
  int optindex = 0;
  while ((opt = getopt_long (argc, argv, "hvn:rld:e", long_options, &optindex))
         != -1)
    {
      switch (opt)
        {
        case 'h': // -h
          usage (exe_path);
          exit (EXIT_SUCCESS);
          break;
        case 'e': // --ed
          editor = 1;
          break;
        case 'l': // --ls
          list_projects ();
          exit (EXIT_SUCCESS);
          break;
        case 'n': // -n
          create_new_project (optarg);
          printf ("Successfully created project %s\n", optarg);
          exit (EXIT_SUCCESS);
          break;
        case 'd': // --rm
          delete_project (optarg);
          exit (EXIT_SUCCESS);
          break;
        case 'v': // -v
          print_version ();
          exit (EXIT_SUCCESS);
          break;
        default:
          abort ();
          break;
        }
    }

  if (optind >= argc)
    {
      usage (exe_path);
      exit (EXIT_FAILURE);
    }

  project = argv[optind];
  enter_project (project, editor);

  return 0;
}