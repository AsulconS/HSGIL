# --- Stage 1: Build HSGIL ---
FROM archlinux:latest AS builder

# Install build tools and dependencies
RUN pacman -Syu --noconfirm && \
	pacman -S --noconfirm base-devel cmake ninja \
	libx11 libxinerama xcb-util-cursor \
	xorgproto mesa

WORKDIR /build
COPY . .
# Using the preset with examples enabled for more comprehensive build
RUN cmake --preset linux-gcc-x64 -DHSGIL_BUILD_EXAMPLES=ON
RUN cmake --build --preset linux-gcc-x64-debug
# ctest --preset linux-gcc-x64-test-debug --build-config Debug


# --- Stage 2: Runtime Environment ---
FROM archlinux:latest

# Install runtime dependencies
RUN pacman -Syu --noconfirm && \
	pacman -S --noconfirm libx11 libxinerama xcb-util-cursor xorg-xwayland \
	mesa mesa-utils vulkan-mesa-layers libglvnd nvidia-utils gdb

# Clean up any existing X11 socket files
RUN rm -rf /tmp/.X11-unix

# 1. Copy the library to the system path
COPY --from=builder /build/out/build/linux-gcc-x64/lib/Debug/libhsgil-runtime.so /usr/lib/
COPY --from=builder /build/out/build/linux-gcc-x64/lib/Debug/libhsgil-runtime.so.* /usr/lib/
RUN ldconfig

# 2. Copy example applications
WORKDIR /app
COPY --from=builder /build/out/build/linux-gcc-x64/bin/Debug/examples/ .

CMD ["/bin/bash"]
