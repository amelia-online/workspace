#include <ws/impl.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>

static const char *
get_default_ws ()
{
  const char *const path = getenv ("DEFAULT_WS");

  if (!path)
    {
      fprintf (stderr, "Error: your DEFAULT_WS was unset!\n");
      exit (EXIT_FAILURE);
    }

  return strdup (path);
}

void
create_new_project (const char *name)
{
  const char *ws_path = get_default_ws ();
  if (access (ws_path, F_OK) == -1)
    {
      fprintf (stderr, "Error: your DEFAULT_WS is invalid.\n");
      free (ws_path);
      exit (EXIT_FAILURE);
    }

  size_t path_len = strlen (ws_path);
  int has_slash = ws_path[path_len - 1] == '/';
  size_t full_len = (has_slash) ? path_len + strlen (name) + 1
                                : path_len + strlen (name) + 2;

  char result_path[full_len];
  const char *fmt = (has_slash) ? "%s%s" : "%s/%s";
  snprintf (result_path, full_len, fmt, ws_path, name);

  mode_t mode = S_IRWXG | S_IRWXO | S_IRWXU;
  if (mkdir (result_path, mode) == -1)
    {
      fprintf (stderr, "Error: %s\n", strerror (errno));
      free (ws_path);
      exit (EXIT_FAILURE);
    }

  free (ws_path);
}

void
enter_project (const char *name)
{
}

void
delete_project (const char *name)
{
}

void
list_projects ()
{
}