from linear_regression import LinearRegression
import numpy as np

regressor = LinearRegression()
regressor.fit(X_train, y_train)
predicted = regressor.predict(X_test)

def mse(y_true, y_predicted):
    return np.mean((y_true - y_predicted) ** 2)


mse_value = mse(y_test, predicted)
print(mse_value)