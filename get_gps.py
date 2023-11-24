#!/usr/bin/env python

import time
from pymavlink import mavutil

# Set up the connection to the Pixhawk
master = mavutil.mavlink_connection('udpin:localhost:14550')

# Wait for the heartbeat message to ensure the connection is ready
master.wait_heartbeat()

# Continuously loop to get GPS coordinates and height
while True:
    # Get the current GPS data from the Pixhawk
    gps_data = master.recv_match(type='GLOBAL_POSITION_INT', blocking=True)

    file = open('gps_data.txt','a+')
    #Extract the GPS coordinates and height from the data
    lat = gps_data.lat / 10000000.0
    lon = gps_data.lon / 10000000.0
    alt = gps_data.alt / 1000.0
    output = 'Lat' + str(lat) +',Lon' + str(lon) +',Alt'+ str(alt) +'\n'
    file.write(output)
    file.close()

    # Print the GPS coordinates and height
    print("Latitude: {0:.6f} degrees".format(lat))
    print("Longitude: {0:.6f} degrees".format(lon))
    print("Altitude: {0:.2f} meters".format(alt))

    # Wait for one second before getting the GPS data again

    #print(master.recv_match(blocking=True).to_dict())
    time.sleep(0.5)
