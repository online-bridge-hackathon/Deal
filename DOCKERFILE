FROM debian:stretch as deal-builder

RUN apt-get update
RUN apt-get install -y \
  git \
  build-essential \
  cmake
  
RUN mkdir -p /app

RUN git clone https://github.com/online-bridge-hackathon/Deal.git /app && \
  cd /app && \

RUN mkdir /build && \
  cd build && \
  cmake .. && \
  make

WORKDIR /app

RUN server/api-server
