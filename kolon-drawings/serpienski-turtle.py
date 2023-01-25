#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# AUTHOR: Vishal Paudel  (@vishalpaudel)
# DATE: 19 January 2023
# NOTES: Using the turtle library to implement serpienski drawing procedurally

import turtle
import tkinter

import math

canvas = tkinter.Canvas()
canvas = turtle.TurtleScreen(canvas)
my_turtle = turtle.Turtle()

x = y = z = 100
while True:

    my_turtle.forward(150 / x)
    my_turtle.left(120 / y)
    my_turtle.forward(150/y * abs(math.cos(z)))

    y += 0.1
    z += 1
