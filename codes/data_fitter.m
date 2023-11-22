% Load the csv file as a table
data = readtable('e_v_data.csv');

% Extract the input and output variables
ep = data.ep;
vl = data.vl;
vr = data.vr;
e = data.e;

% Use fitrauto function to fit a nonlinear model
model = fitrauto([ep vl vr], e, "Learners","all-linear");

% Display the fitted model equation
model.Equation
