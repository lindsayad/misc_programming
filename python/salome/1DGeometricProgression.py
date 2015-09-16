# Arithmetic 1D and Geometric Progression

import salome
salome.salome_init()

from salome.geom import geomBuilder
geompy = geomBuilder.New(salome.myStudy)

from salome.smesh import smeshBuilder
smesh =  smeshBuilder.New(salome.myStudy)

p1 = geompy.MakeVertex(0.,0.,0.)
p2 = geompy.MakeVertex(1.,0.,0.)
line1 = geompy.MakeLineTwoPnt(p1,p2)
geompy.addToStudy(line1, "line1")

lineSeg = smesh.Mesh(line1, "Simple meshing of a line")

gpAlgo = lineSeg.Segment()
gpAlgo.GeometricProgression( 0.1, 1.2 )

# compute the mesh
lineSeg.Compute()

# add node
n1 = lineSeg.AddNode(2,0,0)

# add edge
e1 = lineSeg.AddEdge([n1,6])

algo_local = lineSeg.Segment(e1)

algo_local.GeometricProgression(0.1,1.2)

lineSeg.Compute()
