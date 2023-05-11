#!/usr/bin/env python3

import os

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

def draw(filenames, labels):
    dataX = []
    dataY = []

    plt.rcParams["legend.markerscale"] = 2.0
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.size'] = '12'
    plt.rcParams["legend.loc"] = "upper left" # 'upper left', 'upper right', 'lower left', 'lower right', 'center'
    plt.rcParams["legend.fontsize"] = "5"
    
    cm = 1/2.54  # centimeters in inches
    fig = plt.figure(figsize=(10*cm, 7*cm))
    ax = fig.add_subplot(111)
    ax.set_title("")
    ax.set(xlabel="Number of threads", ylabel="Speedup")
    ax.label_outer()
    
    ax.xaxis.set_tick_params(direction='in', which='both')
    ax.yaxis.set_tick_params(direction='in', which='both')
    ax.xaxis.set_major_locator(ticker.MultipleLocator(1))
    # ax.yaxis.set_major_locator(ticker.MultipleLocator(1))

    count_versions = 0
    lbls = []
    for (fname, datalabel) in zip(filenames, labels):
        data = np.loadtxt(fname)
        dataX.append((data[:, 0]))
        dataY.append(data[:, 1])
        lbls.append(datalabel)
        count_versions += 1

    thrd_cur = min(dataX[0])
    thrd_step = dataX[0][1] - dataX[0][0] if len(dataX[0]) > 1 else 0
    thrd_end = max(dataX[0])
    wdh = 0.8 / (count_versions + 1)
    
    first_iteration = True
    p_offset = -wdh * count_versions * 0.5
    while thrd_cur <= thrd_end:
        if first_iteration:
            lbl = "Linear speedup"
            first_iteration = False
        else:
            lbl = ""
        ax.bar(thrd_cur + p_offset, thrd_cur, label = lbl, color = "blue", width = wdh);
        thrd_cur += thrd_step
    
    # p_offset += wdh * 0.5
    p_offset += wdh
    for i in range(0, len(dataX)):
        ax.bar(dataX[i] + p_offset, dataY[i], label=lbls[i], width = wdh);
        p_offset += wdh
    

    plt.tight_layout()
    ax.legend()
    fig.savefig('chart.png', dpi=300)
    # fig.savefig('chart.pdf', dpi=300)

if __name__ == "__main__":
    draw(["prog1.dat", "prog2.dat", "prog3.dat", "prog4.dat", "prog5.dat"], ["Single critical section", "6 atomic operations", "N blocks", "Excess calculations", "Matrix of forces"])
    # draw(["prog1.dat", "prog2.dat", "prog3.dat", "prog4.dat", "prog5.dat"], ["Версия 1", "Версия 2", "Версия 3", "Версия 4", "Версия 5"])
