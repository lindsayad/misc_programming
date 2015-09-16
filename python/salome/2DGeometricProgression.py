# Arithmetic 1D and Geometric Progression

import salome
salome.salome_init()

from salome.geom import geomBuilder
geompy = geomBuilder.New(salome.myStudy)

from salome.smesh import smeshBuilder
smesh =  smeshBuilder.New(salome.myStudy)

face1 = geompy.MakeFaceHW(100,100,1)
geompy.addToStudy(face1, "face1")

quadra = smesh.Mesh(face1, "Rectangle : quadrangle mesh")

gpAlgo = quadra.Segment()
gpAlgo.GeometricProgression( 1, 1.2 )

# create a quadrangle 2D algorithm for faces
quadra.Quadrangle()

# compute the mesh
quadra.Compute()
