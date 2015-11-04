# This work is derived from the work at https://www.daniweb.com/software-development/python/code/216636/multiple-word-replace-in-text-python
# replace words in a text that match key_strings in a dictionary with the given value_string
# Python's regular expression module  re  is used here
# tested with Python24       vegaseat      07oct2005

import re
def multiwordReplace(text, wordDic):
    """
    take a text and replace words that match a key in a dictionary with
    the associated value, return the changed text
    """
    rc = re.compile('|'.join(map(re.escape, wordDic)))
    def translate(match):
        return wordDic[match.group(0)]
    return rc.sub(translate, text)
with open ("FileToParse.txt","r") as myfile:
    data=myfile.read()
str1 = \
"""When we see a Space Shuttle sitting on its launch pad, there are two big booster rockets
attached to the sides of the main fuel tank. These are solid rocket boosters, made by Thiokol
at their factory in Utah. The engineers who designed the solid rocket boosters might have preferred
to make them a bit fatter, but they had to be shipped by train from the factory to the launch site.
The railroad line from the factory runs through a tunnel in the mountains.  The boosters had to fit
through that tunnel.  The tunnel is slightly wider than the railroad track.  The width of the railroad
track came from the width of horse-drawn wagons in England, which were as wide as two horses' behinds.
So, a major design feature of what is the world's most advanced transportation system was determined
over two thousand years ago by the width of a horse's ass!
"""
# the dictionary has target_word : replacement_word pairs

#wordDic = {
#'booster': 'rooster',
#'rocket': 'pocket',
#'solid': 'salted',
#'tunnel': 'funnel',
#'ship': 'slip'}

wordDic = {
    'rxn1': 'Reaction1',
    'rxn2': 'Reaction2'}

rxnDic = {
  'rxn1[_qp]'	: 'k1[_qp]*em[_qp]*cw[_qp]',
  'rxn2[_qp]'	: 'k2[_qp]*em[_qp]*H2Op[_qp]',
  'rxn3[_qp]'	: 'k3[_qp]*em[_qp]*em[_qp]*cw[_qp]*cw[_qp]',
  'rxn4[_qp]'	: 'k4[_qp]*em[_qp]*H[_qp]*cw[_qp]',
  'rxn5[_qp]'	: 'k5[_qp]*em[_qp]*OH[_qp]',
  'rxn6[_qp]'	: 'k6[_qp]*em[_qp]*Om[_qp]*cw[_qp]',
  'rxn7[_qp]'	: 'k7[_qp]*em[_qp]*H3Op[_qp]',
  'rxn8[_qp]'	: 'k8[_qp]*em[_qp]*H2O2[_qp]',
  'rxn9[_qp]'	: 'k9[_qp]*em[_qp]*HO2m[_qp]*cw[_qp]',
  'rxn10[_qp]'	: 'k10[_qp]*em[_qp]*O2[_qp]',
  'rxn11[_qp]'	: 'k11[_qp]*em[_qp]*O[_qp]',
  'rxn12[_qp]'	: 'k12[_qp]*H[_qp]*cw[_qp]',
  'rxn13[_qp]'	: 'k13[_qp]*H[_qp]*H[_qp]',
  'rxn14[_qp]'	: 'k14[_qp]*H[_qp]*OH[_qp]',
  'rxn15[_qp]'	: 'k15[_qp]*H[_qp]*OHm[_qp]',
  'rxn16[_qp]'	: 'k16[_qp]*H[_qp]*H2O2[_qp]',
  'rxn17[_qp]'	: 'k17[_qp]*H2[_qp]*H2O2[_qp]',
  'rxn18[_qp]'	: 'k18[_qp]*H[_qp]*O2[_qp]',
  'rxn19[_qp]'	: 'k19[_qp]*H[_qp]*HO2[_qp]',
  'rxn20[_qp]'	: 'k20[_qp]*O[_qp]*cw[_qp]',
  'rxn21[_qp]'	: 'k21[_qp]*O[_qp]*O2[_qp]',
  'rxn22[_qp]'	: 'k22[_qp]*OH[_qp]*OH[_qp]',
  'rxn23[_qp]'	: 'k23[_qp]*OH[_qp]*Om[_qp]',
  'rxn24[_qp]'	: 'k24[_qp]*OH[_qp]*H2[_qp]',
  'rxn25[_qp]'	: 'k25[_qp]*OH[_qp]*OHm[_qp]',
  'rxn26[_qp]'	: 'k26[_qp]*OH[_qp]*HO2[_qp]',
  'rxn27[_qp]'	: 'k27[_qp]*OH[_qp]*O2m[_qp]',
  'rxn28[_qp]'	: 'k28[_qp]*Om[_qp]*cw[_qp]',
  'rxn29[_qp]'	: 'k29[_qp]*Om[_qp]*H2[_qp]',
  'rxn30[_qp]'	: 'k30[_qp]*Om[_qp]*H2O2[_qp]',
  'rxn31[_qp]'	: 'k31[_qp]*Om[_qp]*HO2m[_qp]',
  'rxn32[_qp]'	: 'k32[_qp]*Om[_qp]*O2m[_qp]',
  'rxn33[_qp]'	: 'k33[_qp]*Om[_qp]*O2m[_qp]*cw[_qp]',
  'rxn34[_qp]'	: 'k34[_qp]*OH[_qp]*H2O2[_qp]',
  'rxn35[_qp]'	: 'k35[_qp]*OH[_qp]*HO2m[_qp]',
  'rxn36[_qp]'	: 'k36[_qp]*H2Op[_qp]*cw[_qp]',
  'rxn37[_qp]'	: 'k37[_qp]*H3Op[_qp]*OHm[_qp]',
  'rxn38[_qp]'	: 'k38[_qp]*HO2[_qp]*cw[_qp]',
  'rxn39[_qp]'	: 'k39[_qp]*H3Op[_qp]*O2m[_qp]'}
# call the function and get the changed text

#str2 = multiwordReplace(str1, wordDic)

data2 = multiwordReplace(data, rxnDic)

output_file = open("Output.txt", "w")
output_file.write(data2)
output_file.close()
