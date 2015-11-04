#!/usr/bin/python

from paraview.simple import *
# Create a simple pipeline
sph = Sphere()
elev = Elevation(sph)
Show(elev)
Render()
# Set the representation type of elev
dp = GetDisplayProperties(elev)
dp.Representation = 'Points'
# Here is how you get the list of representation types
Render()
# Change the representation to wireframe
dp.Representation = 'Wireframe'
Render()
# Lets get some information about the output of the elevation
# filter. We want to color the representation by one of its
# arrays.
# Second array = Elevation. Interesting. Lets use this one.
ai = elev.PointData[1]
ai.GetName()
# What is its range?
ai.GetRange()
# To color the representation by an array, we need to first create
# a lookup table.  We use the range of the Elevation array
dp.LookupTable = MakeBlueToRedLT(0, 0.5)
dp.ColorAttributeType = 'POINT_DATA'
dp.ColorArrayName = 'Elevation' # color by Elevation
Render()
