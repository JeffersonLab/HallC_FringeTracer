# -*- coding: utf-8 -*-

from __future__ import division, print_function

from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import scipy.optimize as spo


def gauss(x, A, mu, sigma):
    return A * np.exp(-(x-mu)**2 / (2*sigma)**2)


colNames = ['x', 'y', 'z', 'particle.type']
particleTypeNames = {
    -1: 'other',
    0: 'e-',
    1: 'e+',
    2: 'gamma'
}


data = pd.read_csv(
    '../build-10/out_nt_bdScreenHits.csv',
    header=None,
    names=colNames,
    comment='#'
)

data = data[data['particle.type'] == 0]


def fitProfile(axis, range):
    histo, edges = np.histogram(data[axis], bins=100, range=range)
    centers = (edges[:-1] + edges[1:])/2
    width = edges[1] - edges[0]

    popti = [max(histo), 0, 10]
    popt, pcov = spo.curve_fit(gauss, centers, histo, p0=popti)

    pts = np.linspace(edges[0], edges[-1], 500)
    vals = gauss(pts, *popt)

    fig, ax = plt.subplots()

    ax.bar(centers, histo, align='center', width=width)
    ax.plot(pts, vals, 'r')

    txt = '$A = {:.3f}$\n'.format(popt[0])
    txt = txt + '$\mu = {:.3f} \, \mathrm{{mm}}$\n'.format(popt[1])
    txt = txt + '$\sigma = {:.3f} \, \mathrm{{mm}}$'.format(popt[2])

    ax.text(
        0.05, 0.95, txt,
        ha='left', va='top',
        transform=ax.transAxes
    )

    ax.grid(True)
    ax.set_xlim(edges[-1], edges[0])
    ax.set_title('beam profile ' + axis)
    ax.set_xlabel('$' + axis + '_\mathrm{dump} \quad [\mathrm{mm}]$')
    ax.set_ylabel('$\#_\mathrm{counts}$')
    fig.tight_layout()

    pp.savefig()
    plt.close(fig)


with PdfPages('fit_position.pdf') as pp:
    fitProfile('x', (-200, 0))
    fitProfile('y', (-100, 100))
