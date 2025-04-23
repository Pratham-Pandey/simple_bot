#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <cmath>
#include <vector>

class LidarFilter : public rclcpp::Node
{
public:
    LidarFilter()
    : Node("lidar_filter")
    {
        sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&LidarFilter::scan_callback, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::LaserScan>("/filtered_scan", 10);
    }

private:
    void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        const float angle_min = msg->angle_min;
        const float angle_increment = msg->angle_increment;

        const float start_angle = 0.0;
        const float end_angle = M_PI * 2.0f / 3.0f; // 120 degrees in radians

        int start_index = static_cast<int>((start_angle - angle_min) / angle_increment);
        int end_index = static_cast<int>((end_angle - angle_min) / angle_increment);

        start_index = std::max(0, start_index);
        end_index = std::min(static_cast<int>(msg->ranges.size()), end_index);

        auto filtered_msg = *msg;
        filtered_msg.ranges = std::vector<float>(msg->ranges.begin() + start_index, msg->ranges.begin() + end_index);

        // Updating angle_min and angle_max accordingly
        filtered_msg.angle_min = angle_min + start_index * angle_increment;
        filtered_msg.angle_max = angle_min + end_index * angle_increment;

        pub_->publish(filtered_msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr pub_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LidarFilter>());
    rclcpp::shutdown();
    return 0;
}
