#!/bin/sh

taskset --cpu-list 0 ./dgemm
