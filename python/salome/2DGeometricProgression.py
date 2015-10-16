# Arithmetic 1D and Geometric Progression

import salome
salome.salome_init()

from salome.geom import geomBuilder
geompy = geomBuilder.New(salome.myStudy)

from salome.smesh import smeshBuilder
smesh =  smeshBuilder.New(salome.myStudy)

p0 = geompy.MakeVertex(0,0,0)
p1 = geompy.MakeVertex(10,10,0)

# face1 = geompy.MakeFaceHW(100,100,1)
face1 = geompy.MakeBoxTwoPnt(p0,p1)
geompy.addToStudy(face1, "face1")

quadra = smesh.Mesh(face1, "Rectangle : quadrangle mesh")

# gpAlgo = quadra.Segment()
# gpAlgo.GeometricProgression( 1, 1.2 )

algo1D = quadra.Segment()
algo1D.NumberOfSegments(10)

# create a quadrangle 2D algorithm for faces
quadra.Quadrangle()

# compute the mesh
quadra.Compute()
