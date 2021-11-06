#ifndef STELLA_TF_MONITOR_STELLA_TF_MONITOR_NODELET_H
#define STELLA_TF_MONITOR_STELLA_TF_MONITOR_NODELET_H

#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <tf2_ros/transform_listener.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <string>

namespace stella_tf_monitor {

class StellaTfMonitorNodelet : public nodelet::Nodelet {
public:
    StellaTfMonitorNodelet();
    virtual ~StellaTfMonitorNodelet();
    void onInit() override;
    bool init();
    void timer_callback(const ros::TimerEvent&);
    void lookup_callback(diagnostic_updater::DiagnosticStatusWrapper& stat);

private:
    ros::Timer timer_;
    diagnostic_updater::Updater updater_;
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    std::string target_frame_;
    std::string source_frame_;
    double timeout_;
};

} // namespace stella_tf_monitor

#endif // STELLA_TF_MONITOR_STELLA_TF_MONITOR_NODELET_H