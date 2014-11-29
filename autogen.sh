#!/usr/bin/env bash

autoheader
aclocal
automake --add-missing --copy
autoconf
