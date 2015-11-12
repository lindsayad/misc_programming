from paraview.simple import *

path = "/home/lindsayad/gdrive/MooseOutput/"
file_name = "DCPlasma_argon_energy_variable_trans_for_compare_townsend_spline_new_form_var_iz_var_el_new_ip_trans_coeffs_small_plasma_radius_gold_out"
inp = file_name + ".e"
out = file_name + ".csv"
Show(ExodusIIReader(FileName=path+inp))
Render()
# Get a nice view angle
cam = GetActiveCamera()
cam.Elevation(45.)
Render()
# Check the current view time
view = GetActiveView()
view.ViewTime
reader = GetActiveSource()
reader.TimestepValues
tsteps = reader.TimestepValues
# Lets be fancy and use a time annotation filter. This will show the
# current time value of the reader as text in the corner of the view.
annTime = AnnotateTimeFilter(reader)
# Show the filter
Show(annTime)
# Look at a few time steps. Note that the time value is requested not
# the time step index.
view.ViewTime = tsteps[2]
Render()
view.ViewTime = tsteps[4]
Render()
writer = CreateWriter(path+out, view)
writer.FieldAssociation = "Points" # or "Cells"
writer.UpdatePipeline()
del writer
