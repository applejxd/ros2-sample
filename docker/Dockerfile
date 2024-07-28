# hadolint global ignore=DL3008

# https://gitlab.com/nvidia/container-images/cuda/blob/master/doc/supported-tags.md
FROM nvidia/cuda:11.8.0-cudnn8-devel-ubuntu22.04

# ビルド時のみ有効
ARG UNAME=nonroot
RUN useradd -m "${UNAME}" -s /bin/bash

# ------------ #
# Localization #
# ------------ #

# skip interactive timezone selection
# cf. https://sleepless-se.net/2018/07/31/docker-build-tzdata-ubuntu/
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive \
    apt-get install -y --no-install-recommends \
    tzdata \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
ENV TZ=Asia/Tokyo

# Japanese IME
# cf. https://qiita.com/n_oshiumi/items/cfe91c60730f602b38eb
RUN apt-get update \
    && apt-get install -y  --no-install-recommends  \
    locales \
    && locale-gen ja_JP.UTF-8 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
ENV LANG=ja_JP.UTF-8

#------#
# ROS2 #
#------#

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    software-properties-common curl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN add-apt-repository universe -y
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo "$UBUNTU_CODENAME") main" >> /etc/apt/sources.list.d/ros2.list

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    ros-humble-desktop \
    python3-colcon-common-extensions \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Copy configuration files
RUN echo "source /opt/ros/humble/setup.bash" >> "/home/${UNAME}/.bashrc" \
    && echo "source /home/${UNAME}/workspace/install/setup.bash" >> "/home/${UNAME}/.bashrc"

# Setup entrypoint
COPY entrypoint.sh /
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
WORKDIR /home/"${UNAME}"/workspace
CMD ["/bin/bash"]
