import random

for i in range(20):

	with open('input'+str(i)+'.txt','w') as file:

		for j in range(200):
			
			x = random.uniform(-1000,1000)
			y = random.uniform(-1000,1000)
			file.write('('+'%.4f'%x+','+'%.4f'%y+')\n')
