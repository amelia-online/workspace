#include <ws/impl.h>

#include <dirent.h>
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

static const char *
full_path (const char *name)
{
  const char *ws_path = get_default_ws ();
  size_t path_len = strlen (ws_path);
  int has_slash = ws_path[path_len - 1] == '/';
  size_t full_len = (has_slash) ? path_len + strlen (name) + 1
                                : path_len + strlen (name) + 2;

  char *result_path = (char *)malloc (sizeof (char) * full_len);
  const char *fmt = (has_slash) ? "%s%s" : "%s/%s";
  snprintf (result_path, full_len, fmt, ws_path, name);
  free (ws_path);
  return result_path;
}

static void
verify_path (const char *path)
{
  if (access (path, F_OK) == -1)
    {
      fprintf (stderr, "Error: your DEFAULT_WS is invalid.\n");
      exit (EXIT_FAILURE);
    }
}

void
create_new_project (const char *name)
{
  const char *ws_path = get_default_ws ();
  verify_path (ws_path);
  free (ws_path);

  const char *result_path = full_path (name);

  mode_t mode = S_IRWXG | S_IRWXO | S_IRWXU;
  if (mkdir (result_path, mode) == -1)
    {
      fprintf (stderr, "Error: %s: %s\n", name, strerror (errno));
      free (result_path);
      exit (EXIT_FAILURE);
    }

  free (result_path);
}

void
enter_project (const char *name, int editor)
{
  const char *path = full_path (name);
  verify_path (path);

  if (editor)
    fprintf (stderr, "Warn: --ed is currently unsupported.\n");

  if (chdir (path) == -1)
    {
      fprintf (stderr, "Error: %s: %s\n", path, strerror (errno));
      free (path);
      exit (EXIT_FAILURE);
    }

  free (path);

  char *args[] = { "/bin/zsh", NULL };
  execvp (args[0], args);
}

void
delete_project (const char *name)
{
  const char *path = full_path (name);
  verify_path (path);

  if (rmdir (path) == -1)
    {
      fprintf (stderr, "Error: %s: %s\n", path, strerror (errno));
      free (path);
      exit (EXIT_FAILURE);
    }

  free (path);
}

void
list_projects ()
{
  const char *ws_path = get_default_ws ();
  verify_path (ws_path);

  DIR *ws = opendir (ws_path);

  if (!ws)
    {
      fprintf (stderr, "Error: unable to open DEFAULT_WS!\n");
      free (ws_path);
      exit (EXIT_FAILURE);
    }

  struct dirent *entry;
  while ((entry = readdir (ws)) != NULL)
    {
      if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
        printf ("%s\n", entry->d_name);
    }

  closedir (ws);
  free (ws_path);
}