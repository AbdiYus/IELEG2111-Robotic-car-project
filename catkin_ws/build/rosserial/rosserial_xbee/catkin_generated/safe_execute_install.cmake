execute_process(COMMAND "/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/build/rosserial/rosserial_xbee/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/mosa/IELEG2111-Robotic-car-project/catkin_ws/build/rosserial/rosserial_xbee/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
