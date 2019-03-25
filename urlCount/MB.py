import random,string
f = open('/100.txt','w+')
for i in range(1,6790000):
	num=string.ascii_letters+string.digits
	x = random.randint(1, 10)
	f.write('www.'+str("".join(random.sample(num,x))+'.com'))
	f.write('\n')
f.seek(0)
f.close()
