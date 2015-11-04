import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
from collections import OrderedDict
rc('text', usetex=True)
#
mpl.rcParams.update({'font.size': 20})

data_dir = '/home/lindsayad/gdrive/MooseOutput/'
job_names = ['Townsend_energy','Rate_coeff_energy','Townsend_var_elastic_energy','Townsend_energy_spline']
# job_names = ['Townsend_energy','Rate_coeff_energy','Townsend_var_elastic_energy','Townsend_lfa','Townsend_energy_spline']
dep_var_names = ['electron_temp']
# dep_var_names = ['electron_density','ion_density','potential']

# f_twn_en = '/home/lindsayad/gdrive/MooseOutput/Townsend_energy_ion_and_electron_densities.csv'
# f_rate_en = '/home/lindsayad/gdrive/MooseOutput/Rate_coeff_energy_ion_and_electron_densities.csv'
# f_twn_lfa = '/home/lindsayad/gdrive/MooseOutput/Townsend_lfa_ion_and_electron_densities.csv'

data = OrderedDict()
for job in job_names:
    data[job] = OrderedDict()
    for dep_var in dep_var_names:
        file_name = data_dir + job + '_' + dep_var + '.csv'
        rewrite = False
        with open(file_name,'r') as fin:
            c = fin.read(1)
            if c == '"':
                rewrite = True
                fin.seek(0)
                file_data = fin.read().splitlines(True)
        if rewrite:
            with open(file_name, 'w') as fout:
                fout.writelines(file_data[1:])
        data[job][dep_var] = np.loadtxt(file_name,delimiter=',')

# figures = OrderedDict()
for dep_var in dep_var_names:
    var_for_tex = dep_var.replace("_"," ")
    fig = plt.figure()
    ax = fig.add_subplot(111)
    # ax = fig.add_axes([0.1,0.1,0.6,0.75])
    for job in job_names:
        job_for_tex = job.replace("_"," ")
        ax.plot(data[job][dep_var][:,2],data[job][dep_var][:,0],label=job_for_tex,linewidth=2)
    ax.set_xlabel('x (m)')
    ax.set_ylabel(var_for_tex)
    ax.set_xlim(-.0001,.0011)
    ax.legend(loc='upper center',bbox_to_anchor=(0.5,1.1),fancybox=True,shadow=True,fontsize=12,ncol=len(data.keys())/2)
    fig.set_size_inches((10,9))
    # fig.tight_layout()
    fig.savefig('/home/lindsayad/Pictures/' + dep_var + '_dummy_name_to_prevent_accidental_overwrite_of_good_figs.eps',format='eps')
plt.show()

# data_twn_en = np.loadtxt(f_twn_en,delimiter=',')
# ion_density_twn_en = data_twn_en[:,0]
# electron_density_twn_en = data_twn_en[:,1]
# arc_length = data_twn_en[:,3]

# data_rate_en = np.loadtxt(f_rate_en,delimiter=',')
# ion_density_rate_en = data_rate_en[:,0]
# electron_density_rate_en = data_rate_en[:,1]

# data_twn_lfa = np.loadtxt(f_twn_lfa,delimiter=',')
# ion_density_twn_lfa = data_twn_lfa[:,0]
# electron_density_twn_lfa = data_twn_lfa[:,1]

# figIon = plt.figure()
# figElectron = plt.figure()
# axIon = figIon.add_subplot(111)
# axElectron = figElectron.add_subplot(111)

# axIon.plot(arc_length,ion_density_twn_en,label='Townsend energy form',linewidth=2)
# axElectron.plot(arc_length,electron_density_twn_en,label='Townsend energy form',linewidth=2)

# axIon.plot(arc_length,ion_density_rate_en,label='Rate coeff energy form',linewidth=2)
# axElectron.plot(arc_length,electron_density_rate_en,label='Rate coeff energy form',linewidth=2)

# axIon.plot(arc_length,ion_density_twn_lfa,label='Townsend lfa form',linewidth=2)
# axElectron.plot(arc_length,electron_density_twn_lfa,label='Townsend lfa form',linewidth=2)

# axIon.set_xlabel('x (m)')
# axIon.set_ylabel('Densities (m$^{-3}$)')
# axIon.legend(loc=0)

# axIon.axvline(x=0,ymin=0,ymax=1,color='k',ls='--')
# axIon.axvline(x=0.001,ymin=0,ymax=1,color='k',ls='--')
# axIon.annotate('cathode', xy=(0.0385,0.5),xycoords='axes fraction',xytext=(0.08,0.55),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))
# axIon.annotate('anode', xy=(0.9615,0.5),xycoords='axes fraction',xytext=(0.77,0.56),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))

# axElectron.set_xlabel('x (m)')
# axElectron.set_ylabel('Densities (m$^{-3}$)')
# axElectron.legend(loc=0)

# axElectron.axvline(x=0,ymin=0,ymax=1,color='k',ls='--')
# axElectron.axvline(x=0.001,ymin=0,ymax=1,color='k',ls='--')
# axElectron.annotate('cathode', xy=(0.0385,0.5),xycoords='axes fraction',xytext=(0.08,0.55),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))
# axElectron.annotate('anode', xy=(0.9615,0.5),xycoords='axes fraction',xytext=(0.77,0.56),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))

# # axIon.set_xlim([-.002,0.05])
# # axIon.set_ylim([0,3.5e17])
# # axElectron.set_xlim([-.002,0.05])

# figIon.tight_layout()
# figElectron.tight_layout()
# # figIon.savefig('/home/lindsayad/gdrive/Pictures/IonDensitiesZoomed.eps',format='eps')
# # figElectron.savefig('/home/lindsayad/gdrive/Pictures/ElectronDensities.eps',format='eps')
# plt.show()
