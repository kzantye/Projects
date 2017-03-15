'''
 Program Name: Recommender.py
 Author: Kunal Zantye
 Program Intent: Model for Recommender System
 Input Data: train_all_txt.txt
 Output Data: Output.txt
 Compile Note: python Rocommender.py
 '''

#Import the following libraires
import numpy as np
import scipy.stats
import time

#To calculate the total execution time of the program
start_time = time.time()


#Class implementing the model for recommender sytem
class Recomender:

    #initialization
    def __init__(self,total_user,total_item):
        self.total_user=total_user
        self.total_item = total_item
        self.matrix = np.empty([self.total_user, self.total_item])
        self.simiMatrix = np.empty([self.total_user, self.total_user])
        self.outmatrix = np.empty([self.total_user, self.total_item])
        # np.savetxt("out.csv", matrix, delimiter=",",fmt='%-7.2f')

    #Module to read the train data
    def fileReader(self):
        f = open('train_all_txt.txt', 'r')
        for line in f:
            a, b, c = (int(x) for x in line.split())
            self.matrix[a, b] = c
        f.close()

    # Calculating User Based Similarity Matrix
    def similarity_matrix(self):
        for i in range(1, self.total_user):
            for j in range(1,self.total_user):
                self.simiMatrix[i,j]=scipy.stats.pearsonr(self.matrix[i,:], self.matrix[j,:])[0]

    # Calculating Prediction
    def prediction(self):
        for userid in range(1, self.total_user):
            for i in range(1,self.total_item):
                if self.matrix[userid, i]==0:
                    value=0.0
                    similarity_sum=0.0
                    for u in range(1,self.total_user):
                        if(self.matrix[u,i]==0):
                            continue
                        value= self.matrix[u,i]*abs(self.simiMatrix[userid,u]) + value
                        similarity_sum = abs(self.simiMatrix[userid, u]) + similarity_sum
                    #print >> file, dblDemo
                    if(similarity_sum==0.0):
                        rating=3
                    else:
                        rating=round(value/similarity_sum)
                    if(rating<1):
                        rating=1
                    if (rating > 5):
                        rating = 5
                    self.outmatrix[userid,i]=int(rating)
                else:
                    self.outmatrix[userid, i]=self.matrix[userid,i]

    # Module to write the result to output file
    def fileWriter(self):
        file = open('Output.txt', 'w')
        for i in range(1, self.total_user):
            for j in range(1, self.total_item):
                line = '%d %d %d' % (i, j, self.outmatrix[i, j])
                file.write("{}\n".format(line))
        file.close()


#MAIN()
rec_sys=Recomender(944,1683)
rec_sys.fileReader()
rec_sys.similarity_matrix()
rec_sys.prediction()
rec_sys.fileWriter()


print("--- %s seconds ---" % (time.time() - start_time))