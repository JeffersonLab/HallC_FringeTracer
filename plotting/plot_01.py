# -*- coding: utf-8 -*-

from __future__ import division, print_function

from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


colNames = ['x', 'y', 'z', 'particle.type']
particleTypeNames = {
    -1: 'other',
    0: 'e-',
    1: 'e+',
    2: 'gamma'
}


data = pd.read_csv(
    '../build-10/out_nt_screen_hits.csv',
    header=None,
    names=colNames,
    comment='#'
)

particleTypes = sorted(data['particle.type'].unique())


def plot(data, typeName, pp):
    histo, xEdges, yEdges = np.histogram2d(
        data['x'], data['y'],
        bins=400, range=[[-400, 400], [-400, 400]]
    )

    histo = histo.T
    histoMasked = np.ma.masked_where(histo == 0, histo)

    fig, ax = plt.subplots()

    cm = ax.pcolormesh(
        xEdges, yEdges, histoMasked,
        cmap='viridis', rasterized=True
    )
    cb = fig.colorbar(cm)

    ax.plot(
        [-40, 40, 40, -40, -40],
        [-40, -40, 40, 40, -40],
        '-', color=(1.0, 0.0, 1.0),
        zorder=6
    )

    ax.grid(True)
    xlims = ax.get_xlim()
    ax.set_xlim(xlims[1], xlims[0])
    ax.set_title('{} hits'.format(typeName))
    ax.set_xlabel('$x_\mathrm{dump} \quad [\mathrm{mm}]$')
    ax.set_ylabel('$y_\mathrm{dump} \quad [\mathrm{mm}]$')
    cb.set_label('$\#_\mathrm{counts}$')
    fig.tight_layout()

    pp.savefig(dpi=150)


with PdfPages('plot.pdf') as pp:
    plot(data, 'all', pp)

    for particleType in particleTypes:
        dataType = data[data['particle.type'] == particleType]

        plot(dataType, particleTypeNames[particleType], pp)
