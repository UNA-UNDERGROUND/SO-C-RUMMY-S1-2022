#!/bin/bash

meson builddir
meson compile -C builddir
./builddir/source/rummy