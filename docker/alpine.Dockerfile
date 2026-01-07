# --- Stage 1: Build HSGIL ---
FROM alpine:latest AS builder

# Install build tools and dependencies
RUN apk add --no-cache \
	build-base cmake ninja \
	libx11-dev libxinerama-dev xcb-util-cursor-dev \
	xorgproto mesa-dev mesa-gl

WORKDIR /build
COPY . .
# Using the preset with examples enabled for more comprehensive build
RUN cmake --preset linux-gcc-x64 -DHSGIL_BUILD_EXAMPLES=ON -DHSGIL_FORCE_GLX_CTX_VERSION=ON -DHSGIL_GLX_CTX_VERSION_MAJOR=4 -DHSGIL_GLX_CTX_VERSION_MINOR=5
RUN cmake --build --preset linux-gcc-x64-debug
# ctest --preset linux-gcc-x64-test-debug --build-config Debug


# --- Stage 2: Runtime Environment ---
FROM alpine:latest

# Install runtime dependencies
RUN apk add --no-cache \
	libx11 libxinerama xcb-util-cursor \
	mesa mesa-gl gdb


# Clean up any existing X11 socket files
RUN rm -rf /tmp/.X11-unix

# 1. Copy the library to the system path
COPY --from=builder /build/out/build/linux-gcc-x64/lib/Debug/libhsgil-runtime.so /usr/lib/
COPY --from=builder /build/out/build/linux-gcc-x64/lib/Debug/libhsgil-runtime.so.* /usr/lib/
RUN ldconfig

# 2. Copy example applications
WORKDIR /app
COPY --from=builder /build/out/build/linux-gcc-x64/bin/Debug/examples/ .

CMD ["/bin/sh"]
