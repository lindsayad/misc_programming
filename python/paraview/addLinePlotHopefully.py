try: paraview.simple
except: from paraview.simple import *
paraview.simple._DisableFirstRenderCameraReset()

PlotOverLine6 = GetActiveSource()
PlotOverLine6.Input = []
PlotOverLine6.Source = []

XYChartView1 = GetRenderView()

Delete(PlotOverLine6)
AnimationScene1 = GetAnimationScene()
AnimationScene1.EndTime = 1.0
AnimationScene1.PlayMode = 'Sequence'

lots_of_variables_out_e = ExodusIIReader( FileName=['/home/alexlindsay/zapdos/problems/lots_of_variables_out.e'] )

AnimationScene1.EndTime = 0.0094
AnimationScene1.PlayMode = 'Snap To TimeSteps'

lots_of_variables_out_e.FileRange = [0, 0]
lots_of_variables_out_e.XMLFileName = 'Invalid result'
lots_of_variables_out_e.FilePrefix = '/home/alexlindsay/zapdos/problems/lots_of_variables_out.e'
lots_of_variables_out_e.ModeShape = 5
lots_of_variables_out_e.FilePattern = '%s'

lots_of_variables_out_e.ElementBlocks = ['Unnamed block ID: 0 Type: EDGE2']
lots_of_variables_out_e.NodeSetArrayStatus = []
lots_of_variables_out_e.SideSetArrayStatus = []
lots_of_variables_out_e.PointVariables = ['em']

RenderView7 = CreateRenderView()
RenderView7.CompressorConfig = 'vtkSquirtCompressor 0 3'
RenderView7.InteractionMode = '2D'
RenderView7.UseLight = 1
RenderView7.CameraPosition = [1.0300000212737359e-05, 10000.0, 10000.0]
RenderView7.LightSwitch = 0
RenderView7.Background = [0.31999694819562063, 0.3400015259021897, 0.4299992370489052]
RenderView7.CameraFocalPoint = [1.0300000212737359e-05, 0.0, 0.0]
RenderView7.CameraViewUp = [1.0, 1.0, 0.0]
RenderView7.CenterOfRotation = [1.0300000212737359e-05, 0.0, 0.0]
RenderView7.CameraParallelProjection = 1

AnimationScene1.ViewModules = [ XYChartView1, RenderView7 ]

DataRepresentation13 = Show()
DataRepresentation13.EdgeColor = [0.0, 0.0, 0.5000076295109483]
DataRepresentation13.SelectionPointFieldDataArrayName = 'em'
DataRepresentation13.SelectionCellFieldDataArrayName = 'GlobalElementId'
DataRepresentation13.ScalarOpacityUnitDistance = 9.561673194730194e-06
DataRepresentation13.ExtractedBlockIndex = 2
DataRepresentation13.ScaleFactor = 2.060000042547472e-06

RenderView7.CameraViewUp = [0.7071067811865476, 0.7071067811865476, 0.0]
RenderView7.CameraPosition = [1.0300000212737359e-05, 3.102185033432059e-05, 3.102185033432059e-05]
RenderView7.CameraClippingRange = [4.343280625797747e-05, 4.452959429479509e-05]
RenderView7.CameraParallelScale = 1.1426769862779412e-05

AnimationScene1.ViewModules = XYChartView1

Delete(RenderView7)
Delete(DataRepresentation13)

PlotOverLine7 = PlotOverLine( Source="High Resolution Line Source" )

PlotOverLine7.Source.Point2 = [2.0600000425474718e-05, 0.0, 0.0]

PlotOverLine7.Source.Resolution = 10

SetActiveView(XYChartView1)
DataRepresentation14 = Show()
DataRepresentation14.XArrayName = 'arc_length'
DataRepresentation14.SeriesVisibility = ['ObjectId', '0', 'Points (0)', '0', 'Points (1)', '0', 'Points (2)', '0', 'Points (Magnitude)', '0', 'arc_length', '0', 'vtkOriginalIndices', '0', 'vtkValidPointMask', '0']
DataRepresentation14.UseIndexForXAxis = 0

XYChartView1.BottomAxisRange = [0.0, 2.1e-05]

AnimationScene1.AnimationTime = 0.0094

Render()
