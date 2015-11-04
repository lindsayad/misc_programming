#!/usr/bin/python
#
# Word of advice: the ~ character does not equal the user home directory when 
# assigning paths in python. Don't use it. You'll feel dumb like me.
#
#
import sys
#sys.path.append("/mnt/Data/mntHome/visit2.8.2Build/2.8.2/linux-x86_64/lib/site-packages")
#
#from visit import *
#Launch()
#ResizeWindow(1,1400,1000);
#
#
pathPrefix = "/mnt/Data/mntHome/afivo/examples/test_str2d_"
pathSuffix = ".silo"
lastFileNum = 41
var = "elec"
i = 1
while i <= lastFileNum:
	DeleteAllPlots()
	path = pathPrefix + str(i) + pathSuffix
#	print path
	OpenDatabase(path)
	AddPlot("Pseudocolor",var)
	#AddOperator("Slice")
	p = PseudocolorAttributes()
	p.colorTableName = "rainbow"
	p.opacity = 0.5
	SetPlotOptions(p)
	#a = SliceAttributes()
	#a.originType = a.Point
	#a.normal, a.upAxis = (1,1,1), (-1,1,-1)
	#SetOperatorOptions(a)
	s = SaveWindowAttributes()
	s.fileName = var + "At" + str(i) + "thTimeStepIncreasePot"
	s.family = 0 #if you don't want numbers appended to your filename
#	s.format = s.png
	SetSaveWindowAttributes(s)
	DrawPlots()
	SaveWindow()
	i += 1
sys.exit()

