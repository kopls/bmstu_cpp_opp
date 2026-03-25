#!/bin/bash

./unit_tests.exe
echo ""
echo "=== Code Coverage ==="
gcovr -r . --object-directory out --print-summary | grep lines
