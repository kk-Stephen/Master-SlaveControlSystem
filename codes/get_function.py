import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score, mean_squared_error, mean_absolute_error

df = pd.read_csv("D:/Github/Master-SlaveControlSystem/codes/data/e_v_data/e_v_data.csv")

X = df[['vl', 'vr', 'ep']]
y = df['e']

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 选择多项式的阶数
degree = 3

# 创建多项式回归模型
poly = PolynomialFeatures(degree=degree)

#[‘1’, ‘e_p’, ‘v_l’, ‘v_r’, ‘e_p^2’, ‘e_p v_l’, ‘e_p v_r’, ‘v_l^2’, ‘v_l v_r’, ‘v_r^2’,
# ‘e_p^3’, ‘e_p^2 v_l’, ‘e_p^2 v_r’, ‘e_p v_l^2’, ‘e_p v_l v_r’, ‘e_p v_r^2’, ‘v_l^3’, ‘v_l^2 v_r’, ‘v_l v_r^2’, ‘v_r^3’]

X_train_poly = poly.fit_transform(X_train)

X_test_poly = poly.transform(X_test)

# 训练模型
reg = LinearRegression()
reg.fit(X_train_poly, y_train)

# 在测试集上进行预测
y_pred = reg.predict(X_test_poly)

r2 = r2_score(y_test, y_pred)
mse = mean_squared_error(y_test, y_pred)
mae = mean_absolute_error(y_test, y_pred)

# 打印模型的系数
print(f'The degree of the polynomial function is {degree}')
print(f'The coefficients of the polynomial function are {reg.coef_}')
print(f'The intercept of the polynomial function is {reg.intercept_}')
print(f'The R-squared of the model is {r2}')
print(f'The mean squared error of the model is {mse}')
print(f'The mean absolute error of the model is {mae}')