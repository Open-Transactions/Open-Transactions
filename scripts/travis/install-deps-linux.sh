#!/usr/bin/env bash

sudo apt-get install libprotobuf-dev protobuf-compiler libzmq3-dev libboost-all-dev doxygen
git clone https://github.com/zeromq/cppzmq.git
sudo cp cppzmq/zmq.hpp /usr/local/include/
