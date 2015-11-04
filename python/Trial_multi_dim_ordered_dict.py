from collections import OrderedDict

# class DefaultOrderedDict(OrderedDict):
#     def __missing__(self, key):
#         self[key] = type(self)()
#         return self[key]

# d = DefaultOrderedDict()

# d['a']['b']['c'] = 'd'
# d['a'][1][2] = 3
# d['f']['g']['e'] = 'g'
# d['f'][5][6] = 7
# d['a']['foo']['bar'] = 'hello world'

# print [(i, j, k, d[i][j][k]) for i in d for j in d[i] for k in d[i][j]]

# x = OrderedDict()
# for i in range(0,10):
#     x[i] = {}
#     for j in range(0,10):
#         x[i][j] = i*j
# print x

# direct = '/home/lindsayad/gdrive/MooseOutput/'
# file_name = direct + 'Townsend_energy_electron_density.csv'
# rewrite = False
# with open(file_name,'r') as fin:
#     c = fin.read(1)
#     if c == '"':
#         rewrite = True
#         fin.seek(0)
#         data = fin.read().splitlines(True)
# if rewrite:
#     with open(file_name, 'w') as fout:
#         fout.writelines(data[1:])

data_dir = '/home/lindsayad/gdrive/MooseOutput/'
job_names = ['Townsend_energy','Rate_coeff_energy','Townsend_lfa','Townsend_var_elastic_energy']
dep_var_names = ['ion_density','electron_density','potential']

data = OrderedDict()
for job in job_names:
    data[job] = OrderedDict()
    for dep_var in dep_var_names:
        # file_name = data_dir + job + '_' + dep_var + '.csv'
        # rewrite = False
        # with open(file_name,'r') as fin:
        #     c = fin.read(1)
        #     if c == '"':
        #         rewrite = True
        #         fin.seek(0)
        #         data = fin.read().splitlines(True)
        # if rewrite:
        #     with open(file_name, 'w') as fout:
        #         fout.writelines(data[1:])
        data[job][dep_var] = 1.
        # data[job][dep_var] = np.loadtxt(file_name,delimiter=',')
