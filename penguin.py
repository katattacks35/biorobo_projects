import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import seaborn as sns
import pandas as pd
import csv
import pandas as pd
import seaborn as sns
from pylab import rcParams
import matplotlib.pyplot as plt


def plot_correlation(data):
    '''
    plot correlation's matrix to explore dependency between features
    '''
    # init figure size
    rcParams['figure.figsize'] = 15, 20
    fig = plt.figure()
    sns.heatmap(data.corr(), annot=True, fmt=".2f")
    plt.show()
    fig.savefig('corr.png')

# load your data
data  = pd.read_csv('penguins.csv')

# plot correlation & densities
plot_correlation(data)

X = []
Y = []

#Reading data for penguins
penguins = csv.reader("penguins.csv")

#Splitting dataset into testing and training
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2)

#Establishing KNN classifier
from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
ypred_test=knn.predict(X_test)

# Import the function confusion_matrix (if needed)
from sklearn.metrics import confusion_matrix

#Build the confusion matrix from the target test set y_test and our predicted values ypred_test
cm = confusion_matrix(y_test, ypred_test)

#Metrics
from sklearn.metrics import precision_score, recall_score, accuracy_score
accuracy_score(y_test, ypred_test)
recall_score(y_test, ypred_test, average='macro')
precision_score(y_test, ypred_test, average='macro')

#Linear Regression
from sklearn.linear_model import LinearRegression
ln = LinearRegression()
#Fitting data to train the model
reg = ln.fit(train_data_X,train_data_Y)
#Predict Y values
ypred_ln = ln.predict(test_data_X)

#Mean Squared Error (MSE)
from sklearn.metrics import mean_squared_error
mean_squared_error(Y,Ynew)

#r2 - variance of y explained by independent variables (fitted model vs mean of target/y values)
from sklearn.metrics import r2_score
print(r2_score(Y, Ynew))

#K-Fold cross validation
from sklearn.model_selection import KFold
kf = KFold(n_splits=10, random_state=63, shuffle=True)





