from sklearn.ensemble import AdaBoostClassifier
from sklearn.datasets import make_classification
import numpy as np
import sys
np.set_printoptions(threshold=sys.maxsize)
from scipy.sparse import csc_matrix
"""
Simple comment
"""

# use this to divide
divideCenter = 201

matrix = np.loadtxt("newClevelandNoAmount.txt", usecols=range(14), dtype=int)
matrixLower = matrix[:divideCenter, :14]
matrixUpper = matrix[divideCenter:, :14]

"""
print(matrix)
print(type(matrix))
print("------------------------------------------------------------")
print(matrixLower)
print("------------------------------------------------------------")
print(matrixUpper)
"""

diagnoseColumn = matrix[:,13]
matrix = np.delete(matrix, 13, 1)

clf = AdaBoostClassifier(n_estimators=50, random_state=0)

print(clf.fit(matrix, diagnoseColumn))
print(clf.predict([[61, 1, 4, 138, 166, 0, 2, 125, 1, 36, 2, 1, 3]])) #1
print(clf.predict([[61, 1, 4, 140, 207, 0, 2, 138, 1, 19, 1, 1, 7]])) #1
print(clf.predict([[47, 1, 3, 130, 253, 0, 0, 179, 0, 0, 1, 0, 3]])) #0
print("------------------------------------------------------------\n")

#   np.size(matrixUpper, 0)

for i in range(np.size(matrixUpper, 0)):
    tmpData = matrixUpper[i][:13]
    #print(tmpData)
    print(clf.predict([tmpData]))

print(clf.score(matrix, diagnoseColumn))






