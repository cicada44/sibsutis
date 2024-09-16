#!/bin/bash

opt -opaque-pointers -O3 -S $1.ll -o $1_opt.ll
