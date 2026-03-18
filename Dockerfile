FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    binutils \
    nasm \
    make \
    xorriso \
    grub-pc-bin \
    grub-common \
    mtools \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/env