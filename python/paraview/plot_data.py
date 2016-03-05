import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
from matplotlib.ticker import ScalarFormatter
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})

def cell_gas_generic(cellGasData, job_names, name_dict, gas_variables, x1label, y1label, save = False, tight_plot = True, x1ticks = [], x1ticklabels = [], x1min=None, x1max=None, y1min=None, y1max=None, yscale=None, save_string="dummy", job_colors = None, var_labels = None, var_styles = None, indep_var = 'x', fontsize = 16, show_plot = True):
    fig = plt.figure()
    ax1 = plt.subplot(111)
    for job in job_names:
        plot_label = name_dict[job]
        for variable in gas_variables:
            if len(gas_variables) > 1:
                plot_label = name_dict[job] + var_labels[variable]
            ax1.plot(cellGasData[job][indep_var], cellGasData[job][variable], color = job_colors[job], linestyle = var_styles[variable], label = plot_label, linewidth=2)

    ax1.set_xlabel(x1label)
    ax1.set_ylabel(y1label)
    sf = ScalarFormatter()
    sf.set_scientific(True)
    sf.set_powerlimits((-3,4))
    sf.useOffset = False
    ax1.yaxis.set_major_formatter(sf)
    ax1.xaxis.set_major_formatter(sf)
    if len(x1ticks) > 0:
        ax1.set_xticks(x1ticks)
    if len(x1ticklabels) > 0:
        ax1.set_xticklabels(x1ticklabels)
    if x1min is not None:
        ax1.set_xlim(left=x1min)
    if x1max is not None:
        ax1.set_xlim(right=x1max)
    if y1min is not None:
        ax1.set_ylim(bottom=y1min)
    if y1max is not None:
        ax1.set_ylim(top=y1max)
    if yscale is not None:
        ax1.set_yscale(yscale)
    ax1.legend(loc='best', fontsize = fontsize)
    if tight_plot:
        fig.tight_layout()
    if save:
        fig.savefig('/home/lindsayad/Pictures/' + save_string + '.eps', format='eps')
    if show_plot:
        plt.show()

def cell_coupled_generic(cellGasData, cellLiquidData, job_names, name_dict, gas_variables, liquid_variables, x1label, x2label, y1label, y2label, save = False, tight_plot = True, x1ticks = [], x1ticklabels = [], x1min=None, x1max=None, y1min=None, y1max=None, x2ticks = [], x2ticklabels = [], x2min=None, x2max=None, y2min=None, y2max=None, yscale=None, save_string="dummy", job_colors = None, var_labels = None, var_styles = None, liq_var_labels = None, liq_var_styles = None, indep_var = 'x', fontsize = 16, show_plot = True):
    fig = plt.figure(figsize = (12., 7.), dpi = 80)
    plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
    ax1 = plt.subplot(121)
    for job in job_names:
        plot_label = name_dict[job]
        for variable in gas_variables:
            if len(gas_variables) > 1:
                plot_label = name_dict[job] + var_labels[variable]
            ax1.plot(cellGasData[job][indep_var], cellGasData[job][variable], color = job_colors[job], linestyle = var_styles[variable], label = plot_label, linewidth=2)

    ax1.set_xlabel(x1label)
    ax1.set_ylabel(y1label)
    sf = ScalarFormatter()
    sf.set_scientific(True)
    sf.set_powerlimits((-3,4))
    sf.useOffset = False
    ax1.xaxis.set_major_formatter(sf)
    ax1.yaxis.set_major_formatter(sf)
    if len(x1ticks) > 0:
        ax1.set_xticks(x1ticks)
    if len(x1ticklabels) > 0:
        ax1.set_xticklabels(x1ticklabels)
    if x1min is not None:
        ax1.set_xlim(left=x1min)
    if x1max is not None:
        ax1.set_xlim(right=x1max)
    if y1min is not None:
        ax1.set_ylim(bottom=y1min)
    if y1max is not None:
        ax1.set_ylim(top=y1max)
    if yscale is not None:
        ax1.set_yscale(yscale)
    ax1.legend(loc='best', fontsize = fontsize)

    ax2 = plt.subplot(122)
    for job in job_names:
        plot_label = name_dict[job]
        for liq_variable in liquid_variables:
            if len(liquid_variables) > 1:
                plot_label = name_dict[job] + liq_var_labels[liq_variable]
            ax2.plot(cellLiquidData[job][indep_var], cellLiquidData[job][liq_variable], color = job_colors[job], linestyle = liq_var_styles[liq_variable], label = plot_label, linewidth=2)

    ax2.set_xlabel(x2label)
    ax2.set_ylabel(y2label)
    ax2.xaxis.set_major_formatter(sf)
    ax2.yaxis.set_major_formatter(sf)
    if len(x2ticks) > 0:
        ax2.set_xticks(x2ticks)
    if len(x2ticklabels) > 0:
        ax2.set_xticklabels(x2ticklabels)
    if x2min is not None:
        ax2.set_xlim(left=x2min)
    if x2max is not None:
        ax2.set_xlim(right=x2max)
    if y2min is not None:
        ax2.set_ylim(bottom=y2min)
    if y2max is not None:
        ax2.set_ylim(top=y2max)
    ax2.yaxis.tick_right()
    ax2.yaxis.set_label_position("right")
    if yscale is not None:
        ax2.set_yscale(yscale)
    ax2.legend(loc='best', fontsize = fontsize)
    if tight_plot:
        fig.tight_layout()
    if save:
        fig.savefig('/home/lindsayad/Pictures/' + save_string + '.eps', format='eps')
    if show_plot:
        plt.show()
    plt.close()

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
