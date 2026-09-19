# Workspace (or just 'ws')

This is just a fun little C project for me. I used to write
the equivalent of this in my ~/.bashrc for simple workflow
automation stuff. There was no AI used besides whatever pops
up on google and I tried to stick mostly to the man pages anyway.

## Description

Workspace is a tool that saves me the time of writing out file paths
to projects I work on often. Here's how it works:

* In your ~/.zshrc or ~/.bashrc do `export DEFAULT_WS=/path/to/your/projects`
  * Ex. `export DEFAULT_WS=$HOME/Projects`
* Then, you can run `ws <project name>` and it will open a nested shell in that project.
* You can also do, for example, `ws -n new_project`. This creates a new project in your `DEFAULT_WS` called 'new_project'

If you want to see everything just do `ws -h`. I'll probably add more features as I go.

## Build

To build it, just do `make` in this directory. No `install` rule yet.

## Disclaimer

This has only been mildly tested on MacOS. I want it to work on Linux too so stay tuned for that.
