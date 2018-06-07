#!/bin/bash

find solutions -iname "problem*.c"
find solutions -iname "problem*.java"
find solutions -iname "problem*.py"
find solutions -iname "problem*.ipynb" | grep -v checkpoint
