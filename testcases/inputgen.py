import random

for i in range(20):

	with open('big_input'+str(i)+'.txt','w') as file:

		for j in range(500000):
			
			x = random.uniform(-100000,100000)
			y = random.uniform(-100000,100000)
			file.write('('+'%.2f'%x+','+'%.2f'%y+')\n')
