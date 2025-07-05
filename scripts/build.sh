#!/bin/bash
# Cross-platform build script for StyleCPP
cmake -S . -B build && cmake --build build
