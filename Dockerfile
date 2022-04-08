FROM ubuntu:18.04

RUN apt-get update

RUN DEBIAN_FRONTEND=noninteractive \
    apt-get install -y git build-essential cmake ninja-build curl x11-apps lsb-release

RUN echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list && \
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - && \
    apt-get update

RUN DEBIAN_FRONTEND=noninteractive \
    apt-get install -y ros-melodic-desktop-full ros-melodic-heron* ros-melodic-uuv-simulator

RUN DEBIAN_FRONTEND=noninteractive \
    apt-get install -y python-rosdep python-rosinstall python-rosinstall-generator python-wstool && \
    sudo rosdep init && \
    rosdep update

RUN apt-get install -y python3-pip tmux vim

RUN pip3 install rospkg

ARG USERNAME=ros
RUN useradd --create-home --shell /bin/bash --password ${USERNAME} ${USERNAME}

USER ${USERNAME}

RUN echo ". /opt/ros/melodic/setup.sh" >> ~/.bashrc

RUN mkdir ~/catkin_ws && \
    cd ~/catkin_ws && \
    mkdir src && \
    . /opt/ros/melodic/setup.sh && \
    catkin_init_workspace src

CMD [ "bash" ]
