from load_data import load_data
from plot_data import *
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from collections import OrderedDict
from matplotlib import rc
from matplotlib.ticker import ScalarFormatter
from test_module import hello_world
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})
nnN_A = 6.02e23
coulomb = 1.6e-19

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
left_start = .9e-3
# microns = (1e-3 - left_start) * 1e6
# mic_step = microns / 5
microns = 20
mic_step = 5
# ticks = [left_start + i * 1e-6 for i in range(0, int(microns + mic_step), int(mic_step))]
# ticklabels = ['{:.2e}'.format(tick) for tick in ticks]
ticks = [1e-3 - i * 1e-6 for i in range(microns, -mic_step, -mic_step)]
ticklabels = [str(microns - i) for i in range(0, microns + mic_step, mic_step)]
xmin = 1e-3 - 1.1 * microns * 1e-6
xmax = 1e-3 + .1 * microns * 1e-6
ymin = -.2e22
ymax = 1.1e22

# job_names = ['', 'pt9', 'pt99', 'pt999', 'pt9999']
# job_names = ["_r_en_0", "pt9999_r_en_0"]
# job_names = ['', 'e1', 'e2', 'e3', 'e4', 'e5', 'e6', 'e7']
# job_names = ['', 'e2', 'e4', 'e6']
job_names = ['', '_low_resist']
# job_names = ['mean_en_r_dens_0' + i + '_r_en_0' for i in job_names]
# job_names = ['mean_en_r_dens_0pt9999_r_en_0' + i for i in job_names]
job_names = ['mean_en_r_dens_0_r_en_0' + i for i in job_names]
# job_names = ['mean_en_H_1' + i + '_r_en_0' for i in job_names]

# short_names = ["$\gamma_{dens}=1$", "$\gamma_{dens}=10^{-1}$", "$\gamma_{dens}=10^{-2}$", "$\gamma_{dens}=10^{-3}$", "$\gamma_{dens}=10^{-4}$"]
# short_names = ["$\gamma_{en}=1$", "$\gamma_{en}=10^{-1}$", "$\gamma_{en}=10^{-2}$", "$\gamma_{en}=10^{-3}$", "$\gamma_{en}=10^{-4}$"]
# short_names = ["$\gamma_{dens}=1$", "$\gamma_{dens}=10^{-4}$"]
short_names = ['$R = 10^6\Omega$', '$R = 8.1\cdot10^3\Omega$']
# short_names = ["$H=1$", "$H=10^2$", "$H=10^4$", "$H=10^6$"]

num_jobs = len(job_names)

labels_list = ['blue', 'red', 'green', 'orange', 'magenta']
styles_list = ['solid', 'dashed', 'dashdot']
labels = [labels_list[i] for i in range(num_jobs)]
mesh_struct = ["scaled" for i in range(num_jobs)]
styles = [styles_list[i % 3] for i in range(num_jobs)]
job_colors = labels
job_color_dict = {x:y for x,y in zip(job_names, job_colors)}
name_dict = {x:y for x,y in zip(job_names, short_names)}

gas_variables = ['Efield']
# gas_var_labels = ['; e$^-$', '; Ar$^+$']
gas_var_labels = ['; el', '; ex', '; iz']
num_gas_vars = len(gas_variables)
gas_var_styles = [styles_list[i % 3] for i in range(num_gas_vars)]
gas_var_label_dict = {x:y for x,y in zip(gas_variables, gas_var_labels)}
gas_var_style_dict = {x:y for x,y in zip(gas_variables, gas_var_styles)}
liquid_variables = ['emliq_lin']
liq_var_labels = ['; e$^-$', '; OH$^-$']
num_liq_vars = len(liquid_variables)
liq_var_styles = [styles_list[i % 3] for i in range(num_liq_vars)]
liq_var_label_dict = {x:y for x,y in zip(liquid_variables, liq_var_labels)}
liq_var_style_dict = {x:y for x,y in zip(liquid_variables, liq_var_styles)}

cellGasData, cellLiquidData, pointGasData, pointLiquidData = load_data(job_names, short_names, labels, mesh_struct, styles)

# for job in job_names:
#     pointGasData[job]['Points0'] = 1e-3 * pointGasData[job]['Points0']
#     cellGasData[job]['tot_gas_current'] = -cellGasData[job]['tot_gas_current']

cell_gas_generic(cellGasData, job_names, name_dict, gas_variables, 'Distance from Interface ($\mu$m)', 'Electric Field (V m$^{-1}$)', save = True, tight_plot = True, show_plot = False, job_colors = job_color_dict, var_styles = gas_var_style_dict, var_labels = gas_var_label_dict, save_string = 'Dummy', x1min = xmin, x1max = xmax, x1ticks = ticks, x1ticklabels = ticklabels, y1min = -1e6)#, yscale = 'log')
# cell_coupled_generic(cellGasData, cellLiquidData, job_names, name_dict, gas_variables, liquid_variables, 'Distance from Interface ($\mu$m)', 'Liquid coordinate (m)', 'Electron Gas Density (\# m$^{-3}$)', 'Liquid Electron Density (\# m$^{-3}$)', save = True, tight_plot = False, show_plot = False, job_colors = job_color_dict, var_styles = gas_var_style_dict, var_labels = gas_var_label_dict, liq_var_styles = liq_var_style_dict, liq_var_labels = liq_var_label_dict, save_string = 'Dummy', yscale = 'log', x1ticks = ticks, x1ticklabels = ticklabels)# y1min = 1e17, y2min = 1e21, y1max = 1e19, y2max = 1e23, x1min = -.05e-3, x1max = 1.05e-3, x2min = 0.9e-7, x2max = 2.1e-7)#, )
