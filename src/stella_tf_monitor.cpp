#include "stella_tf_monitor/stella_tf_monitor.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace stella_tf_monitor {

StellaTfMonitor::StellaTfMonitor(const rclcpp::NodeOptions& options = rclcpp::NodeOptions())
    : Node("stella_tf_monitor", options), updater_(this), tf_buffer_(get_clock()), tf_listener_(tf_buffer_) {
    target_frame_ = std::string("map");
    target_frame_ = declare_parameter("target_frame", target_frame_);
    source_frame_ = std::string("base_link");
    source_frame_ = declare_parameter("source_frame", source_frame_);
    timeout_ = 0.1;
    timeout_ = declare_parameter("timeout", timeout_);

    updater_.setHardwareID("none");
    updater_.add("lookup", this, &StellaTfMonitor::lookup_callback);
}

void StellaTfMonitor::lookup_callback(diagnostic_updater::DiagnosticStatusWrapper& stat) {
    try {
        tf_buffer_.lookupTransform(target_frame_, source_frame_, tf2::TimePointZero, tf2::durationFromSec(timeout_));
    }
    catch (tf2::TransformException& ex) {
        stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, ex.what());
        stat.add("target_frame", target_frame_);
        stat.add("source_frame", source_frame_);
        return;
    }
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "success");
    stat.add("target_frame", target_frame_);
    stat.add("source_frame", source_frame_);
}

} // namespace stella_tf_monitor

RCLCPP_COMPONENTS_REGISTER_NODE(stella_tf_monitor::StellaTfMonitor)
