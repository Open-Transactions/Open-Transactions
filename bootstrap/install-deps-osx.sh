#!/usr/bin/env bash

brew update
brew install protobuf-c protobuf boost openssl
brew link --force openssl

git clone https://github.com/zeromq/cppzmq.git
sudo cp cppzmq/zmq.hpp /usr/local/include/
