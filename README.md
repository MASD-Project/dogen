![Dogen Logo](https://raw.githubusercontent.com/DomainDrivenConsulting/dogen/master/doc/images/logo_with_message.png)

[![Licence](https://img.shields.io/badge/license-GPL_3-green.svg?dummy)](https://raw.githubusercontent.com/DomainDrivenConsulting/dogen/master/LICENCE)
[![Build Status](https://img.shields.io/travis/DomainDrivenConsulting/dogen.svg?label=linux/osx)](https://travis-ci.org/DomainDrivenConsulting/dogen)
[![Build Status](https://img.shields.io/appveyor/ci/mcraveiro/dogen.svg?label=windows)](https://ci.appveyor.com/project/mcraveiro/dogen)
[![Coverage Status](https://img.shields.io/coveralls/DomainDrivenConsulting/dogen.svg)](https://coveralls.io/r/DomainDrivenConsulting/dogen)
[![Issues](https://img.shields.io/github/issues/domaindrivenconsulting/dogen.svg)](https://github.com/DomainDrivenConsulting/dogen/issues)
[![Releases](https://badge.fury.io/gh/domaindrivenconsulting%2fdogen.svg)](https://github.com/domaindrivenconsulting/dogen/releases)
[![Gitter](https://img.shields.io/gitter/room/nwjs/nw.js.svg)](https://gitter.im/domaindrivenconsulting/dogen?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Coverity](https://img.shields.io/coverity/scan/9268.svg)](https://scan.coverity.com/projects/domaindrivenconsulting-dogen)
[![Download](https://api.bintray.com/packages/domaindrivenconsulting/Dogen/Dogen/images/download.svg?version=1.0.04) ](https://bintray.com/domaindrivenconsulting/Dogen/Dogen/1.0.04/link)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5d7fca8ac9a64ea8b8d35bc8b0d534b5)](https://www.codacy.com/app/marco-craveiro/dogen?utm_source=github.com&utm_medium=referral&utm_content=DomainDrivenConsulting/dogen&utm_campaign=badger)

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
([Dia test models](https://github.com/DomainDrivenConsulting/dogen/tree/master/test_data/yarn.dia/input)),
but we also support JSON
([JSON test models](https://github.com/DomainDrivenConsulting/dogen/tree/master/test_data/yarn.json/input)). Depending
on use cases and user demand, other frontends may follow.

The generated code contains most of the functionality required from a
typical C++ domain object such as serialisation, hashing, streaming
and so on. Whilst we intend for the suite to be useful out of the box
for most use cases, our end goal is to enable users to extend Dogen,
adapting it to the vagaries of their specific use cases.

Dogen also has experimental C# support, but it is not in feature
parity with the C++ support.

# Binary Packages

We provide binary packages
on [BinTray](https://bintray.com/domaindrivenconsulting/Dogen). At
present we support Debian Linux, OSX and Windows, all in 64-bit. The
packages are generated at the end of each sprint - with the exception
of Windows, where we generate packages on each commit due to
a
[problem with AppVeyor](http://help.appveyor.com/discussions/problems/6209-build-is-not-triggered-for-tag).

# Building From Source

The Dogen build has the following dependencies, across all operative
systems:

| Name   | Type      | Version                | Description                             |
|--------|-----------|------------------------|-----------------------------------------|
| Git    | Optional  | Any recent.    | Required to clone repository. Alternatively, download the zip from [GitHub](https://github.com/DomainDrivenConsulting/dogen).               |
| CMake  | Mandatory | 3.3 or later.  | Required to generate the build files.   |
| Boost  | Mandatory | 1.61 or later. | Earlier versions may also work, but patches are required. **Very Important**: We link statically against Boost at present, so be sure to build and install the static libraries.|
| ODB    | Optional  | Any recent.    | If you want to build the ORM examples, you need ODB. You will also need a backend such as Oracle, Postgres, etc.|

In addition to these dependencies, you will also need a build
toolchain. On Linux and OSX, you need a recent compiler - such as GCC
6 or Clang 3.8 - and Ninja or GNU Make. On Windows you will need
Visual Studio 2015 or later.

Once you have all dependencies installed and setup, you can then clone
the repository and setup the build directory, using the shell of your
choice (ours is Bash):

```
git clone git@github.com:DomainDrivenConsulting/dogen.git
cd dogen/build
mkdir output
cd output
```

On Linux and OSX, you can build using GNU Make as follows:

```
cmake ../..
make -j5 # number of cores available
```

We personally prefer Ninja:

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
