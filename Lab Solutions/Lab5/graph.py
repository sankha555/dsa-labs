import csv
import numpy as np 


with open("stats.txt", "r") as f:
    stats = f.readlines()
    
    for stat in stats:
        stat = stat.split(';')
        stat[2] = stat[2][:-2]
        print(stat)

fields = ["Input", "Stack", "Time"]
with open("out.csv", "w") as fout:
    writer = csv.writer(fout)
    writer.writerow(fields) 
    writer.writerows(stats)
    
np.savetxt("stats.csv",  
           stats, 
           delimiter =", ",  
           fmt ='% s') 