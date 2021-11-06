# stella_tf_monitor

## Getting started

```bash
docker build -t stella-tf-monitor .
docker run --rm -it --net=host stella-tf-monitor
roscore&
rosrun stella_tf_monitor stella_tf_monitor_node
```
