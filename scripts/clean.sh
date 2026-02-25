#!/bin/bash
docker run --rm -v "//$(pwd):/root/env" osdev-env make clean