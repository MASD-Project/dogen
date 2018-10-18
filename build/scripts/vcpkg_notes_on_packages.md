# Linux

Building:

```
./vcpkg install libxml2 boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit
```

Add ```libodb libodb-pgsql```.

Exporting:

```
./vcpkg export libxml2 boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit --zip
```

# Windows

Building:

```
./vcpkg install --triplet x64-windows-static libxml2 boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit
```

Add ```libodb libodb-pgsql```.

Exporting:

```
./vcpkg export --triplet x64-windows-static libxml2 boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit --zip
```

# OSX

First patch boost:

```
diff --git a/ports/boost-modular-build-helper/CMakeLists.txt b/ports/boost-modular-build-helper/CMakeLists.txt
index dc4d13d..b0fe964 100644
--- a/ports/boost-modular-build-helper/CMakeLists.txt
+++ b/ports/boost-modular-build-helper/CMakeLists.txt
@@ -122,6 +122,9 @@ add_custom_target(boost ALL
         --hash
         -q

+        cxxstd=14
+        cxxflags=-fvisibility=hidden
+        cxxflags=-fvisibility-inlines-hidden
         architecture=x86
         threading=multi
         threadapi=pthread
diff --git a/toolsrc/CMakeLists.txt b/toolsrc/CMakeLists.txt
index a06cbae..834a459 100644
--- a/toolsrc/CMakeLists.txt
+++ b/toolsrc/CMakeLists.txt
@@ -2,7 +2,7 @@ cmake_minimum_required(VERSION 3.3)
 project(vcpkg C CXX)

 OPTION(DEFINE_DISABLE_METRICS "Option for disabling metrics" OFF)
 if(CMAKE_COMPILER_IS_GNUXX OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
     set(GCC 1)
 elseif(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
```

Building (exclude ```libxml2```):

```
./vcpkg install boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit
```

Exporting:

```
./vcpkg export boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit --zip
```
