#!/usr/bin/env sh

docker run --rm -it \
    --net=host \
    -e DISPLAY \
    -v "/tmp/.X11-unix:/tmp/.X11-unix" \
    -v "${PWD}:/workspace" \
    -w "/workspace" \
    heron \
    bash
