#!/usr/bin/env bash

sudo brew install protobuf-c protobuf zeromq32 boost

git clone https://github.com/zeromq/cppzmq.git
sudo cp cppzmq/zmq.hpp /usr/local/include/
