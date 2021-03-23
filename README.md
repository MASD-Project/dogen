![Dogen Logo](https://raw.githubusercontent.com/MASD-Project/dogen/master/doc/images/new_logo_with_message.png)

[![Licence](https://img.shields.io/badge/license-GPL_3-green.svg?dummy)](https://raw.githubusercontent.com/MASD-Project/dogen/master/LICENCE)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen?ref=badge_shield)
[![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)](https://github.com/MASD-Project/dogen/pulse/monthly)
[![Gitter](https://img.shields.io/gitter/room/nwjs/nw.js.svg)](https://gitter.im/MASD-Project/Lobby)
[![Issues](https://img.shields.io/github/issues/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/issues)
[![Contributors](https://img.shields.io/github/contributors/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/graphs/contributors)
[![PRs Welcome](https://img.shields.io/badge/PRs%20-welcome-brightgreen.svg)](https://github.com/MASD-Project/dogen/blob/master/CONTRIBUTING.md)
[![Github All Releases](https://img.shields.io/github/downloads/MASD-Project/dogen/total.svg)](https://github.com/MASD-Project/dogen/releases)
[![Code Quality: Cpp](https://img.shields.io/lgtm/grade/cpp/g/DomainDrivenConsulting/dogen.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/DomainDrivenConsulting/dogen/context:cpp)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5d7fca8ac9a64ea8b8d35bc8b0d534b5)](https://www.codacy.com/app/marco-craveiro/dogen?utm_source=github.com&utm_medium=referral&utm_content=MASD-Project/dogen&utm_campaign=badger)
[![Build Dashboard](https://img.shields.io/badge/cdash-dashboard-00cc00.svg)](https://my.cdash.org/index.php?project=MASD+Project+-+Dogen)
[![Report CI](https://report.ci/status/MASD-Project/dogen/badge.svg?branch=master)](https://report.ci/status/MASD-Project/dogen?branch=master)
[![Build Status](https://img.shields.io/travis/MASD-Project/dogen.svg?label=linux/osx)](https://travis-ci.org/MASD-Project/dogen)
[![Build Status](https://img.shields.io/appveyor/ci/mcraveiro/dogen.svg?label=windows)](https://ci.appveyor.com/project/mcraveiro/dogen)
[![Releases](https://img.shields.io/github/release/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/releases)
[![Binaries (Stable)](https://api.bintray.com/packages/masd-project/main/dogen/images/download.svg?version=1.0.30) ](https://bintray.com/masd-project/main/dogen/1.0.30/link)
[![GitHub commits](https://img.shields.io/github/commits-since/MASD-Project/dogen/v1.0.30.svg)](https://github.com/MASD-Project/dogen/commits/master)
[![Binaries (Unstable)](https://api.bintray.com/packages/masd-project/main/dogen/images/download.svg) ](https://bintray.com/masd-project/main/dogen/_latestVersion)
[![Documentation](https://github.com/MASD-Project/dogen/blob/master/assets/doxygen_badge.svg)]
[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://www.openhub.net/p/dogen/analyses/latest/languages_summary)
[![C++](https://img.shields.io/badge/std-C++17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![gcc-9](https://img.shields.io/badge/GCC-9-blue.svg)](https://www.gnu.org/software/gcc/gcc-9)
[![clang-9](https://img.shields.io/badge/CLANG-9-blue.svg)](http://releases.llvm.org/9.0.0/tools/clang/docs/ReleaseNotes.html)
[![msvc2017](https://img.shields.io/badge/MSVC-2017-blue.svg)](https://visualstudio.microsoft.com/vs/whatsnew/)
[![Project Stats](https://www.openhub.net/p/dogen/widgets/project_thin_badge.gif)](https://www.openhub.net/p/dogen)
[![Readme Score](http://readme-score-api.herokuapp.com/score.svg?url=https://github.com/masd-project/dogen)](http://clayallsopp.github.io/readme-score?url=https://github.com/masd-project/dogen)

# Overview

**Dogen** is the reference implementation of the MASD Project code
generator. MASD - Model Assisted Software Development - is a new
methodology for the development of software systems based on [MDE
(Model Driven
Engineering)](https://en.wikipedia.org/wiki/Model-driven_engineering). The
theoretical framework for MASD is under development as part of my PhD
thesis, and is not yet ready for public review. However, the
development of Dogen remains as it always was, an open source project
available to all.

In lay terms, Dogen's objective is to automate the development process
as much as possible: the user creates models in one of the supported
codecs and respecting a set of predefined restrictions; Dogen then
uses this input to generate a source code representation of the
model. At present the main frontend is [Org
Mode](https://orgmode.org/), though there is also support for
[Dia](https://en.wikipedia.org/wiki/Dia_(software)) and
[JSON](http://json.org/). Depending on use cases and user demand,
other frontends may follow.

The generated code contains most of the functionality required from a
typical C++ domain object such as serialisation, hashing, streaming
and so on. Whilst we intend for the application to be useful out of
the box for most use cases, our end goal is to enable users to extend
Dogen, adapting it to the vagaries of their specific needs. Note that
Dogen has experimental C# support, but it is not in feature parity
with C++ support.

Dogen provides a reference implementation for each supported language,
available as a separate git repo:

- [C++ Reference
  Implementation](https://github.com/MASD-Project/cpp_ref_impl). Models
  available [here](https://github.com/MASD-Project/cpp_ref_impl/tree/master/projects/cpp_ref_impl.models).
- [C# Reference
  Implementation](https://github.com/MASD-Project/csharp_ref_impl). Models
  available [here](https://github.com/MASD-Project/csharp_ref_impl/tree/master/Src/CSharpRefImpl.Models).

These are designed to give you a feel for how the generated code will
look like, and they attempt to exercise all of Dogen's functionality.

# Status

Whilst we welcome users and contributors, we think its important to
set clear expectations for the project. At the outset we must stress
that Dogen is an _academic project_ at present, with academic
goals. That is, our objectives are not (yet) to produce a fully
polished tool, ready for end users to work on industrial scale
projects. If for whatever reason you decide to use it, bear in mind
the following:

- our goal at present is to work out the MASD conceptual model. We
  will continue to refactor the code internally until it is consistent
  with the conceptual model. It will take a long while to get
  there. This means that adding new features is not a priority for
  Dogen development (though of course we are gathering a long list of
  ideas in our [product
  backlog](https://github.com/MASD-Project/dogen/blob/master/doc/agile/product_backlog.org)).
- in our quest for the conceptual model, we have broken and _we shall
  continue_ to break the API many times. This will manifest itself in
  having to update user models or in changes in the generated
  code. Features that have been working thus far may also be
  deprecated. We provide no guarantees of forward or backward
  compatibility; there isn't even an effort not to break these - in
  fact, quite the opposite, if its not in agreement with the
  conceptual model it must be changed. We do try to highlight these in
  the [release notes](https://github.com/MASD-Project/dogen/releases).
- we do have an [extensive suite of
  tests](https://my.cdash.org/index.php?project=MASD+Project+-+Dogen)
  (both generated and handcrafted), but these focus _only_ on Dogen's
  use cases. If you try any permutations outside these, it is likely
  you will find problems. The errors you will get will not be the most
  obvious.
- there is little to no documentation on Dogen. This will not change
  until we publish the PhD thesis. Resources are limited and they are
  all directed to development at present.
- for this tool to be useful in any way in its present state, you must
  have a good working knowledge of
  [MDE](https://en.wikipedia.org/wiki/Model-driven_engineering).

These warnings can probably best summarised as follows: "if it breaks,
you get to keep the pieces; and it will break, often". But if you find
such things fun, proceed with caution.

# Packages

Binary packages are available for each release on
[BinTray](https://bintray.com/masd-project/main/dogen) and
[GitHub](https://github.com/MASD-Project/dogen/releases) (links at the
end of each release note). The binaries cover Debian Linux, OSX and
Windows - 64-bit only. Packages are also generated for each commit,
and placed in BinTry only. Development is done from git master, so
latest should always be greatest, but you may want to use packages
from the previous sprint rather than what is currently under
development (see badges above).

---
**Notes**

- The OSX installer provides you with a DMG. Once you open it in Finder,
it mounts under ```/Volumes/```, e.g.:

```
/Volumes/dogen-${VERSION}-Darwin-x86_64/dogen.app/Contents/Resources/bin
```

Where ```${VERSION}``` is your Dogen version such as ```1.0.30```.

----

# Building

In order to build Dogen you will need a C++ toolchain. On Linux and
OSX, you'll need a recent compiler with C++ 17 support, such as [GCC
8](https://www.gnu.org/software/gcc/gcc-8) or [Clang
7](https://img.shields.io/badge/CLANG-7-cyan.svg) - and
[Ninja](https://ninja-build.org/manual.html) or [GNU
Make](https://www.gnu.org/software/make/). On Windows you'll need
[Visual Studio
2017](https://visualstudio.microsoft.com/vs/whatsnew/). Older
compilers may work, but we try to always use the most recent releases
in MASD. So, if you can, please try using to those.

Dogen has the following additional dependencies, across all operative systems:

| Name   | Type      | Version                | Description                             |
|--------|-----------|------------------------|-----------------------------------------|
| [CMake](https://cmake.org/)  | Mandatory | 3.12 or later.  | Required to generate the build files.Earlier versions may also work.  |
| [Boost](https://boost.org)  | Mandatory | 1.68 or later. | Earlier versions may also work, but patches may be needed. **Very Important**: We link statically against Boost at present, so be sure to build and install the static libraries.|
| [LibXml2](http://xmlsoft.org/) | Mandatory | 2.9.4 | Earlier versions may work but haven't been tested.|
| [DTL](https://github.com/cubicdaiya/dtl) | Mandatory | 1.19 | Earlier versions may work but haven't been tested.|

Though Dogen should build fine with package manager supplied
libraries - or even with hand-built dependencies - the easiest way to
setup a development environment on all supported platforms is by using
[vcpkg](https://github.com/Microsoft/vcpkg). We have a vcpkg fork
with a [MASD
Branch](https://github.com/MASD-Project/vcpkg/commits/masd) that is
setup correctly to build both Dogen and the C++ Reference
Implementation and is used/validated by our CI. If at all possible,
please use this instead of the mainline vcpkg because it contains a
few changes that cannot be easily mainlined (C++ 17 on all
dependencies, ODB 2.5, etc).

Either way, you can compile vcpkg as per [vcpkg
documentation](https://github.com/Microsoft/vcpkg/blob/master/README.md),
and then install packages by running:

```
./vcpkg install libxml2 boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit dtl
```

---
**Notes**

- The default vcpkg triplet on Windows [is 32-bit
dynamic](https://github.com/Microsoft/vcpkg/issues/1254) whereas we
build with ```--triplet x64-windows-static``` (e.g. add this to the
line above if you are on Windows). If you are experiencing [weird and
wonderful errors](https://github.com/Microsoft/vcpkg/issues/4447)
building Dogen, check your triplet.
- If you are on OSX, you probably should rely on the system's LibXML2
(e.g. remove it from the vcpkg list above) or else you may see [some
interesting linking
errors](https://github.com/Microsoft/vcpkg/issues/4476) related to
```iconv```.
- Remember that the recommended compiler for vcpkg on OSX is Homebrew's GCC. If
  you do decide to use XCode Clang or LLVM Clang, be ready to handle [some pain](https://github.com/Microsoft/vcpkg/issues/4476). In addition, beware that for some reason [boost does
  not
  default](https://github.com/Microsoft/vcpkg/issues/4476#issuecomment-430175834)
  to C++ 14. You'll need to add ```cxxstd=14```. Our vcpkg repo has fixes for this.
- Setting up ODB is not quite as simple as we would like. If you are using a
  stable version of ODB such as 2.4 you can just install the compiler and libraries
  from your distribution packages or download the compiler and libraries
  form the [ODB downloads page](https://www.codesynthesis.com/products/odb/download.xhtml)
  or even install it from vcpkg (i.e., add ```libodb libodb-boost libodb-pgsql```
  to the vcpkg line above). However, as ODB 2.4 has limited support for C++ 17,
  you will likely end up needing the beta version 2.5. This is not as trivial. If
  you definitely want to do this, follow the instructions in the ODB documentation
  and then ensure you place the installed files in the path (e.g. setup ```PATH```,
  ```CMAKE_INCLUDE_PATH``` and ```CMAKE_LIBRARY_PATH``` accordingly).

---

Once you have all dependencies set up, you can then clone the
repository and create the build directory:

```
git clone https://github.com/MASD-Project/dogen.git
cd dogen/build
mkdir output
cd output
```

On Linux and OSX, you can build using GNU Make as follows:

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_VCPKG_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake ../..
make -j${CORES}
```

Where ```PATH_TO_VCPKG_DIR``` is the directory in which you've
downloaded and built vcpkg and ```CORES``` is the number of cores
available on your machine. Alternatively, you can use Ninja:

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_VCPKG_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake ../.. -G Ninja
ninja -j${CORES}
```

On Windows, the incantation is slightly different:

```
cmake -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_VCPKG_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static ../.. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release --target ALL_BUILD
```

---
**Notes**

- If you are **not** using vcpkg, you can omit ```-DCMAKE_TOOLCHAIN_FILE``` and ```-DVCPKG_TARGET_TRIPLET```. However if the dependencies are not on the standard paths, you must then set
```CMAKE_INCLUDE_PATH``` and ```CMAKE_LIBRARY_PATH``` accordingly, e.g.:

```
CMAKE_INCLUDE_PATH=/my/boost/include/path CMAKE_LIBRARY_PATH=/my/boost/lib/path cmake ../..
```

- If you are using vcpkg in Windows, **make sure** you are targeting
the right triplet. As explained above. We tend to use
```x64-windows-static```. If you have installed all the libraries (or
you are using our export) but somehow CMake just doesn't seem to be
able to find them, the likely cause is the wrong vcpkg triplet.
- Note that we are targeting 64-bit builds (e.g. ```"Visual Studio 15
2017 Win64"```). If you want to do a 32-bit build, you will need to
have a vcpkg export built for 32-bits. Note also that if you forget to set the
generator, it will default to 32-bits and you'll experience weird and
wonderful linker errors.

---

## Testing

If you'd like to run the project tests, execute the target
```run_all_tests``` or its abbreviation ```rat```. This is sufficient
if you just need to gain some confidence on the code generator as we
perform tests against Dogen's own models. However, if you are trying
to submit a PR that changes the behaviour of the code generator, you
must also run the tests against the C++ and C# reference
implementation models, as well as a ["Frozen" version of
Dogen](https://github.com/MASD-Project/dogen/releases/tag/v1.0.30). For
this you need to download the zips or clone the repositories locally:

- [C++ Reference Implementation](https://github.com/MASD-Project/cpp_ref_impl)
- [C# Reference Implementation](https://github.com/MASD-Project/csharp_ref_impl)
- [Frozen](https://github.com/MASD-Project/frozen)

Then, point the corresponding environment variables to the respective
projects directory, e.g.:

```
export FROZEN_PROJECTS_DIRECTORY=${DIR}/frozen/projects
export MASD_CPP_REF_IMPL_PROJECTS_DIRECTORY=${DIR}/cpp_ref_impl/projects
export MASD_CSHARP_REF_IMPL_PROJECTS_DIRECTORY=${DIR}/csharp_ref_impl/Src
```

Where ```DIR``` is set to the local directory where you placed the
repositories. You should then ensure Dogen correctly recognises the
additional models (```${DIR}``` being the local directory):

```
...
-- CMake Version: 3.13.4
-- DOGEN_PROJECTS_DIRECTORY=${DIR}/dogen/projects
-- FROZEN_PROJECTS_DIRECTORY=${DIR}/frozen/projects
-- CPP_REF_IMPL_PROJECTS_DIRECTORY=${DIR}/cpp_ref_impl/projects
-- CSHARP_REF_IMPL_PROJECTS_DIRECTORY=SOME_PATH/csharp_ref_impl/Src
...

```

Executing the ```run_all_tests``` target will now also include the
reference implementations. Make sure your changes do not break these models.

## Generation

If you'd like to run Dogen to regenerate all of its models, you can do
so by using the target ```generate_all_org``` or its abbreviation
```gao```. This is useful, for example, to update the models to the
latest version of Dogen, or just to see how Dogen works. By default
Dogen uses the current built version, but you can also use
another. For this you may need to tell CMake of its location by
setting ```CMAKE_PROGRAM_PATH```:

```
CMAKE_PROGRAM_PATH=/path/to/dogen/binary cmake ../..
```

After regeneration, you can then use ```git diff``` to inspect the
differences produced by regeneration, if any. The build directory
contains all of the logs, under the directory ```log```.

# Videos

A number of videos are now available discussing Dogen, gathered under
"themed" playlists:

- [MASD - Dogen
  Demos](https://www.youtube.com/playlist?list=PLwfrwe216gF0RmXOv8yCinHfv9QeSRDcm):
  end of sprint demos.
- [MASD - Dogen Coding: Org
  Codec](https://www.youtube.com/playlist?list=PLwfrwe216gF0wdVhy4fO1_QXJ-njWLSy4):
  Series of videos describing the addition of org-mode support to
  Dogen.
- [MASD - Dogen Coding: Relational Model for
  Tracing](https://www.youtube.com/playlist?list=PLwfrwe216gF3EzrrvwNFivnLSZ2l8X9k6):
  Narrates the design and implementation of the relational model for tracing.
- [MASD - Dogen Coding: Identification Refactor](https://www.youtube.com/playlist?list=PLwfrwe216gF0wxWcw33JrXI4R2gTN9E8X): Describes some of the woes we went through when updating the code-base to use the shiny new ```identification``` model.
- [MASD - Dogen Coding: Formatables Refactor](https://www.youtube.com/playlist?list=PLwfrwe216gF0NHaErGDeJrtGU8pAoNYlG): Series of videos covering the long-running formattables refactor in Dogen, which moved most technical space specific types into their Logical and Physical destinations.
- [MASD - MDE Paper of the
  Week](https://www.youtube.com/playlist?list=PLwfrwe216gF0wbLBkiOmpCpdaeAU66634):
  Series of relevant
  [MDE](https://en.wikipedia.org/wiki/Model-driven_engineering) papers
  that have been read to get a better understanding of the field. We
  try to read one of these a week, but we don't always succeed.

# Posts

Over time, a number of assorted blog posts have been published on
Dogen, mainly covering its development process:

- **[Nerd Food: The Refactoring Quagmire](https://mcraveiro.blogspot.co.uk/2018/01/nerd-food-refactoring-quagmire.html)**: How we solved the "refactoring ad infinitum" problem in Dogen development.
- **Nerd Food: Northwind, or Using Dogen with ODB**: Four part series on using Dogen with [ODB](https://www.codesynthesis.com/products/odb/). [Part I](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with.html), [Part II](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with_24.html), [Part III](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with.html), [Part IV](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with_25.html).
- **[Nerd Food: The Strange Case of the Undefined References](http://mcraveiro.blogspot.co.uk/2016/06/nerd-food-strange-case-of-undefined.html)**: Problems faced using Conan with Dogen.
- **[Nerd Food: On Product Backlog](http://mcraveiro.blogspot.co.uk/2016/01/nerd-food-on-product-backlogs.html)**: The importance of the Product Backlog in Dogen development.
- **[Nerd Food: Dogen: The Package Management Saga](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-dogen-package-management-saga.html)**: Dogen's attempt at finding a package management for C++.
- **[Nerd Food: Pull Request Driven Development](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-pull-request-driven.html)**: Not directly related to Dogen as we don't get many PRs, but may be of interest; reflections on the importance of a Pull-Request Driven Development approach.
- **[Nerd Food: Dogen: Lessons in Incremental Coding](http://mcraveiro.blogspot.co.uk/2014/09/nerd-food-dogen-lessons-in-incremental.html)**: How the Dogen development process works, via very small, incremental changes.

The [release notes](https://github.com/MASD-Project/dogen/releases)
are also worth perusing as contain quite a lot of material about
Dogen's internals.

# Reporting Problems

If you have encountered a failure building Dogen or running its unit
tests, please submit a bug report. It must include:

- the error messages;
- the versions of all dependencies (compiler, Boost etc);
- the operative system name and version;

If you find a bug whilst using Dogen with one of your models, please
also include:

- a small model reproducing the problem, called the [MWE (Minimum
  Working
  Example)](https://en.wikipedia.org/wiki/Minimal_working_example).
- the compressed log. By default, dogen creates a directory structure
  for all of its byproducts, in the folder it was executed from. It
  has the form ```dogen.byproducts/cli.generate.MODEL```, where
  ```MODEL``` is the file name and extension of the generated
  model. The log file is stored in this directory, with a name such as
  ```cli.generate.MODEL.log```.

Bugs can be submitted
using [github Issues](https://github.com/MASD-Project/dogen/issues).
