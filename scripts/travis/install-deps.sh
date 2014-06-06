#!/usr/bin/env bash

# Install cppcheck on Ubuntu from source since we need a recent version.
# Will not be needed once travis is updated to Ubuntu 14.04.
install_cppcheck()
{
    git clone https://github.com/danmar/cppcheck.git
    cd cppcheck
    git checkout 1.65
    make SRCDIR=build CFGDIR=/usr/share/cppcheck HAVE_RULES=no -j2
    sudo make install
    # On travis cppcheck ignores CFGDIR. Instead, it looks in $PWD. Compare
    # strace output.
    sudo install -m644 ./cfg/* ../
}

if [ $# -ne 1 ]; then
    echo "Error: expected OS type argument." >&2
    exit 1
fi

os=$1

case "$os" in
    linux)
        sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
        sudo apt-get -qq update
        sudo apt-get -qq install g++-4.8
        sudo apt-get install libprotobuf-dev protobuf-compiler libzmq3-dev \
            libboost-all-dev doxygen
        sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
        sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
        install_cppcheck
        ;;
    osx)
        brew update
        brew install protobuf-c protobuf boost openssl cppcheck
        brew link --force openssl
        ;;
    *)
        echo "Error: unknown OS '$os'" >&2
        exit 1
        ;;
esac

git clone https://github.com/zeromq/cppzmq.git
sudo cp cppzmq/zmq.hpp /usr/local/include/
