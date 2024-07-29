cmake_minimum_required(VERSION 3.8)
project(sample_nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#----------#
# packages #
#----------#

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

#-------#
# fetch #
#-------#

include(FetchContent)

FetchContent_Declare(
  GeographicLib
  GIT_REPOSITORY https://github.com/geographiclib/geographiclib.git
  GIT_TAG v2.4)
FetchContent_MakeAvailable(GeographicLib)

#---------#
# targets #
#---------#

add_executable(talker src/talker.cpp)
target_include_directories(talker PUBLIC include/talker)
target_link_libraries(talker
  GeographicLib::GeographicLib)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/listener.cpp)
target_include_directories(listener PUBLIC include/listener)
target_link_libraries(listener
  GeographicLib::GeographicLib)
ament_target_dependencies(listener rclcpp std_msgs)

install(TARGETS
  talker listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()
