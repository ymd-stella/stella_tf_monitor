FROM ros:noetic
ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NOWARNINGS yes
ARG NUM_THREADS=1

RUN set -x && \
  apt-get update -y -qq && \
  : "install ROS packages" && \
  apt-get install -y -qq \
    ros-${ROS_DISTRO}-geometry2 \
    ros-${ROS_DISTRO}-diagnostic-updater && \
  : "remove cache" && \
  apt-get autoremove -y -qq && \
  rm -rf /var/lib/apt/lists/*

RUN set -x && \
  apt-get update -y -qq && \
  : "ci dependencies" && \
  apt-get install -y -qq \
    clang-format-6.0 && \
  apt-get autoremove -y -qq && \
  rm -rf /var/lib/apt/lists/*

RUN set -x && \
  apt-get update -y -qq && \
  : "dev dependencies" && \
  apt-get install -y -qq \
    rsync && \
  apt-get autoremove -y -qq && \
  rm -rf /var/lib/apt/lists/*

WORKDIR /catkin_ws
COPY . /catkin_ws/src/stella_tf_monitor

RUN set -x && \
  : "build ROS packages" && \
  bash -c "source /opt/ros/${ROS_DISTRO}/setup.bash; \
  catkin_make -j${NUM_THREADS}"

RUN set -x && \
  sh -c "echo 'source /opt/ros/${ROS_DISTRO}/setup.bash\nsource /catkin_ws/devel/setup.bash' >> ~/.bashrc"

CMD ["bash"]
