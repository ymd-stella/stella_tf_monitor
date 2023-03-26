#ifndef STELLA_TF_MONITOR_STELLA_TF_MONITOR_HPP
#define STELLA_TF_MONITOR_STELLA_TF_MONITOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <diagnostic_updater/diagnostic_updater.hpp>
#include <string>

namespace stella_tf_monitor {

class StellaTfMonitor : public rclcpp::Node {
public:
    StellaTfMonitor(const rclcpp::NodeOptions& options);
    void timer_callback();
    void lookup_callback(diagnostic_updater::DiagnosticStatusWrapper& stat);

private:
    diagnostic_updater::Updater updater_;
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    std::string target_frame_;
    std::string source_frame_;
    double timeout_;
};

} // namespace stella_tf_monitor

#endif // STELLA_TF_MONITOR_STELLA_TF_MONITOR_HPP
