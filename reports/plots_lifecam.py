import numpy as np
import matplotlib.pyplot as plt

BATCH_PROPS = {}
BATCH_PROPS['20'] = { 'color' : 'g' }
BATCH_PROPS['30'] = { 'color' : 'b' }
BATCH_PROPS['40'] = { 'color' : 'r' }
BATCH_PROPS['50'] = { 'color' : 'c' }

_batchLifecam_chessboard = {}
_batchLifecam_chessboard['pattern'] = 'chessboard'
_batchLifecam_chessboard['results'] = {}
_batchLifecam_chessboard['results']['20'] = [ 0.374204,
                                              0.386824, 0.387518, 0.388246, 0.387661, 0.387104,
                                              0.387812, 0.387095, 0.387599, 0.387075, 0.387289,
                                              0.387346, 0.387846, 0.388015, 0.387295, 0.387837,
                                              0.386991, 0.387972, 0.387119, 0.387245, 0.38766 ]
_batchLifecam_chessboard['results']['30'] = [ 0.415195,
                                              0.427997, 0.427879, 0.428498, 0.428606, 0.428238,
                                              0.42822, 0.428391, 0.428177, 0.42828, 0.428312,
                                              0.428412, 0.428384, 0.428483, 0.427958, 0.428181,
                                              0.428223, 0.428093, 0.428663, 0.42821, 0.428411 ]
_batchLifecam_chessboard['results']['40'] = [ 0.336462,
                                              0.286344, 0.286971, 0.286356, 0.287404, 0.286966,
                                              0.287148, 0.287011, 0.287655, 0.286647, 0.286731,
                                              0.287288, 0.28679, 0.286553, 0.286748, 0.28636,
                                              0.286908, 0.28685, 0.287676, 0.286633, 0.287172 ]
_batchLifecam_chessboard['results']['50'] = [ 0.306374,
                                              0.327822, 0.326808, 0.326679, 0.326878, 0.326855,
                                              0.326507, 0.326885, 0.326483, 0.326695, 0.326826,
                                              0.326585, 0.326698, 0.326799, 0.326766, 0.326531,
                                              0.326686, 0.32708, 0.32655, 0.326698, 0.326697 ]

_batchLifecam_asymmetric = {}
_batchLifecam_asymmetric['pattern'] = 'asymmetric'
_batchLifecam_asymmetric['results'] = {}
_batchLifecam_asymmetric['results']['20'] = [ 0.222345,
                                              0.223197, 0.222766, 0.222986, 0.22308, 0.22285,
                                              0.223124, 0.22281, 0.222959, 0.22299, 0.22304,
                                              0.222617, 0.223003, 0.222914, 0.222849, 0.222864,
                                              0.223087, 0.222817, 0.222988, 0.222809, 0.222763 ]
_batchLifecam_asymmetric['results']['30'] = [ 0.331330,
                                              0.320094, 0.326128, 0.328878, 0.328007, 0.32825,
                                              0.327919, 0.327751, 0.328012, 0.327937, 0.327862,
                                              0.327937, 0.327859, 0.327842, 0.328008, 0.327971,
                                              0.3281, 0.327765, 0.32812, 0.327904, 0.328184 ]
_batchLifecam_asymmetric['results']['40'] = [ 0.259684,
                                              0.249012, 0.248585, 0.248689, 0.24874, 0.248602,
                                              0.248739, 0.248725, 0.248731, 0.248795, 0.248591,
                                              0.248512, 0.248739, 0.24882, 0.248621, 0.248766,
                                              0.248721, 0.24864, 0.248798, 0.248643, 0.248669 ]
_batchLifecam_asymmetric['results']['50'] = [ 0.264687,
                                              0.26305, 0.26317, 0.263294, 0.263293, 0.263125,
                                              0.263336, 0.263146, 0.263032, 0.263158, 0.26323,
                                              0.263317, 0.26324, 0.263366, 0.263183, 0.263152,
                                              0.263146, 0.263316, 0.263362, 0.263252, 0.26316 ]

_batchLifecam_rings = {}
_batchLifecam_rings['pattern'] = 'rings'
_batchLifecam_rings['results'] = {}
_batchLifecam_rings['results']['20'] = [ 0.306374,
                                         0.20859, 0.213348, 0.209956, 0.207824, 0.215483,
                                         0.210602, 0.212177, 0.210893, 0.211693, 0.209232,
                                         0.215479, 0.212218, 0.211494, 0.208487, 0.215407,
                                         0.209408, 0.212108, 0.212573, 0.212114, 0.21358 ]
_batchLifecam_rings['results']['30'] = [ 0.259630,
                                         0.244397, 0.244801, 0.245215, 0.244375, 0.245156,
                                         0.245261, 0.246108, 0.24472, 0.243604, 0.245569,
                                         0.24595, 0.244628, 0.246315, 0.243777, 0.242965,
                                         0.245809, 0.245171, 0.244373, 0.246472, 0.24536 ]
_batchLifecam_rings['results']['40'] = [ 0.270549,
                                         0.270123, 0.267186, 0.269603, 0.262515, 0.260166,
                                         0.264552, 0.269376, 0.268108, 0.264286, 0.267724,
                                         0.260501, 0.267936, 0.26445, 0.268995, 0.261186,
                                         0.264746, 0.272383, 0.262331, 0.258778, 0.258839 ]
_batchLifecam_rings['results']['50'] = [ 0.374728,
                                         0.375525, 0.373785, 0.37338, 0.373912, 0.37327,
                                         0.372868, 0.373604, 0.373998, 0.373984, 0.373429,
                                         0.372022, 0.373695, 0.373307, 0.373024, 0.373033,
                                         0.372595, 0.373622, 0.373831, 0.372724, 0.373889 ]


def plotBatchesResults( batch, figureBaseIndx = 1 ) :

    _countFigure = 0

    for key in BATCH_PROPS :

        plt.figure( figureBaseIndx + _countFigure )

        _color = BATCH_PROPS[key]['color']
        _results = batch['results'][key]
        _pattern = batch['pattern']

        _label = _pattern + " - " + key

        ii = [ ( i + 1 ) for i in range( len( _results ) ) ]
        yy = [ _res for _res in _results ]

        plt.plot( ii, yy, _color, label = _label )
        plt.legend( loc = 'lower right', shadow = True )
        plt.grid( True )


plotBatchesResults( _batchLifecam_chessboard, 1 )

plt.show()
