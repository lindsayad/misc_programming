from paraview.simple import *
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from collections import OrderedDict
from matplotlib import rc
from matplotlib.ticker import ScalarFormatter
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})
nnN_A = 6.02e23
coulomb = 1.6e-19

def load_data(short_names, labels, mesh_struct, styles):
    global job_names, name_dict, cellGasData, cellLiquidData, pointGasData, pointLiquidData, label_dict, style_dict, mesh_dict
    data = OrderedDict()
    cellData = OrderedDict()

    name_dict = {x:y for x,y in zip(job_names, short_names)}
    label_dict = {x:y for x,y in zip(job_names, labels)}
    style_dict = {x:y for x,y in zip(job_names, styles)}
    mesh_dict = {x:y for x,y in zip(job_names, mesh_struct)}

    index = 0
    GasElemMax = 0
    path = "/home/lindsayad/gdrive/MooseOutput/"
    for job in job_names:
        file_sans_ext = path + job + "_gold_out"
        inp = file_sans_ext + ".e"
        out = file_sans_ext + ".csv"

        reader = ExodusIIReader(FileName=inp)
        tsteps = reader.TimestepValues
        writer = CreateWriter(out, reader)
        writer.Precision = 16
        writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
        del writer

        for i in range(2,6):
            os.remove(file_sans_ext + str(i) + ".csv")

        new_inp0 = file_sans_ext + "0.csv"
        data[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
        pointGasData[job] = data[job]

        # Use for coupled gas-liquid simulations
        new_inp1 = file_sans_ext + "1.csv"
        data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
        pointLiquidData[job] = data1
        data[job] = np.concatenate((data[job],data1), axis=0)

        writer = CreateWriter(out, reader)
        writer.FieldAssociation = "Cells"
        writer.Precision = 16
        writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
        del writer

        for i in range(2,6):
            os.remove(file_sans_ext + str(i) + ".csv")

        new_inp0 = file_sans_ext + "0.csv"
        cellData[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
        cellGasData[job] = cellData[job]
        if index == 0:
            GasElemMax = np.amax(cellData[job]['GlobalElementId'])

        # Use for coupled gas-liquid simulations
        new_inp1 = file_sans_ext + "1.csv"
        data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
        cellData[job] = np.concatenate((cellData[job],data1), axis=0)
        cellLiquidData[job] = data1


def plot_elec_dens_full(save, pmode):
    # Plot of electron densities. Whole gas-liquid domain
    fig = plt.figure(figsize=(10., 7.), dpi = 80)
    plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
    ax1 = plt.subplot(121)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'] * 1e-3, cellGasData[job]['em_lin'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax1.set_yscale('log')
    ax1.legend(loc='upper left', fontsize = 16)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(['1000', '750', '500', '250', '0'])
    ax1.set_xlabel('Distance from Interface ($\mu m$)')
    ax1.set_ylabel('Gas Electron Density (m$^{-3}$)')
    ax1.set_xlim(-.1e-3,1.1e-3)
    ax2 = plt.subplot(122)
    for job in job_names:
        ax2.plot(1e-3 + (cellLiquidData[job]['x'] - 1.) * 1e-7, cellLiquidData[job]['emliq_lin'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax2.legend(loc=0, fontsize = 16)
    ax2.set_xticks([1e-3, 1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
    ax2.set_xticklabels(['0', '25', '50', '75', '100'])
    ax2.set_xlabel('Distance from interface ($nm$)')
    ax2.yaxis.tick_right()
    ax2.yaxis.set_label_position("right")
    ax2.set_ylabel('Liquid Electron Density (m$^{-3}$)')
    ax2.set_yscale('log')
    ax2.set_xlim(1e-3 - .1e-7, 1e-3 + 1.1e-7)
    if save:
        if pmode == "kinetic":
            fig.savefig('/home/lindsayad/Pictures/plasliq_electron_density_full_kinetic_wide.eps', format='eps')
        elif pmode == "energybc":
            fig.savefig('/home/lindsayad/Pictures/plasliq_electron_density_full_energy_bc_wide.eps', format='eps')
        elif pmode == "thermo":
            fig.savefig(pic_path + "plasliq_electron_density_full_thermo_wide.eps", format='eps')

        elif pmode == "kinetic_vary_gamma_dens_only":
            fig.savefig(pic_path + "plasliq_edens_full_gammadens_wide.eps", format='eps')
    plt.show()

def currents_full(save, pmode):
    # Plot of currents. Whole gas-liquid domain
    fig = plt.figure(figsize=(10., 5.), dpi = 80)
    plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
    ax1 = plt.subplot(121)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['tot_gas_current'], label = name_dict[job], linewidth=2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode ($\mu m$)')
    ax1.set_ylabel('Gas current (A m$^{-2}$)')
    ax2 = plt.subplot(122)
    for job in job_names:
        ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['tot_liq_current'], label = name_dict[job], linewidth=2)
    ax2.legend(loc=0, fontsize = 16)
    ax2.set_xticks([1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
    ax2.set_xticklabels(['25', '50', '75', '100'])
    ax2.set_xlabel('Distance from interface ($nm$)')
    ax2.yaxis.tick_right()
    ax2.yaxis.set_label_position("right")
    ax2.set_ylabel('Liquid Current (A m$^{-2}$)')
    if save:
        if pmode == "kinetic":
            fig.savefig('/home/lindsayad/Pictures/plasliq_current_full_kinetic.eps', format='eps')
        elif pmode == "energybc":
            fig.savefig('/home/lindsayad/Pictures/plasliq_current_full_energy_bc.eps', format='eps')
        elif pmode == "thermo":
            fig.savefig(pic_path + "plasliq_current_full_thermo.eps", format='eps')
    plt.show()

def plot_ions(save, pmode):
    # Plot of ion density. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        if mesh_dict[job] == "phys":
            ax1.plot(cellGasData[job]['x'], cellGasData[job]['Arp_lin'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
        elif mesh_dict[job] == "scaled":
            ax1.plot(cellGasData[job]['x'] * 1e-3, cellGasData[job]['Arp_lin'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from interface ($\mu m$)')
    ax1.set_ylabel('Gas Ion Density (m$^{-3}$)')
    ax1.set_yscale('log')
    ax1.set_xlim(-.1e-3, 1.1e-3)
    ax1.set_ylim(bottom=1e16)
    if save:
        if pmode == "kinetic":
            fig.savefig('/home/lindsayad/Pictures/plasliq_ion_density_full_kinetic.eps', format='eps')
        elif pmode == "energybc":
            fig.savefig('/home/lindsayad/Pictures/plasliq_ion_density_full_energy_bc.eps', format='eps')
        elif pmode == "thermo":
            fig.savefig(pic_path + "plasliq_ion_density_thermo.eps", format='eps')

        elif pmode == "kinetic_vary_gamma_dens_only":
            fig.savefig(pic_path + "plasliq_idens_gammadens.eps", format='eps')

        elif pmode == "condition_compare":
            if files == "all consistent":
                fig.savefig(pic_path + "plasliq_ion_density_consist_compare.eps", format='eps')
            elif files == "all":
                fig.savefig(pic_path + "plasliq_ion_density_compare.eps", format='eps')
            elif files == "thermo extremes":
                fig.savefig(pic_path + "plasliq_ion_density_thermo_extremes.eps", format='eps')
            elif files == "kinetic extremes":
                fig.savefig(pic_path + "plasliq_ion_density_kinetic_extremes.eps", format='eps')
    plt.show()

def plot_elec_gas(save, pmode):
    # Plot of electron density. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        if mesh_dict[job] == "phys":
            ax1.plot(cellGasData[job]['x'], cellGasData[job]['em_lin'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
        elif mesh_dict[job] == "scaled":
            ax1.plot(cellGasData[job]['x'] * 1e-3, cellGasData[job]['em_lin'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode ($\mu m$)')
    ax1.set_ylabel('Gas Electron Density (m$^{-3}$)')
    ax1.set_yscale('log')
    ax1.set_ylim(bottom=1e16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    if save:
        if pmode == "kinetic":
            fig.savefig('/home/lindsayad/Pictures/plasliq_electron_density_gas_only_kinetic.eps', format='eps')
        elif pmode == "energybc":
            fig.savefig('/home/lindsayad/Pictures/plasliq_electron_density_gas_only_energy_bc.eps', format='eps')
        elif pmode == "thermo":
            fig.savefig(pic_path + "plasliq_electron_density_thermo.eps", format='eps')
        elif pmode == "condition_compare":
            if files == "all consistent":
                fig.savefig(pic_path + "plasliq_electron_density_consist_compare.eps", format='eps')
            elif files == "all":
                fig.savefig(pic_path + "plasliq_electron_density_compare.eps", format='eps')
            elif files == "thermo extremes":
                fig.savefig(pic_path + "plasliq_electron_density_thermo_extremes.eps", format='eps')
            elif files == "kinetic extremes":
                fig.savefig(pic_path + "plasliq_electron_density_kinetic_extremes.eps", format='eps')
    plt.show()

def cell_gas_generic(save, variables, pos_scaling, ylabel, tight_plot, xticks, xticklabels, xlabel, xmin=None, xmax=None, ymin=None, ymax=None, yscale=None, save_string="dummy", var_labels = ''):
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        plot_label = name_dict[job]
        for variable in variables:
            if len(variables) > 1:
                plot_label = plot_label + var_labels[variable]
            ax1.plot(cellGasData[job]['x'] / pos_scaling, cellGasData[job][variable], color = label_dict[job], linestyle = style_dict[job], label = plot_label, linewidth=2)

    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xticks(xticks)
    ax1.set_xticklabels(xticklabels)
    ax1.set_xlabel(xlabel)
    ax1.set_ylabel(ylabel)
    sf = ScalarFormatter()
    sf.set_scientific(True)
    sf.set_powerlimits((-3,4))
    ax1.yaxis.set_major_formatter(sf)
    if xmin is not None:
        ax1.set_xlim(left=xmin)
    if xmax is not None:
        ax1.set_xlim(right=xmax)
    if ymin is not None:
        ax1.set_ylim(bottom=ymin)
    if ymax is not None:
        ax1.set_ylim(top=ymax)
    if yscale is not None:
        ax1.set_yscale(yscale)
    if tight_plot:
        fig.tight_layout()
    if save:
        fig.savefig('/home/lindsayad/Pictures/' + save_string + '_' + variable + '.eps', format='eps')
    plt.show()

def point_gas_generic(save, variable, pos_scaling, ylabel, tight_plot, xticks, xticklabels, xlabel, xmin=None, xmax=None, ymin=None, ymax=None, yscale=None, save_string="dummy"):
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        if mesh_dict[job] == "phys":
            ax1.plot(pointGasData[job]['Points0'], pointGasData[job][variable], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
        elif mesh_dict[job] == "scaled":
            ax1.plot(pointGasData[job]['Points0'] / pos_scaling, pointGasData[job][variable], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xticks(xticks)
    ax1.set_xticklabels(xticklabels)
    ax1.set_xlabel(xlabel)
    ax1.set_ylabel(ylabel)
    if xmin is not None:
        ax1.set_xlim(left=xmin)
    if xmax is not None:
        ax1.set_xlim(right=xmax)
    if ymin is not None:
        ax1.set_ylim(bottom=ymin)
    if ymax is not None:
        ax1.set_ylim(top=ymax)
    if yscale is not None:
        ax1.set_yscale(yscale)
    if tight_plot:
        fig.tight_layout()
    if save:
        fig.savefig('/home/lindsayad/Pictures/' + save_string + '_' + variable + '.eps', format='eps')
    plt.show()

def plot_potential(save, pmode):
    # Plot of potential. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        if mesh_dict[job] == "phys":
            ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['potential'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
        elif mesh_dict[job] == "scaled":
            ax1.plot(pointGasData[job]['Points0'] * 1e-3, pointGasData[job]['potential'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from interface (microns)')
    ax1.set_ylabel('Potential (kV)')
    if PIC:
        ax1.plot(emi_x, emi_pot / 1000, label = "PIC pot", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    if save:
        if pmode == "kinetic":
            fig.savefig(pic_path + "plasliq_potential_kinetic.eps", format = 'eps')
        elif pmode == "energybc":
            fig.savefig('/home/lindsayad/Pictures/plasliq_potential_thermo_energy_bc.eps', format='eps')
        elif pmode == "thermo":
            fig.savefig(pic_path + "plasliq_potential_thermo.eps", format='eps')

        elif pmode == "kinetic_vary_gamma_dens_only":
            fig.savefig(pic_path + "plasliq_potential_gammadens.eps", format='eps')

        elif pmode == "condition_compare":
            if files == "all consistent":
                fig.savefig(pic_path + "plasliq_potential_consist_compare.eps", format='eps')
            elif files == "all":
                fig.savefig(pic_path + "plasliq_potential_compare.eps", format='eps')
            elif files == "thermo extremes":
                fig.savefig(pic_path + "plasliq_potential_thermo_extremes.eps", format='eps')
            elif files == "kinetic extremes":
                fig.savefig(pic_path + "plasliq_potential_kinetic_extremes.eps", format='eps')
    plt.show()

def plot_e_temp(save, pmode):
    # Plot of e temp. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        if mesh_dict[job] == "phys":
            ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['e_temp'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
        elif mesh_dict[job] == "scaled":
            ax1.plot(pointGasData[job]['Points0'] * 1e-3, pointGasData[job]['e_temp'], color = label_dict[job], linestyle = style_dict[job], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from interface (microns)')
    ax1.set_ylabel('Electron temperature (V)')
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    fig.tight_layout()
    # ax1.set_ylim(bottom = 0, top = 10)
    if save:
        if pmode == "kinetic":
            fig.savefig(pic_path + "plasliq_e_temp_kinetic.eps", format = 'eps')
        elif pmode == "energybc":
            fig.savefig('/home/lindsayad/Pictures/plasliq_e_temp_thermo_energy_bc.eps', format='eps')
        elif pmode == "thermo":
            fig.savefig(pic_path + "plasliq_e_temp_thermo.eps", format='eps')

        elif pmode == "kinetic_vary_gamma_dens_only":
            fig.savefig(pic_path + "plasliq_etemp_gammadens_wide.eps", format='eps')

        elif pmode == "condition_compare":
            if files == "all consistent":
                fig.savefig(pic_path + "plasliq_e_temp_consist_compare.eps", format='eps')
            elif files == "all":
                fig.savefig(pic_path + "plasliq_e_temp_compare.eps", format='eps')
            elif files == "thermo extremes":
                fig.savefig(pic_path + "plasliq_e_temp_thermo_extremes.eps", format='eps')
            elif files == "kinetic extremes":
                fig.savefig(pic_path + "plasliq_e_temp_kinetic_extremes.eps", format='eps')
    plt.show()

def plot_power_dep_elec(save, pmode):
    # Plot of power deposition in electrons. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['PowerDep_em'], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Power Deposition in electron heating (W m$^{-2}$)')
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    ax1.set_ylim(bottom = 0)
    if save:
        if pmode == "ion_power_dep":
            fig.savefig(pic_path + "plasliq_power_dep_electrons.eps", format = 'eps')
    plt.show()

def plot_power_dep_ion(save, pmode):
    # Plot of power deposition in ions. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['PowerDep_Arp'], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Power Deposition in ion heating (W m$^{-2}$)')
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    ax1.set_ylim(bottom = 0)
    if save:
        if pmode == "ion_power_dep":
            fig.savefig(pic_path + "plasliq_power_dep_ions.eps", format = 'eps')
    plt.show()

def plot_iz_rate(save, pmode):
    # Plot of rate of ionization. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        # ax1.plot(cellGasData[job]['x'], cellGasData[job]['ProcRate_ex'], label = name_dict[job] + " excitation", linewidth=2)
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['ProcRate_iz'], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Volumetric rate of ionization (\# m$^{-3}$ s$^{-1}$)')
    ax1.set_ylim(bottom = 0)
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    if save:
        if pmode == "ion_power_dep":
            fig.savefig(pic_path + "plasliq_volumetric_rates.eps", format = 'eps')
    plt.show()

def plot_ex_rate(save, pmode):
    # Plot of rate of excitation. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['ProcRate_ex'], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Volumetric rate of excitation (\# m$^{-3}$ s$^{-1}$)')
    ax1.set_ylim(bottom = 0)
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    if save:
        if pmode == "ion_power_dep":
            fig.savefig(pic_path + "plasliq_volumetric_excitation.eps", format = 'eps')
    plt.show()

def plot_el_rate(save, pmode):
    # Plot of rate of elastic collisions. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['ProcRate_el'], label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Volumetric rate of elastic collisions (\# m$^{-3}$ s$^{-1}$)')
    ax1.set_ylim(bottom = 0)
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    if save:
        if pmode == "ion_power_dep":
            fig.savefig(pic_path + "plasliq_volumetric_elastic.eps", format = 'eps')
    plt.show()

def plot_rho(save, pmode):
    # Plot of charge density. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['rho'] * 1.6e-19, label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Charge Density (C m$^{-3}$)')
    if PIC:
        ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(.25e-3, .75e-3)
    ax1.set_ylim(-1, 1)
    if save:
        if pmode == "kinetic":
            fig.savefig(pic_path + "plasliq_rho_kinetic.eps", format = 'eps')
    plt.show()

def plot_efield(save, pmode, pos_scaling):
    # Plot of electric field. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'] / pos_scaling, cellGasData[job]['Efield'] * 1000 * pos_scaling, label = name_dict[job], linewidth=2)
    ax1.set_xticks(xtickers)
    ax1.set_xticklabels(xticker_labels)
    ax1.set_xlabel('Distance from cathode (microns)')
    ax1.set_ylabel('Electric Field(V m$^{-1}$)')
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(-.1e-3, 1.1e-3)
    if save:
        if pmode == "kinetic":
            fig.savefig(pic_path + "plasliq_efield_kinetic.eps", format = 'eps')
    plt.show()

def plot_efield_interface(save, pmode, pos_scaling):
    # Plot of electric field. Whole gas domain
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        ax1.plot(cellGasData[job]['x'] / pos_scaling, cellGasData[job]['Efield'] * 1000 * pos_scaling, label = name_dict[job], linewidth=2)
    ax1.set_xticks([.996e-3, .998e-3, 1e-3])
    ax1.set_xticklabels(['4', '2', '0'])
    ax1.set_xlabel('Distance from interface (microns)')
    ax1.set_ylabel('Electric Field(V m$^{-1}$)')
    ax1.legend(loc='best', fontsize = 16)
    ax1.set_xlim(0.995e-3, 1e-3)
    ax1.set_ylim(-4e6, 0)
    sf = ScalarFormatter()
    sf.set_scientific(True)
    sf.set_powerlimits((-3,4))
    ax1.yaxis.set_major_formatter(sf)
    fig.tight_layout()
    if save:
        if pmode == "kinetic":
            fig.savefig(pic_path + "plasliq_efield_kinetic_int.eps", format = 'eps')
        if pmode == "kinetic_vary_gamma_dens_only":
            fig.savefig(pic_path + "plasliq_efield_kdens_int.eps", format = 'eps')
    plt.show()

def plot_fluxes_full(save, pmode):
    # Plot of fluxes. Whole domain
    fig = plt.figure(figsize=(10., 5.), dpi = 80)
    plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
    ax1 = plt.subplot(121)
    for job in job_names:
        job_for_tex = job.replace("_"," ")
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['EFieldAdvAux_em'], label = 'Gas advective', linewidth=2)
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['DiffusiveFlux_em'], 'r-', label = 'Gas diffusive', linewidth=2)
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['Current_em'] / -1.6e-19, 'g-', label = 'Gas total', linewidth=2)
        ax1.set_ylim(-1e23,1e23)
        ax1.legend(loc=0)
        ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
        ax1.set_xticklabels(['0','250', '500', '750'])
        ax1.set_xlabel('Distance from cathode (microns)')
        # ax1.set_ylabel('Density (m$^{-3}$) x 10$^{18}$')
        # fig.tight_layout()
        # fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
    ax2 = plt.subplot(122)
    # ax2 = plt.subplot(122, sharey=ax1)
    for job in job_names:
        job_for_tex = job.replace("_"," ")
        ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['EFieldAdvAux_em'], label = 'Liquid advective', linewidth=2)
        ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['DiffusiveFlux_em'], 'r-', label = 'Liquid diffusive', linewidth=2)
        ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['Current_em'] / -1.6e-19, 'g-', label = 'Liquid total', linewidth=2)
        ax2.legend(loc=0)
        ax2.set_xticks([1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
        ax2.set_xticklabels(['25', '50', '75', '100'])
        ax2.set_xlabel('Distance from interface (nm)')
        ax2.yaxis.tick_right()
        ax2.yaxis.set_label_position("right")
        ax2.set_ylim(-1e23,1e23)
        # ax2.set_ylabel('Density (m$^{-3}$) x 10$^{22}$')
    # fig.tight_layout()
    fig.savefig('/home/lindsayad/Pictures/fluxes_grad_Te_zero.pdf', format='pdf')
    fig.savefig('/home/lindsayad/Pictures/fluxes_grad_Te_zero.eps', format='eps')
    plt.show()

def plot_fluxes_last_bit(save, pmode):
    # Plot of fluxes. Last bit of gas phase
    # fig = plt.figure(figsize=(10., 5.), dpi = 80)
    fig = plt.figure()
    # plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
    ax1 = fig.add_subplot(111)
    # ax1 = plt.subplot(121)
    for job in job_names:
        job_for_tex = job.replace("_"," ")
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['EFieldAdvAux_em'], label = 'Gas advective', linewidth=2)
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['DiffusiveFlux_em'], 'r-', label = 'Gas diffusive', linewidth=2)
        ax1.plot(cellGasData[job]['x'], cellGasData[job]['Current_em'] / -1.6e-19, 'g-', label = 'Gas total', linewidth=2)
        # ax1.set_ylim(-1e22,1e22)
        ax1.set_xlim(0.000999, 0.001)
        ax1.legend(loc=0)
        # ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
        # ax1.set_xticklabels(['0','250', '500', '750'])
        ax1.set_xlabel('Distance from cathode (microns)')
        # ax1.set_ylabel('Density (m$^{-3}$) x 10$^{18}$')
        # fig.tight_layout()
        # fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
    fig.savefig('/home/lindsayad/Pictures/fluxes_inset_grad_Te_zero.pdf', format='pdf')
    fig.savefig('/home/lindsayad/Pictures/fluxes_inset_grad_Te_zero.eps', format='eps')
    plt.show()

path = "/home/lindsayad/gdrive/MooseOutput/"
pic_path = "/home/lindsayad/gdrive/Pictures/"
cellGasData = OrderedDict()
cellLiquidData = OrderedDict()
pointGasData = OrderedDict()
pointLiquidData = OrderedDict()
xtickers = [0, .25e-3, .5e-3, .75e-3, 1e-3]
# xticker_labels = ['0','250', '500', '750', '1000']
xticker_labels = ['1000', '750', '500', '250', '0']
# Emi data
emi_path = "/home/lindsayad/gdrive/TabularData/emi_data/gas_only/"
emi_x, emi_n_e = np.loadtxt(emi_path + "ne_vs_x.txt", unpack = True)
emi_x, emi_n_i = np.loadtxt(emi_path + "ni_vs_x.txt", unpack = True)
emi_x, emi_pot = np.loadtxt(emi_path + "Potential_vs_x.txt", unpack = True)
emi_x, emi_efield = np.loadtxt(emi_path + "Efield_vs_x.txt", unpack = True)
emi_x, emi_etemp = np.loadtxt(emi_path + "Te_vs_x.txt", unpack = True)
PIC = False
global_save = True
pos_scaling = 1
microns = 100
mic_step = 20
ticks = [1e-3 - 1e-6 * (microns - i) for i in range(0, microns + mic_step, mic_step)]
ticklabels = [str(i) for i in range(microns, -mic_step, -mic_step)]
num_jobs = 5
# job_names = ["mean_en_gden_0_gen_0_ballast_50e3", "mean_en_gden_0_gen_0_ballast_1e6"]
# short_names = ["high current", "low current"]
job_names = ["_r_en_0", "pt9_r_en_0", "pt99_r_en_0", "pt999_r_en_0", "pt9999_r_en_0"]
job_names = ["mean_en_r_dens_0" + i for i in job_names]
short_names = ["$\gamma_{dens}=1$", "$\gamma_{dens}=10^{-1}$", "$\gamma_{dens}=10^{-2}$", "$\gamma_{dens}=10^{-3}$", "$\gamma_{dens}=10^{-4}$"]
labels_list = ['blue', 'red', 'green', 'pink', 'orange']
styles_list = ['solid', 'dashed', 'dashdot']
labels = [labels_list[i] for i in range(num_jobs)]
mesh_struct = ["scaled" for i in range(num_jobs)]
styles = [styles_list[i % 3] for i in range(num_jobs)]

load_data(short_names, labels, mesh_struct, styles)
# plot_elec_dens_full(global_save, mode)
# plot_ions(global_save, mode)
# plot_potential(global_save, mode)
# plot_rho(False, mode)
# plot_efield(global_save, mode)
# plot_el_rate(global_save, mode)
# plot_elec_gas(global_save, mode)
# plot_e_temp(global_save, mode)
# plot_efield_interface(global_save, mode, pos_scaling)
# cell_gas_generic(global_save, 'rho', pos_scaling, 'Charge Density (C m$^{-3}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - microns * 1e-6, xmax=1e-3)
# cell_gas_generic(global_save, 'em_lin', pos_scaling, 'Gas Electron Density (m$^{-3}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - microns * 1e-6, xmax=1e-3, yscale='log', ymin=1e17)
# cell_gas_generic(global_save, 'Arp_lin', pos_scaling, 'Gas Ion Density (m$^{-3}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - microns * 1e-6, xmax=1e-3, yscale='log', ymin=1e17)
# cell_gas_generic(global_save, 'PowerDep_em', pos_scaling, 'Power deposited in electrons (W m$^{-3}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - 1.1 * microns * 1e-6, xmax=1e-3 + .1 * microns * 1e-6)
cell_gas_generic(global_save, ['PowerDep_em', 'PowerDep_Arp'], pos_scaling, 'Power deposition (W m$^{-3}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - 1.1 * microns * 1e-6, xmax=1e-3 + .1 * microns * 1e-6, var_labels = [' e$^-$', ' Ar$^+$'])
# cell_gas_generic(global_save, 'Efield', pos_scaling, 'Electric Field (V m$^{-1}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - 1.1 * microns * 1e-6, xmax=1e-3 + .1 * microns * 1e-6, ymin = -4e6)
# cell_gas_generic(global_save, 'Current_em', pos_scaling, 'Electron Current (A m$^{-2}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - 1.1 * microns * 1e-6, xmax=1e-3 + .1 * microns * 1e-6, ymin = -1600, ymax = -1200)
# cell_gas_generic(global_save, 'tot_gas_current', pos_scaling, 'Gas Current (A m$^{-2}$)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - microns * 1e-6, xmax=1e-3)
# point_gas_generic(global_save, 'potential', pos_scaling, 'Potential (kV)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - microns * 1e-6, xmax=1e-3)
# point_gas_generic(global_save, 'e_temp', pos_scaling, 'Electron Temperature (eV)', True, ticks, ticklabels, 'Distance from interface ($\mu m$)', xmin= 1e-3 - microns * 1e-6, xmax=1e-3, ymin=0)
