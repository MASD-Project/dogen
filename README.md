![Dogen Logo](https://raw.githubusercontent.com/MASD-Project/dogen/master/doc/images/new_logo_with_message.png)

[![Licence](https://img.shields.io/badge/license-GPL_3-green.svg?dummy)](https://raw.githubusercontent.com/MASD-Project/dogen/master/LICENCE)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen?ref=badge_shield)
[![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)](https://github.com/MASD-Project/dogen/pulse/monthly)
[![Gitter](https://img.shields.io/gitter/room/nwjs/nw.js.svg)](https://gitter.im/MASD-Project/Lobby)
[![Issues](https://img.shields.io/github/issues/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/issues)
[![Contributors](https://img.shields.io/github/contributors/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/graphs/contributors)
[![PRs Welcome](https://img.shields.io/badge/PRs%20-welcome-brightgreen.svg)](https://github.com/MASD-Project/dogen/blob/master/CONTRIBUTING.md)
[![Github All Releases](https://img.shields.io/github/downloads/MASD-Project/dogen/total.svg)](https://github.com/MASD-Project/dogen/releases)
[![Continuous Linux](https://github.com/MASD-Project/dogen/actions/workflows/continuous-linux.yml/badge.svg)](https://github.com/MASD-Project/dogen/actions/workflows/continuous-linux.yml)
[![Continuous Windows](https://github.com/MASD-Project/dogen/actions/workflows/continuous-windows.yml/badge.svg)](https://github.com/MASD-Project/dogen/actions/workflows/continuous-windows.yml)
[![Continuous MacOS](https://github.com/MASD-Project/dogen/actions/workflows/continuous-macos.yml/badge.svg)](https://github.com/MASD-Project/dogen/actions/workflows/continuous-macos.yml)
[![Nightly FG Branch](https://github.com/MASD-Project/dogen/actions/workflows/nightly-create-fullgen-branch.yml/badge.svg)](https://github.com/MASD-Project/dogen/actions/workflows/nightly-create-fullgen-branch.yml)
[![Nightly FG](https://github.com/MASD-Project/dogen/actions/workflows/nightly-fullgen-linux.yml/badge.svg)](https://github.com/MASD-Project/dogen/actions/workflows/nightly-fullgen-linux.yml)
[![Nightly Linux](https://github.com/MASD-Project/dogen/actions/workflows/nightly-linux.yml/badge.svg)](https://github.com/MASD-Project/dogen/actions/workflows/nightly-linux.yml)
[![CDash](https://img.shields.io/badge/cdash-dashboard-00cc00.svg)](https://my.cdash.org/index.php?project=MASD+Project+-+Dogen)
[![Releases](https://img.shields.io/github/release/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/releases)
[![GitHub commits](https://img.shields.io/github/commits-since/MASD-Project/dogen/v1.0.32.svg)](https://github.com/MASD-Project/dogen/commits/master)
[![Documentation](https://github.com/MASD-Project/dogen/blob/master/assets/doxygen_badge.svg)](https://mcraveiro.github.io/dogen/doxygen/index.html)
[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://www.openhub.net/p/dogen/analyses/latest/languages_summary)
[![C++](https://img.shields.io/badge/std-C++17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![gcc-11](https://img.shields.io/badge/GCC-11-blue.svg)](https://www.gnu.org/software/gcc/gcc-11)
[![clang-14](https://img.shields.io/badge/CLANG-14-blue.svg)](https://releases.llvm.org/14.0.0/tools/clang/docs/ReleaseNotes.html)
[![msvc2022](https://img.shields.io/badge/MSVC-2022-blue.svg)](https://visualstudio.microsoft.com/vs/whatsnew/)
[![TODOs](https://badgen.net/https/api.tickgit.com/badgen/github.com/MASD-Project/dogen)](https://www.tickgit.com/browse?repo=github.com/MASD-Project/dogen)
[![Project Stats](https://www.openhub.net/p/dogen/widgets/project_thin_badge.gif)](https://www.openhub.net/p/dogen)

# Overview

**Dogen** is the reference implementation of the _MASD Project_ code generator.
MASD - Model Assisted Software Development - is a new methodology for the
development of software systems based on [MDE (Model Driven
Engineering)](https://en.wikipedia.org/wiki/Model-driven_engineering). MASD was
developed in the context of a PhD programme; if you are that way inclined, you
may find the thesis of interest: [Model Assisted Software Development - a
MDE-Based Software Development
Methodology](https://uhra.herts.ac.uk/handle/2299/25708).

In lay terms, Dogen's objective is to automate the development process as much
as possible: the user creates _models_ using [Org Mode](https://orgmode.org/),
though these must respect a set of predefined restrictions. Dogen uses this
input to generate a source code representation of the model. Unlike traditional
modeling techniques like
[UML](https://en.wikipedia.org/wiki/Unified_Modeling_Language), Dogen focuses
instead on literate modeling - an approach based on Knuth's [Literate
programming](https://en.wikipedia.org/wiki/Literate_programming).

The generated code contains most of the functionality required from a typical
domain object such as serialisation, hashing, streaming and so on. Whilst we
intend for the application to be useful out of the box for most use cases, our
end goal is to enable users to extend Dogen, adapting it to the vagaries of
their specific needs. Note that Dogen has experimental C# support, but it is not
in feature parity with C++ support.

Dogen provides a _reference product_ for each supported language, available as a
separate git repo:

- [C++ Reference Product](https://github.com/MASD-Project/cpp_ref_impl).
  Models available
  [here](https://github.com/MASD-Project/cpp_ref_impl/tree/master/projects/cpp_ref_impl.models).
- [C# Reference Product](https://github.com/MASD-Project/csharp_ref_impl).
  Models available
  [here](https://github.com/MASD-Project/csharp_ref_impl/tree/master/Src/CSharpRefImpl.Models).

These are intended to give you a feel for how the generated code will look like,
and they attempt to exercise all of Dogen's functionality. Note that these
reference products still use older codecs rather than org-model.

# Status

Our previous major milestone for Dogen was to complete the [PhD
thesis](https://uhra.herts.ac.uk/handle/2299/25708), which we did so
successfully. The current major milestone is to sync up the source code with the
latest version of the theoretical framework, as laid out in the thesis. In other
words, our focus is _not_ on producing a fully polished tool, ready for end
users to deploy on industrial scale projects. If, for whatever reason you still
want to go ahead and use it, bear in mind the following:

- our immediate goal is to refactor the conceptual model in the source code to
  reflect the MASD conceptual model presented in Chapter 6 of the thesis
  (_Domain Architecture_). We will continue to refactor the code internally
  until it is consistent with the conceptual model. It may take a long while to
  get there. This means that adding new features is not a priority for Dogen
  development (though we are gathering a long list of ideas in our [product
  backlog](https://github.com/MASD-Project/dogen/blob/master/doc/agile/product_backlog.org)).
- in our quest for the conceptual model, we have broken and _we shall continue
  to break_ the API many times. This will manifest itself in having to update
  user models or in changes in the generated code. Features that have been
  working thus far may also be deprecated. We provide no guarantees of forward
  or backward compatibility; there isn't even an effort not to break these - in
  fact, quite the opposite, if its not in agreement with the conceptual model it
  must be changed. We do try to highlight these in the [release
  notes](https://github.com/MASD-Project/dogen/releases) best we can.
- we do have an [extensive suite of
  tests](https://my.cdash.org/index.php?project=MASD+Project+-+Dogen) (both
  generated and handcrafted), but these focus _only_ on Dogen's use cases. If
  you try any permutations outside these, it is likely you will find problems.
  The errors you will get will not be the most obvious.
- there is little to no documentation on Dogen. We are presently working on
  porting across the documentation generated for the thesis but the process is
  slow and laborious.
- for this tool to be useful in any way in its present state, you must have a
  good working knowledge of
  [MDE](https://en.wikipedia.org/wiki/Model-driven_engineering). You can make
  use of our companion notes to get up to speed: [Notes on Model Driven
  Engineering](https://zenodo.org/record/5812017#.YkmlftDMKXI)

These warnings can probably best summarised as follows: "if it breaks, you get
to keep the pieces; and it will break, often". But if you find such things fun,
proceed with caution.

# Binary Packages

Binary packages are available for each release on and
[GitHub](https://github.com/MASD-Project/dogen/releases) (links at the end of
each release note). The binaries cover Debian Linux, OSX and Windows - 64-bit
only. Packages are also generated for each commit and saved with the
corresponding [GitHub Workflow](https://github.com/MASD-Project/dogen/actions).
Development is done from git master, so latest should always be greatest, but
you may want to use packages from the previous sprint rather than what is
currently under development (see badges above).

---
**Notes**

- Other than Linux, we do not test the packages manually. If you find any issues
  with a binary package, please raise an issue.
- The OSX installer provides you with a DMG. Once you open it in Finder, it
  mounts under ```/Volumes/```, _e.g_.:

```
/Volumes/dogen-${VERSION}-Darwin-x86_64/dogen.app/Contents/Resources/bin
```

  Where ```${VERSION}``` is your Dogen version such as ```1.0.32```.

----

# Building From Source

In order to build Dogen you will need a C++ toolchain. On Linux and OSX, you'll
need a recent compiler with C++ 17 support, such as [GCC
11](https://www.gnu.org/software/gcc/gcc-11) or [Clang
14](https://releases.llvm.org/14.0.0/tools/clang/docs/ReleaseNotes.html) - and
[Ninja](https://ninja-build.org/manual.html) or [GNU
Make](https://www.gnu.org/software/make/). On Windows you'll need [Visual Studio
2017](https://visualstudio.microsoft.com/vs/whatsnew/). On all platforms, we
make use of [CMake](https://cmake.org/). Older compilers may work, but we try to
always use the most recent releases in MASD. So, if you can, please try using to
those.

Dogen has the following dependencies, across all operative systems:

| Name                                     | Type      | Version          |
|------------------------------------------|-----------|------------------|
| [CMake](https://cmake.org/)              | Mandatory | 3.23 or greater. |
| [Boost](https://boost.org)               | Mandatory | 1.81 or greater. |
| [DTL](https://github.com/cubicdaiya/dtl) | Mandatory | 1.19             |

Note that earlier versions may work but haven't been tested. Also, though Dogen
should build fine with package manager supplied libraries - or even with
hand-built dependencies - the recommended way to setup a development environment
on all supported platforms is by using
[vcpkg](https://github.com/Microsoft/vcpkg), which is what this document
describes. Dogen uses the "sub-module setup", whereby vcpkg is a submodule of
Dogen. All of the dependencies are declared in the
[vcpkg.json](https://github.com/MASD-Project/dogen/blob/master/vcpkg.json) file.

Before we proceed, please note that Dogen makes use of [CMake
Presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html). You
can have a look at our presets file
[```CMakePresets.json```](https://github.com/MASD-Project/dogen/blob/master/CMakePresets.json)
for a list of available presets; alternatively, just use CMake:

```
$ cmake --list-presets
Available configure presets:

  "linux-clang-debug"             - Linux clang debug
  "linux-clang-release"           - Linux clang release
  "linux-gcc-debug"               - Linux gcc debug
  "linux-gcc-release"             - Linux gcc release
  "windows-msvc-debug"            - Windows x64 Debug
  "windows-msvc-release"          - Windows x64 Release
  "windows-msvc-clang-cl-debug"   - Windows x64 Debug
  "windows-msvc-clang-cl-release" - Windows x64 Release
  "macos-clang-debug"             - Mac OSX Debug
  "macos-clang-release"           - Mac OSX Release
```

For the remainder of this document we shall assume ```linux-clang-release```,
which is our preferred preset. If it isn't yours, remember to update the preset
name to match your desired build.

To checkout Dogen, clone as follows:

```
git clone https://github.com/MASD-Project/dogen.git --recurse-submodules
```

This takes into account the vcpkg submodule setup, as well as test data
(explained below). For the configure step:

```
cd dogen
cmake --preset linux-clang-release
```

You can build Dogen on all platforms (modulus preset) as follows:

```
cmake --build --preset linux-clang-release
```

## Testing

If you'd like to run the project tests, execute the target ```run_all_tests```
or its abbreviation ```rat```. Note that the tests check code generation against
both Dogen, as well as the reference products:

- [C++ Reference Implementation](https://github.com/MASD-Project/cpp_ref_impl)
- [C# Reference Implementation](https://github.com/MASD-Project/csharp_ref_impl)

Reference products are checked out as git sub-modules under ```test_data``` and
pointed to in the presets file, _e.g._:

``` json
            "environment": {
                "DOGEN_PROJECTS_DIRECTORY": "${sourceDir}/projects",
                "CPP_REF_IMPL_PROJECTS_DIRECTORY":"${sourceDir}/test_data/cpp_ref_impl/projects",
                "CSHARP_REF_IMPL_PROJECTS_DIRECTORY":"${sourceDir}/test_data/csharp_ref_impl/Src"
            },
```

If you see any errors running CMake - _e.g._ "DOGEN_PROJECTS_DIRECTORY not
found.", _etc._ - please make sure the sub-modules were checked out correctly.
If all has gone according to plan, you should then see that Dogen correctly
recognises the additional models (where ```DIR``` is the top-level directory for
Dogen):

```
...
-- CMake Version: 3.24.2
-- DOGEN_PROJECTS_DIRECTORY=${DIR}/projects
-- CPP_REF_IMPL_PROJECTS_DIRECTORY=${DIR}/test_data/cpp_ref_impl/projects
-- CSHARP_REF_IMPL_PROJECTS_DIRECTORY=${DIR}/test_data/csharp_ref_impl/Src
...

```

You can run all tests as follows:

```
cmake --build --preset linux-clang-release --target rat
```

You can also use CTest to run the tests, _e.g._:

```
ctest --preset linux-clang-release
```

Or, the slightly more verbose incantation which has the same result:

```
cmake --build --preset linux-clang-release --target test
```

Though in the CTest form, the tests take slightly longer to run and the output
is a bit more verbose.

## Generation

If you'd like to run Dogen to regenerate all of its models, you can do so by
using the target ```generate_all_org``` or its abbreviation ```gao```. This is
useful, for example, to update the models to the latest version of Dogen, or
just to see how Dogen works. By default Dogen uses the current built version,
but you can also use another. For this you may need to tell CMake of its
location by setting ```CMAKE_PROGRAM_PATH```. After regeneration, you can then
use ```git diff``` to inspect the differences produced by regeneration, if any.
The build directory contains all of the logs, under the directory ```log```.
Example:

```
cmake --build --preset linux-clang-release --target gao
```

Replacing ```linux-clang-release``` with your platform and compiler.

**Important**: Please note that this does not regenerate the reference models.

# Documentation

Whilst we do not have a huge amount of documentation aimed at end users, there
is plenty of assorted material discussing Dogen. Most of the material is more
suitable for researchers.

## Videos

A number of videos are available discussing Dogen, gathered under "themed"
playlists:

- [MASD - Dogen Coding: PMM
  Refactor](https://www.youtube.com/playlist?list=PLwfrwe216gF0_1KPp_ir7ZCYLwnhdmBGJ):
  Series of coding videos on refactoring the Physical MetaModel. However, it
  beings where the previous series left off (MASD - Dogen Coding: Move to GitHub
  CI), _e.g._ on getting our CI and nightlies to work again.
- [MASD: An introduction to Model Assisted Software
  Development](https://youtube.com/playlist?list=PLwfrwe216gF3Qamk0YOSo5Csx1R_LplG0):
  Series of lectures on Model Assisted Software Development (MASD), the
  methodology put forward in my PhD and implemented by Dogen. This series of
  lectures was made in preparation for the /viva/.
- [MASD - Dogen
  Demos](https://www.youtube.com/playlist?list=PLwfrwe216gF0RmXOv8yCinHfv9QeSRDcm):
  end of sprint demos. Suitable for end users.
- [MASD - Dogen Coding: Move to GitHub
  CI](https://www.youtube.com/playlist?list=PLwfrwe216gF2qlIWKsBrL7UEsrEg8dXC0):
  Series of videos on moving Dogen from Travis CI to GitHub CI.
- [MASD - Dogen Coding: Org
  Codec](https://www.youtube.com/playlist?list=PLwfrwe216gF0wdVhy4fO1_QXJ-njWLSy4):
  Series of videos describing the addition of org-mode support to Dogen.
- [MASD - Dogen Coding: Relational Model for
  Tracing](https://www.youtube.com/playlist?list=PLwfrwe216gF3EzrrvwNFivnLSZ2l8X9k6):
  Narrates the design and implementation of the relational model for tracing.
- [MASD - Dogen Coding: Identification
  Refactor](https://www.youtube.com/playlist?list=PLwfrwe216gF0wxWcw33JrXI4R2gTN9E8X):
  Describes some of the woes we went through when updating the code-base to use
  the shiny new ```identification``` model.
- [MASD - Dogen Coding: Formatables
  Refactor](https://www.youtube.com/playlist?list=PLwfrwe216gF0NHaErGDeJrtGU8pAoNYlG):
  Series of videos covering the long-running formattables refactor in Dogen,
  which moved most technical space specific types into their Logical and
  Physical destinations.
- [MASD - MDE Paper of the
  Week](https://www.youtube.com/playlist?list=PLwfrwe216gF0wbLBkiOmpCpdaeAU66634):
  Series of relevant
  [MDE](https://en.wikipedia.org/wiki/Model-driven_engineering) papers that have
  been read to get a better understanding of the field. We try to read one of
  these a week, but we don't always succeed.

## Posts

Over time, a number of assorted blog posts have been published on Dogen, mainly
covering its development process:

- **[Nerd Food: The Refactoring
  Quagmire](https://mcraveiro.blogspot.co.uk/2018/01/nerd-food-refactoring-quagmire.html)**:
  How we solved the "refactoring ad infinitum" problem in Dogen development.
- **Nerd Food: Northwind, or Using Dogen with ODB**: Four part series on using
  Dogen with [ODB](https://www.codesynthesis.com/products/odb/). [Part
  I](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with.html),
  [Part
  II](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with_24.html),
  [Part
  III](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with.html),
  [Part
  IV](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with_25.html).
- **[Nerd Food: The Strange Case of the Undefined
  References](http://mcraveiro.blogspot.co.uk/2016/06/nerd-food-strange-case-of-undefined.html)**:
  Problems faced using Conan with Dogen.
- **[Nerd Food: On Product
  Backlog](http://mcraveiro.blogspot.co.uk/2016/01/nerd-food-on-product-backlogs.html)**:
  The importance of the Product Backlog in Dogen development.
- **[Nerd Food: Dogen: The Package Management
  Saga](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-dogen-package-management-saga.html)**:
  Dogen's attempt at finding a package management for C++.
- **[Nerd Food: Pull Request Driven
  Development](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-pull-request-driven.html)**:
  Not directly related to Dogen as we don't get many PRs, but may be of
  interest; reflections on the importance of a Pull-Request Driven Development
  approach.
- **[Nerd Food: Dogen: Lessons in Incremental
  Coding](http://mcraveiro.blogspot.co.uk/2014/09/nerd-food-dogen-lessons-in-incremental.html)**:
  How the Dogen development process works, via very small, incremental changes.

The [release notes](https://github.com/MASD-Project/dogen/releases) are also
worth perusing as contain quite a lot of material about Dogen's internals.

## Papers

We are strong believers in open academia so all of our papers are open.

- [Notes on Model Driven
  Engineering](https://zenodo.org/record/5812017#.YkmlftDMKXI): Background on
  MDE.
- [Survey of Special Purpose Code
  Generators](https://zenodo.org/record/5790875#.YkoSutDMKXI): Short survey of
  Open Source tools dedicated to special purpose code generation.
- [Experience Report of Industrial Adoption of Model Driven Development in the
  Financial Sector](https://zenodo.org/record/5767247#.YkoS6NDMKXI): Our prior
  experiences of using MDE on an industrial setting.
- [Model Assisted Software Development - a MDE-Based Software Development
  Methodology](https://uhra.herts.ac.uk/handle/2299/25708): PhD thesis.

# Reporting Problems

If you have encountered a failure building Dogen or running its unit tests,
please submit a bug report. It must include:

- the error messages;
- the versions of all dependencies (compiler, Boost etc);
- the operative system name and version.

If you find a bug whilst using Dogen with one of your models, please also
include:

- a small model reproducing the problem, called the [MWE (Minimum Working
  Example)](https://en.wikipedia.org/wiki/Minimal_working_example).
- the compressed log. By default, dogen creates a directory structure for all of
  its byproducts, in the folder it was executed from. It has the form
  ```dogen.byproducts/cli.generate.MODEL```, where ```MODEL``` is the file name
  and extension of the generated model. The log file is stored in this
  directory, with a name such as ```cli.generate.MODEL.log```.

Bugs can be submitted using [github
Issues](https://github.com/MASD-Project/dogen/issues).
