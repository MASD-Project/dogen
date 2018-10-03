![Dogen Logo](https://raw.githubusercontent.com/MASD-Project/dogen/master/doc/images/new_logo_with_message.png)

[![Licence](https://img.shields.io/badge/license-GPL_3-green.svg?dummy)](https://raw.githubusercontent.com/MASD-Project/dogen/master/LICENCE)
[![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)](https://github.com/MASD-Project/dogen/pulse/monthly)
[![Gitter](https://img.shields.io/gitter/room/nwjs/nw.js.svg)](https://gitter.im/MASD-Project/Lobby)
[![Issues](https://img.shields.io/github/issues/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/issues)
[![Github All Releases](https://img.shields.io/github/downloads/MASD-Project/dogen/total.svg)](https://github.com/MASD-Project/dogen/releases)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5d7fca8ac9a64ea8b8d35bc8b0d534b5)](https://www.codacy.com/app/marco-craveiro/dogen?utm_source=github.com&utm_medium=referral&utm_content=MASD-Project/dogen&utm_campaign=badger)
[![Build Status](https://img.shields.io/travis/MASD-Project/dogen.svg?label=linux/osx)](https://travis-ci.org/MASD-Project/dogen)
[![Build Status](https://img.shields.io/appveyor/ci/mcraveiro/dogen.svg?label=windows)](https://ci.appveyor.com/project/mcraveiro/dogen)
[![Coverage Status](https://coveralls.io/repos/github/MASD-Project/dogen/badge.svg?branch=master)](https://coveralls.io/github/MASD-Project/dogen?branch=master)
[![Releases](https://img.shields.io/github/release/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/releases)
[![GitHub commits](https://img.shields.io/github/commits-since/MASD-Project/dogen/v1.0.08.svg)](https://github.com/MASD-Project/dogen/commits/master)
[![Contributors](https://img.shields.io/github/contributors/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/graphs/contributors)
[![Download](https://api.bintray.com/packages/masd-project/Dogen/dogen/images/download.svg?version=v1.0.08)](https://bintray.com/masd-project/Dogen/dogen/v1.0.08)
[![Language](https://img.shields.io/badge/language-c++-blue.svg)](https://www.openhub.net/p/dogen/analyses/latest/languages_summary)
[![C++](https://img.shields.io/badge/std-c++14-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B14)
[![msvc2015](https://img.shields.io/badge/MSVC-2015-ff69b4.svg)](https://visualstudio.microsoft.com/vs/older-downloads/)
[![gcc-6.3.0](https://img.shields.io/badge/GCC-6.3.0-ff69b4.svg)](https://www.gnu.org/software/gcc/gcc-6)
[![clang-3.7](https://img.shields.io/badge/CLANG-3.7-ff69b4.svg)](http://releases.llvm.org/3.7.0/tools/clang/docs/ReleaseNotes.html)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen?ref=badge_shield)
[![Coverity](https://img.shields.io/coverity/scan/16865.svg)](https://scan.coverity.com/projects/masd-project-dogen)
[![Project Stats](https://www.openhub.net/p/dogen/widgets/project_thin_badge.gif)](https://www.openhub.net/p/dogen)

# Overview

**Dogen** is a suite of tools focusing on
bringing [Model Driven Software Development](https://en.wikipedia.org/wiki/Model-driven_software_development) (MDSD)
workflows to C++ development. In lay terms, our main objective is to
automate the development process as much as possible: the user creates
domain models according to one of the supported frontend formats and
respecting a set of predefined restrictions; Dogen then uses this
input to generate a source code representation of the model. At
present the main frontend
is [Dia](https://en.wikipedia.org/wiki/Dia_(software))
([Dia test models](https://github.com/MASD-Project/dogen/tree/master/test_data/yarn.dia/input)),
but we also support JSON
([JSON test models](https://github.com/MASD-Project/dogen/tree/master/test_data/yarn.json/input)). Depending
on use cases and user demand, other frontends may follow.

The generated code contains most of the functionality required from a
typical C++ domain object such as serialisation, hashing, streaming
and so on. Whilst we intend for the suite to be useful out of the box
for most use cases, our end goal is to enable users to extend Dogen,
adapting it to the vagaries of their specific needs.

Note that Dogen has experimental C# support, but it is not in feature
parity with C++ support.

# Binary Packages

Binary packages are available on
[BinTray](https://bintray.com/masd-project/Dogen/), for
Debian Linux, OSX and Windows - all in 64-bit. Packages are generated
at the end of each sprint - with the exception of Windows, where we
generate them on each commit due to a [problem with
AppVeyor](http://help.appveyor.com/discussions/problems/6209-build-is-not-triggered-for-tag).

# Building From Source

Dogen has the following dependencies, across all operative systems:

| Name   | Type      | Version                | Description                             |
|--------|-----------|------------------------|-----------------------------------------|
| Git    | Optional  | Any recent.    | Required to clone repository. Alternatively, download the zip from [GitHub](https://github.com/MASD-Project/dogen).               |
| CMake  | Mandatory | 3.3 or later.  | Required to generate the build files.   |
| Boost  | Mandatory | 1.61 or later. | Earlier versions may also work, but patches are required. **Very Important**: We link statically against Boost at present, so be sure to build and install the static libraries.|
| ODB    | Optional  | Any recent.    | If you want to build the ORM examples, you need ODB. You will also need a backend such as Oracle, Postgres, etc.|

In addition, you will also need a build toolchain. On Linux and OSX,
you'll need a moderately recent compiler - such as GCC 6 or Clang
3.7 - and Ninja or GNU Make. On Windows you'll need Visual Studio 2015
or later.

Once you have all dependencies installed and set up, you can then clone
the repository and create the build directory, using the shell of your
choice (ours is Bash):

```
git clone git@github.com:MASD-Project/dogen.git
cd dogen/build
mkdir output
cd output
```

On Linux and OSX, you can build using GNU Make as follows:

```
cmake ../..
make -j5 # number of cores available
```

Alternatively, you can use Ninja:

```
cmake ../.. -G Ninja
ninja -j5 # number of cores available
```

On Windows, the incantation is slightly different:

```
cmake ../.. -DCMAKE_BUILD_TYPE=Release -G 'Visual Studio 14 2015 Win64'
cmake --build . --config Release --target ALL_BUILD
```

Note that if you have installed Boost on a non-standard location, you
need to set ```CMAKE_INCLUDE_PATH``` and ```CMAKE_LIBRARY_PATH```
accordingly:

```
CMAKE_INCLUDE_PATH=/my/boost/include/path CMAKE_LIBRARY_PATH=/my/boost/lib/path cmake ../..
```

# Demo

We don't really have a recent demo of Dogen, but this fairly old one
should give you an idea of its workflow:

[![Alt text](https://img.youtube.com/vi/Z7k8qbImXkU/0.jpg)](https://youtu.be/Z7k8qbImXkU)

# Blog Posts

Over time a number of assorted blog posts have been published on
Dogen, mainly covering its development process:

- **[Nerd Food: The Refactoring Quagmire](https://mcraveiro.blogspot.co.uk/2018/01/nerd-food-refactoring-quagmire.html)**: How we solved the "refactoring ad infinitum" problem in Dogen development.
- **Nerd Food: Northwind, or Using Dogen with ODB**: Four part series on using Dogen with [ODB](https://www.codesynthesis.com/products/odb/). [Part I](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with.html), [Part II](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with_24.html), [Part III](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with.html), [Part IV](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with_25.html).
- **[Nerd Food: The Strange Case of the Undefined References](http://mcraveiro.blogspot.co.uk/2016/06/nerd-food-strange-case-of-undefined.html)**: Problems faced using Conan with Dogen.
- **[Nerd Food: On Product Backlog](http://mcraveiro.blogspot.co.uk/2016/01/nerd-food-on-product-backlogs.html)**: The importance of the Product Backlog in Dogen development.
- **[Nerd Food: Dogen: The Package Management Saga](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-dogen-package-management-saga.html)**: Dogen's attempt at finding a package management for C++.
- **[Nerd Food: Pull Request Driven Development](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-pull-request-driven.html)**: Not directly related to Dogen as we don't get many PRs, but may be of interest; reflections on the importance of a Pull-Request Driven Development approach.
- **[Nerd Food: Dogen: Lessons in Incremental Coding](http://mcraveiro.blogspot.co.uk/2014/09/nerd-food-dogen-lessons-in-incremental.html)**: How the Dogen development process works, via very small, incremental changes.

# Reporting Problems

If you have encountered a failure building Dogen or running its unit
tests, please submit a bug report. It must include:

- the error messages;
- the versions of all dependencies (compiler, Boost etc);
- the operative system name and version;

If you find a bug whilst using Dogen with one of your models, please
also include:

- a small model reproducing the problem;
- the compressed log; it is located under the directory where you
  executed Dogen and named ```dogen.knitter.MODEL.log``` where
  ```MODEL``` is the name of the model you ran against.

Bugs can be submitted
using [github Issues](https://github.com/kitanda/dogen/issues).
