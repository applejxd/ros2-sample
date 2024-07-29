build:
	colcon build --symlink-install --cmake-arg -DCMAKE_BUILD_TYPE=Debug
clean:
	rm -rf build install log
talk:
	ros2 run sample_nodes talker
listen:
	ros2 run sample_nodes listener