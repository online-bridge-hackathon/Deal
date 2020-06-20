FROM debian:stretch as deal-builder

RUN apt-get update
RUN apt-get install -y \
  git \
  build-essential \
  cmake

RUN git clone https://github.com/online-bridge-hackathon/Deal.git && \
  cd /Deal 
  
WORKDIR /Deal

RUN git clone https://github.com/woefulwabbit/ww-deal.git

RUN cmake . && \
  make

RUN Deal/server/api-server
