# Sensor-Fusion---Summer-Internship
The SONAR fusion kalman file contains the code of arduino , which gets the data from 3 sonar sensors and averages them. and one dimensional kalman filter is applied on it for the purpose of smoothening and reduction of noise in the output.

The kalman Code contains the code for normal kalman filter algorithm for the fusion of the IMU and GPS data.Proper initialization should be  done for better output.

The Error State Extended Kalman Filter contains the code for ESEKF and outputs the plot of ground truth vs prediction. The prediction is plotted to further extent as it was made for prediction when the ground truth is not available. The code imports 
rotation.py which contains the necessary functions to perform on the ESEKF.
