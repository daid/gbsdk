# New project

There are two ways to setup a new project:

1) Use the [template](https://github.com/daid/gbsdk-template) on github and directly create a new repository
2) From scratch

## Using the template

First, make sure you have a github account, and that you are logged in.

Next, select the **Use this template** button on the [template](https://github.com/daid/gbsdk-template) page, and create a your own repository.

You can clone this with the github desktop application, or from the commandline (also in the gbsdk-windows-environment) with:
```sh
# Replace daid/gbsdk-template.git with your own repository
git clone https://github.com/daid/gbsdk-template.git --recursive
```
Be sure to add `--recursive` to get the gbsdk submodule!

This gives you a template project which is ready to be build. You're now ready to [setup build configuration](configuration.md).

## Set up a project from scratch

Your project will need 3 things:

1) A Makefile
2) gbsdk
3) A directory for source files, and for asset files

### Makefile

The Makefile is very bare bones, it just needs to define some project settings. So make a new empty text file with the following contents:
```makefile
# Name of your project, will set the name of your ROM.
PROJECT_NAME := Project_Name
# Run "rgbfix --mbc-type help" for possible MBC types
MBC     := ROM
# Target should be a combination of DMG, CGB and SGB
TARGETS := DMG

include gbsdk/rules.mk
```

### gbsdk

Next to the makefile, you need a directory named "gbsdk" with the gbsdk contents. You can get this as a git submodule, a git clone or downloading the zip from [https://github.com/daid/gbsdk](https://github.com/daid/gbsdk)

Make sure the directory is named gbsdk (or that the makefile is adjusted to look at the right directory)

### Source directory

Create two empty directories, one named `src` and one named `assets`.
In the `src` directory create a `main.c` file with the following contents:
```c
#include <sdk/hardware.h>

void main() {
}
```

This creates an bare minimum piece of code that compiles but does nothing.
