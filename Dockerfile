FROM debian:buster as deal-builder

# Install build dependecies
RUN apt-get update
RUN apt-get install -y --no-install-recommends \
  g++ \
  cmake \
  ninja-build

ARG PREFIX=/usr/local
ARG BUILD_TYPE=RelWithDepInfo

RUN mkdir -p /build/pistache && mkdir -p /build/json

# Fetch source from the build context
ADD pistache       /sources/pistache
# Build the pistache library
RUN cmake -DCMAKE_INSTALL_PREFIX=$PREFIX \
      -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -G Ninja \
      -S /sources/pistache \
      -B /build/pistache && \
      ninja install -C /build/pistache

ADD json           /sources/json
# Build the json library
RUN cmake -DCMAKE_INSTALL_PREFIX=$PREFIX \
      -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DJSON_BuildTests=Off \
      -G Ninja \
      -S /sources/json \
      -B /build/json && \
      ninja install -C /build/json

ADD ww-deal        /sources/ww-deal
ADD server         /sources/server
ADD CMakeLists.txt /sources/

# Build sources
RUN cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -G Ninja \
      -S /sources \
      -B /build && \
      ninja install -C /build

# Create a clean server image
FROM debian:buster as deal-image

# Install runtime dependencies
RUN apt-get update && \
  apt-get install -y --no-install-recommends \
    libatomic1

# Copy required runtime files
COPY --from=deal-builder /usr/local/lib/libpistache.so.0.* /usr/local/lib/
COPY --from=deal-builder /usr/local/bin/api-server /usr/local/bin/api-server

# Add the library to the lookup cache
RUN ln -s /usr/local/lib/libpistache.so.0.* /usr/local/lib/libpistache.so.0 && \
      ldconfig

# Setup runtime options for the server
WORKDIR /usr/local/bin
EXPOSE 8080/tcp
CMD ./api-server
