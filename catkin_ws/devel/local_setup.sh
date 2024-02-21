#!/usr/bin/env sh
# generated from catkin/cmake/template/local_setup.sh.in

# since this file is sourced either use the provided _CATKIN_SETUP_DIR
# or fall back to the destination set at configure time
<<<<<<< HEAD
: ${_CATKIN_SETUP_DIR:=/home/didmup/IELEG2111-Robotic-car-project/catkin_ws/devel}
=======
: ${_CATKIN_SETUP_DIR:=/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/devel}
>>>>>>> cc2ca8602a730e37fbe04d008cad5acbed12b961
CATKIN_SETUP_UTIL_ARGS="--extend --local"
. "$_CATKIN_SETUP_DIR/setup.sh"
unset CATKIN_SETUP_UTIL_ARGS
