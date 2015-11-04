#!/usr/bin/python

from math import floor

OldDistance = 5.46
OldTimeSeconds = 43*60+52.3

ModFactor = 1.1
NewDistance = ModFactor*OldDistance
NewTimeSeconds = ModFactor*OldTimeSeconds
Seconds = NewTimeSeconds % 60
Minutes = int(floor(NewTimeSeconds / 60))
print(NewDistance)
print("{m}:{s}".format(m=Minutes,s=Seconds))

