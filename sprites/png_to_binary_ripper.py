# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    png_ripper.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashih <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:51:07 by ashih             #+#    #+#              #
#    Updated: 2018/01/10 20:53:25 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import struct
import numpy as np
import matplotlib.pylab as plb
import sys

def rip_sprite(file):
	array = plb.imread(file)
	array[:, :, 0:3] *= 255;

	fd = open(file.replace(".png", ".sprite"), "wb")
	fd.write(struct.pack("i", array.shape[0]))
	fd.write(struct.pack("i", array.shape[1]))

	for i in range(0, array.shape[0]):
		for j in range(0, array.shape[1]):
			fd.write(struct.pack("i", (int(array[i][j][0] * array[i][j][3]) << 16) |
									  (int(array[i][j][1] * array[i][j][3]) << 8) |
									  (int(array[i][j][2] * array[i][j][3]) << 0)))
			fd.write(struct.pack("i", int(array[i][j][3] * 255)))
	fd.close()

for arg in sys.argv[1:]:
	rip_sprite(arg)
