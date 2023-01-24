#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# AUTHOR: Vishal Paudel  (@vishalpaudel)
# DATE: 19 January 2023
# NOTES: Only Suryansh and Arnab were able to convert the code in the class

state = 2 ** 32 - 1  # The initial string is all
for i in range(0, 32):
    for j in range(64, 0, -1):

        if (state >> j & 1):
            print('|', end='')
        else:
            print(' ', end='')

    print('')
    state = (state >> 1) ^ (state | state << 1)

# EOF
