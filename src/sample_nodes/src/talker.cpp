#include "talker.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<talker::MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}