# -*- coding: utf-8 -*-

from __future__ import division, print_function

from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


colNames = ['x', 'y', 'z', 'particle.type', 'BPM no']
particleTypeNames = {
    -1: 'other',
    0: 'e-',
    1: 'e+',
    2: 'gamma'
}


data = pd.read_csv(
    '../build-10/out_nt_bpmScreenHits.csv',
    header=None,
    names=colNames,
    comment='#'
)

particleTypes = sorted(data['particle.type'].unique())


def plot(data, typeName, pp):
    histo, xEdges, yEdges = np.histogram2d(
        data['x'], data['y'],
        bins=300, range=[[-300, 300], [-300, 300]]
    )

    histo = histo.T
    histoMasked = np.ma.masked_where(histo == 0, histo)

    fig, ax = plt.subplots()

    cm = ax.pcolormesh(
        xEdges, yEdges, histoMasked,
        cmap='viridis', rasterized=True,
        zorder=6
    )
    cb = fig.colorbar(cm)

    circle = plt.Circle(
        (0, 0), 13.125/2*2.54*10,
        color=(1.0, 0.0, 1.0), fill=False,
        zorder=5
    )
    ax.add_artist(circle)

    ax.grid(True)
    xlims = ax.get_xlim()
    ax.set_xlim(xlims[1], xlims[0])
    ax.set_title('{} hits'.format(typeName))
    ax.set_xlabel('$x_\mathrm{dump} \quad [\mathrm{mm}]$')
    ax.set_ylabel('$y_\mathrm{dump} \quad [\mathrm{mm}]$')
    cb.set_label('$\#_\mathrm{counts}$')
    fig.tight_layout()

    pp.savefig(dpi=150)


with PdfPages('plot_BPM.pdf') as pp:
    for bpmNo in xrange(1, 3):
        plot(data[data['BPM no'] == bpmNo], 'BPM {}'.format(bpmNo), pp)
