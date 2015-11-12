from paraview.simple import *
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import OrderedDict

path = "/home/lindsayad/gdrive/MooseOutput/"
file_root = "DCPlasma_argon_energy_variable_trans_for_compare_townsend_spline_new_form_"
job_names = ["const_elastic_high_ip_diffusive", "var_iz_var_el_old_ip_trans_coeffs_large_plasma_radius", "var_iz_var_el_old_ip_trans_coeffs_small_plasma_radius", "var_iz_var_el_new_ip_trans_coeffs_small_plasma_radius"]
data = OrderedDict()
for job in job_names:
    file_sans_ext = path + file_root + job + "_gold_out"
    inp = file_sans_ext + ".e"
    out = file_sans_ext + ".csv"

    reader = ExodusIIReader(FileName=inp)
    tsteps = reader.TimestepValues
    writer = CreateWriter(out, reader)
    writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
    del writer
    
    for i in range(1,5):
        os.remove(file_sans_ext + str(i) + ".csv")
    
    new_inp = file_sans_ext + "0.csv"
    data[job] = np.genfromtxt(new_inp,delimiter=',',names=True)

plot_vars = ['Arp_lin','em_lin','e_temp','potential']
for var in plot_vars:
    var_for_tex = var.replace("_"," ")
    fig = plt.figure()
    ax = fig.add_subplot(111)
    for job in job_names:
        job_for_tex = job.replace("_"," ")
        ax.plot(data[job]['Points0'],data[job][var],label=job_for_tex, linewidth=2)
    ax.set_xlabel('x (m)')
    ax.set_ylabel(var_for_tex)
    ax.set_xlim(-.0001,.0011)
    # ax.legend(loc='upper center',bbox_to_anchor=(0.5,1.1),fancybox=True,shadow=True,fontsize=12,ncol=len(data.keys())/2)
    # fig.set_size_inches((10,9))
    ax.legend(loc=0)
    fig.tight_layout()
    fig.savefig('/home/lindsayad/Pictures/' + var + '_dummy_name_to_prevent_accidental_overwrite_of_good_figs.svg',format='svg')
plt.show()
