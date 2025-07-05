#!/bin/bash
# Code formatting script for StyleCPP
clang-format -i $(find include/ src/ tests/ examples/ -name '*.h' -o -name '*.cpp')
