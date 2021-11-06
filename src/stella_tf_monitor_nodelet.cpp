#include "stella_tf_monitor/stella_tf_monitor_nodelet.h"
#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(stella_tf_monitor::StellaTfMonitorNodelet, nodelet::Nodelet);

namespace stella_tf_monitor {

StellaTfMonitorNodelet::StellaTfMonitorNodelet()
    : tf_buffer_(), tf_listener_(tf_buffer_) {
}

StellaTfMonitorNodelet::~StellaTfMonitorNodelet() {}

void StellaTfMonitorNodelet::onInit() {
    bool ok = init();
    if (!ok) {
        ROS_FATAL("Initialization failed");
    }
}

bool StellaTfMonitorNodelet::init() {
    getPrivateNodeHandle().param<std::string>("target_frame", target_frame_, "map");
    getPrivateNodeHandle().param<std::string>("source_frame", source_frame_, "base_link");
    double test_frequency;
    getPrivateNodeHandle().param<double>("test_frequency", test_frequency, 1.0);
    getPrivateNodeHandle().param<double>("timeout", timeout_, 0.1);

    updater_.setHardwareID("none");
    updater_.add("lookup", std::bind(&StellaTfMonitorNodelet::lookup_callback, this, std::placeholders::_1));
    timer_ = getNodeHandle().createTimer(ros::Duration(1.0 / test_frequency), &StellaTfMonitorNodelet::timer_callback, this);
    return true;
}

void StellaTfMonitorNodelet::timer_callback(const ros::TimerEvent&) {
    updater_.update();
}

void StellaTfMonitorNodelet::lookup_callback(diagnostic_updater::DiagnosticStatusWrapper& stat) {
    try {
        tf_buffer_.lookupTransform(target_frame_, source_frame_, ros::Time(0), ros::Duration(timeout_));
    }
    catch (tf2::TransformException& ex) {
        stat.summary(diagnostic_msgs::DiagnosticStatus::ERROR, ex.what());
        stat.add("target_frame", target_frame_);
        stat.add("source_frame", source_frame_);
        return;
    }
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "success");
    stat.add("target_frame", target_frame_);
    stat.add("source_frame", source_frame_);
}

} // namespace stella_tf_monitor
