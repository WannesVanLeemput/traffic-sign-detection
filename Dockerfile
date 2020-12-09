# base image is ubuntu 14.04
FROM ubuntu:trusty
# Update the image to the latest packages
RUN apt-get update && apt-get upgrade -y
# Install necesarry packages for project
RUN apt-get install cmake=2.8.12.2-0ubuntu3 -y
RUN apt-get install libeigen3-dev=3.2.0-8 -y
RUN apt-get install libopencv-dev -y
RUN apt-get install libgtest-dev -y
RUN apt-get install git -y

# compile libgtest
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt
RUN make
RUN cp *.a /usr/lib

# install traffic sign detection
WORKDIR ../../../home/
RUN mkdir traffic-sign-detection
WORKDIR traffic-sign-detection
COPY . .
RUN mkdir build
RUN mkdir data
WORKDIR build
RUN cmake ../src
RUN make