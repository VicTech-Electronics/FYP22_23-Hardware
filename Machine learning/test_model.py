from linear_regression import LinearRegressionModel
import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

data = pd.read_csv('csv_data_file.csv')
X = data[['frame','smoke','vibration','gyroscope','brake']]  # Replace with your feature column names
y = data[['result']]  # Replace with your target column name

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
# Drop rows with NaN values
data.dropna(subset=['result'], inplace=True)
# Fill NaN values with the mean value
y_train.fillna(y_train.mean(), inplace=True)

print(f'y_train: {y_train}')
print(f'X_train: {X_train}')

model = LinearRegression()
model.fit(X_train, y_train)

predicted = model.predict(X_test)

mse = np.mean((predicted - y_test) ** 2)
rmse = np.sqrt(mse)
r2_score = model.score(X_test, y_test)

print("Mean Squared Error:", mse)
print("Root Mean Squared Error:", rmse)
print("R^2 Score:", r2_score)


# regressor = LinearRegressionModel()
# regressor.fit(X_train, y_train)

# predicted = regressor.predict(X_test)

# def mse(y_true, y_predicted):
#     return np.mean((y_true - y_predicted) ** 2)


# mse_value = mse(y_test, predicted)
# print(mse_value)