import matplotlib.pyplot as plt
x = pointGasData['mean_en_se_coeff_pt3']['x_node']
y = pointGasData['mean_en_se_coeff_pt3']['e_temp']

x2,y2 = zip(*sorted(zip(x,y),key=lambda x: x[0]))

plt.plot(x,y)
plt.show()
plt.plot(x2,y2)
plt.show()
