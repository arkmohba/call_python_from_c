FROM ubuntu:22.04

SHELL ["/bin/bash", "-c"]

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
 build-essential \
 python3 \
 python3-dev \
 python3-pip \
 git \
 clang-format \
 pkg-config \
 openjdk-21-jdk \
 curl \
 zip \
 && apt-get -y clean \
 && rm -rf /var/lib/apt/lists/*

ENV JAVA_HOME /usr/lib/jvm/java-21-openjdk-amd64
ENV PATH $PATH:$JAVA_HOME/bin

# for installing gradle
RUN curl -s "https://get.sdkman.io" | bash
RUN source "/root/.sdkman/bin/sdkman-init.sh" && sdk install gradle

RUN pip install \
 pybind11 \
 jep
