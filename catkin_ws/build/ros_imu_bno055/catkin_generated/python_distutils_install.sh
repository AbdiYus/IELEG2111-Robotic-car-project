#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/src/ros_imu_bno055"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/install/lib/python3/dist-packages:/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/build" \
    "/usr/bin/python3" \
    "/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/src/ros_imu_bno055/setup.py" \
     \
    build --build-base "/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/build/ros_imu_bno055" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/install" --install-scripts="/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/install/bin"
