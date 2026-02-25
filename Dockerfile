FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    gcc \
    binutils \
    nasm \
    make \
    xorriso \
    grub-pc-bin \
    grub-common \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/env