import random


f = open("array.txt","w")


random_array = open("rand.txt","w")
ascending_array = open("ascend.txt","w")
descending_array = open("descend.txt","w")

size_of_array = 10000

list = []

random_array.write(""+str(size_of_array)+"\n")
ascending_array.write(""+str(size_of_array)+"\n")
descending_array.write(""+str(size_of_array)+"\n")

for i in range(0,size_of_array):
    num = random.randint(0,15000)
    list.append(num)

for num in list:
    random_array.write(""+str(num)+"\n")

list.sort()
for num in list:
    ascending_array.write(""+str(num)+"\n")

list.sort(reverse = True)
for num in list:
    descending_array.write(""+str(num)+"\n")
