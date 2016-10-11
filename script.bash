#!/bin/bash

while true; do
    ./getboard.py
    ./runaway.exe
    ./postsolution.py
done
