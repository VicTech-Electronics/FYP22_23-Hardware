from linear_regression import LinearRegression
import numpy as np
import pandas as pd

csv_training_data = pd.read_csv('csv_train_data_file.csv')
csv_test_data = pd.read_csv('csv_test_data_file.csv')

X_train = csv_training_data.drop('result', axis=1).values
y_train = csv_training_data['result']
y_train = np.array(y_train).reshape(-1, 1)

X_test = csv_test_data.drop('result', axis=1).values
y_test = csv_test_data['result']
y_test = np.array(y_test).reshape(-1, 1)


print(f'y_train: {y_test.shape}')
print(f'X_train: {X_test.shape}')


regressor = LinearRegression()
regressor.fit(X_train, y_train)

predicted = regressor.predict(X_test)

def mse(y_true, y_predicted):
    return np.mean((y_true - y_predicted) ** 2)


mse_value = mse(y_test, predicted)
print(mse_value)