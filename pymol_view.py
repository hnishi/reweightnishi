print "pymol_view.py v1.1.1"
#try:
from pymol.cmd import * 
#except:
import glob
fff = glob.glob('*.pdb')
print fff
func = lambda a:a.split('.')[0]
fff = map(func,fff)
print fff

#settings

#load('/work1/hnishi/3rdTrial/crystal.pdb')
#refpdb = "crystal"

# 

map(load,glob.glob('*.pdb'))
cmd.remove("resn WAT | hydrogen | resn CIP+CIM+NME")

#align_nishi2 = lambda a: align(a,fff[0])

"""
def align_nishi(aaa):
	align(aaa,fff[0])
	return
map(align_nishi,fff[1:])
"""
#map(align_nishi2,fff[1:])
#map(lambda a: align(a,fff[0]),fff[1:])
#map(lambda a: align(a,"crystal"),fff[0:])
map(lambda a: align(a,refpdb),fff[0:])

"""
for i in range(len(fff)-1):
	#align("%s%s%s"%(fff[0],),fff[i+1])
	#align(fff[0],fff[i+1])
	align(fff[i+1],fff[0])
"""
cmd.hide("everything")
cmd.show("ribbon")
#cmd.select("h3","i. 210-222")
#cmd.orient("h3")

#color('gray70')
color('red',refpdb)

""" # for No crystal
### cut below here and paste into script ###
set_view ("\
     0.200583056,    0.873856008,   -0.442877114,\
    -0.113997869,   -0.428173661,   -0.896476626,\
    -0.973021448,    0.230303943,    0.013732688,\
     0.000000000,    0.000000000,  -58.141948700,\
    -0.692646980,  -12.820801735,    3.635968685,\
    41.228359222,   75.055503845,    0.000000000 ")
### cut above here and paste into script ###
"""
# for superposition to crystal structure
### cut below here and paste into script ###
set_view ("\
     0.969908178,   -0.242554322,    0.021179659,\
     0.141093805,    0.489027172,   -0.860781312,\
     0.198428720,    0.837866187,    0.508534372,\
     0.000000000,    0.000000000,  -80.100784302,\
     5.964861870,   15.190623283,   22.049352646,\
    63.152069092,   97.049507141,  -20.000000000 ")
### cut above here and paste into script ###

#cmd.ray()
#cmd.png("all.png")
#save("all.pse")

#quit()
	
