#!/bin/bash

# Perform unit testing.
unit-testing/sprite-batch-cunit
unit-testing/sprite-batch-cunit-quad

# Extract the raw result data.
graphic-test/sprite-batch-graphic > sprite-result.txt
graphic-test/sprite-batch-graphic-quad > quad-result.txt

# Process the result data.
./processRaw.py sprite-result.txt
./processRaw.py quad-result.txt



