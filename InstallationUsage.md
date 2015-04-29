# Installation #

## Compiling from source ##

### Prerequisites ###

**mash16** uses the **Scons** build system, which requires python.
  * In Arch Linux:
> `# pacman -S scons`
  * In Ubuntu/derivatives:
> `# apt-get install scons`
  * In Windows: See the [Scons download page](http://www.scons.org/download.php).

SDL libraries and headers, and gcc, are also required.

### Compilation ###

In Windows, ensure Scons is in your `PATH` variable.

Untar the archive, and change to it. Then run:

`$ scons`

followed by

`# scons install`

this time as root.

## Using precompiled binaries ##

Simply extract the archive.

# Usage #

**mash16** is a command-line utility. Pass the `--help` option to get a list of options you can use.