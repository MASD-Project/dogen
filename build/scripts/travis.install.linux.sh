#!/bin/sh

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

# clang
if [ "$CXX" == "clang++" ]; then
    sudo sh -c "echo 'deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.7 main' >> /etc/apt/sources.list"
    sudo sh -c "echo 'deb http://llvm.org/apt/precise/ llvm-toolchain-precise main' >> /etc/apt/sources.list"
    wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
    sudo apt-get update -qq

    # clang 3.7
    sudo apt-get install --allow-unauthenticated -qq clang-3.7
    which clang-3.7
    export CXX="clang++-3.7" CC="clang-3.7"
fi

# g++
if [ "$CXX" = "g++" ]; then
    sudo apt-get install -qq g++-5
    export CXX="g++-5" CC="gcc-5" GCOV="gcov-5"
fi

# ninja
sudo apt-get install ninja-build

# conan
wget http://downloads.conan.io/latest_debian -O conan.deb
sudo dpkg -i conan.deb
rm conan.deb

# cmake
wget --no-check-certificate https://cmake.org/files/v3.4/cmake-3.4.1-Linux-x86_64.tar.gz -O /tmp/cmake-3.4.1-Linux-x86_64.tar.gz
tar xf /tmp/cmake-3.4.1-Linux-x86_64.tar.gz -C /tmp
sudo cp -r /tmp/cmake-3.4.1-Linux-x86_64/* /usr

# coverage
sudo pip install cpp-coveralls
