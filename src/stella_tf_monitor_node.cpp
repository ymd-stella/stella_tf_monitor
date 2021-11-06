#include "stella_tf_monitor/stella_tf_monitor_nodelet.h"
#include <nodelet/loader.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "stella_tf_monitor_node");
    nodelet::Loader nodelet;
    nodelet::M_string remap(ros::names::getRemappings());
    nodelet::V_string nargv;
    std::string nodelet_name = ros::this_node::getName();
    nodelet.load(nodelet_name, "stella_tf_monitor/StellaTfMonitorNodelet", remap, nargv);
    ros::spin();
    return 0;
}
