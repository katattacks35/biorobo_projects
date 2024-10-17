#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  1 13:47:01 2023

@author: karolinasiekanska
"""

#ex3 renewables

#1
import csv
import matplotlib.pyplot as plt

months = ["January","February","March"
          ,"April","May","June","July",
          "August","September","October",
          "November","December"]

#open the file containing solar intensities in december
def readfile(filename):
    """
    Reads a csv file and returns the contents as a list

    Parameters
    ----------
    filename : String
        Name of file.

    Returns
    -------
    List
        Contents of file as a list.

    """
    with open(filename,"r") as file:
        readfile = csv.reader(file)
        return list(readfile)

def SolarPower(I,E=0.13,H=0.8,W=1):
    """
    Uses equation (10) to calculate the solar power output.

    Parameters
    ----------
    E : Float
        Efficiency. Default is 0.13 for type A
    H : Float
        Height. Default is 0.8 for type A
    W : Float
        Width. Default is 1 for type A
    I : Float
        Intensity.

    Returns
    -------
    Float
        Power of the solar panel.

    """
    return E*H*W*I

#open the file containing solar intensities in december
Intensity = readfile("Solar_intensity_December.csv")
 
#delete the units from top of .csv file
del Intensity[0]

typeAPower_Dec = []
typeBPower = []#setup arrays for the 3 types of solar power and one for time

typeCPower = []
time = []

#run through each data point and calculate the power output, and record the time
for item in Intensity:
    typeAPower_Dec.append(SolarPower(float(item[1])))
    typeBPower.append(SolarPower(float(item[1]),0.22,0.6,0.5))
    typeCPower.append(SolarPower(float(item[1]),0.16,0.6,0.6))
    time.append(float(item[0]))
    
#plot the 3 points on the graph
plt.plot(time,typeAPower_Dec,label="Type A")
plt.plot(time,typeBPower,label="Type B")
plt.plot(time,typeCPower,label="Type C")
plt.xlabel("Time (Hours)")
plt.ylabel("Power (W)")
plt.legend()
plt.title("Power output of 3 types of solar panel during December")
plt.savefig("ex3_question1.pdf", format="pdf")
plt.show()

#2
#canpower checks how many times throughout the day the house can be powered by 10 panels
canpower = 0
for item in typeAPower_Dec:
    #when 10x the power output of 1 panel >250, it counts it as powered
    if item*10 >=250:
        canpower+=1
        
#calculate the percentage and output
percentage = (canpower/24)*100
print("Type A Solar panels power the Home's heating ", percentage, "% of the time.")

#3
#calculating the average power output monthly from a type A solar panel
MonthlyPower = []
date = []
#find each month of data correctly by concatenating the name of the month 
#from the months list to the filename prefixes, ensuring data is recorded in the correct order
for i in range(12):
    Intensity = readfile("Solar_intensity_"+months[i]+".csv")
    date.append(i+1)
    #delete the units from the list
    del Intensity[0]
    #sum the total power, then divide by 24 to obtain an average
    totPower = 0
    for item in Intensity:
        totPower+=SolarPower(float(item[1]))
    totPower/=24
    MonthlyPower.append(totPower)

plt.title("Average Power from solar Panel A throughout the year")
plt.xlabel("Month")
plt.ylabel("Average Power (W/hr)")
plt.plot(date,MonthlyPower)
plt.savefig("ex3_question3.pdf", format="pdf")
plt.show()

#4

def ConvertToMs(mph):
    """
    Converts inputted windspeed in miles per hour (mph) to Meters per second(M/s)

    Parameters
    ----------
    mph : Float
        Windspeed (Mph).

    Returns
    -------
    Float
        Windspeed(M/s).

    """
    return mph*0.44704

def RotationRate(initrot,windspeed):
    """
    Calculates the rotation rate of the turbine given the rotation rate of it
    at a previous timestep, according to equation (12)

    Parameters
    ----------
    initrot : Float
        "Initial Rotation", meaning the rotation speed in previous timestep.
    windspeed : Float
        Windspeed during timestep.

    Returns
    -------
    Float
        The updated windspeed after dt.

    """
    return initrot+(dt/M)*(C*windspeed**2-R*initrot)

def WindPower(rotspeed):
    """
    Calculates the power output from the turbine according to equation (11)

    Parameters
    ----------
    rotspeed : Float
        Rotation speed of the turbine.

    Returns
    -------
    Float
        Power output in Watts.

    """
    return (K*rotspeed**2)/(1+(f*(rotspeed**2)))

#determine power from wind generator
#set constants from question
K,f,M,C,R,dt = 0.6,4e-4,6.2e5,25,2.1,3600
Wind = readfile("wind_data.csv")
    
#delete line of names of months and setup a list of the winds only in july
julyWind = []
del Wind[0]

#convert wind into m/s
for item in Wind:
    julyWind.append(ConvertToMs(float(item[7])))
rotrate = [0]
#find the rotation rate as shown in the question and plot it with time
for i in range(23):
    rotrate.append(RotationRate(rotrate[i],julyWind[i]))
plt.xlabel("Hour")
plt.ylabel("Rotation speed (Rad/s)")
plt.title("Rotation rate of a wind turbine in July")
plt.plot(time,rotrate)
plt.savefig("ex3_question4.pdf",format="pdf")
plt.show()
#print out the power at 5pm (17:00)
windfivepm = WindPower(rotrate[17])
print("The power out of the Wind Turbine at 5pm is " ,windfivepm, "W.")

#5
#find power determined hourly throughout the year from 6 solar panels and a wind generator
#a list of the lengths of each month
monthlength = [30,31,31,30,31,30,31]
#set up lists for the total solar output and time
allsolar = []
DecemberSolarpower = []
alltime = []
#run through each month
for i in range(len(monthlength)):

    Intensity = readfile("Solar_intensity_"+months[i+5]+".csv")
    #setup temporary list of power made in day
    power = []
    #remove units from list
    del Intensity[0]
    #convert intensity to power
    for item in Intensity:
        power.append(6*SolarPower(float(item[1])))
    #add to total power made each hour for every day of month
    #this is easily repeatable as each day experiences same hours of daylight
    #as specified in question
    for k in range(monthlength[i]):
        for item in power:
            allsolar.append(item)
            
#fill time list 
for i in range(len(allsolar)):
    alltime.append(i)
    
#setup list for total wind output
allwind = []

#list for rotation rate, starting at 0
rotrate = [0]

#for loop running through each month
for i in range(len(monthlength)):
    #reset windspeed throughout month each month
    windspeed = []
    for item in Wind:
        windspeed.append(ConvertToMs(float(item[i+6])))
    #run through each day in month with j
    for j in range(monthlength[i]):
        #run through each hour of day with k
        for k in range(24):
            #find the continuous rotation rate of the turbine(doesnt reset
            #each day unlike the solar power)
            rotrate.append(RotationRate(rotrate[-1],windspeed[k]))
            
#delete first rotate for matching size of lists
del rotrate[0]

#convert the rotation rate into power outputted
for item in rotrate:
    allwind.append(WindPower(item))   
#sum the solar and wind power for all power
totalpower = []
for i in range(len(allsolar)):
    totalpower.append(allwind[i]+allsolar[i])    
  
#plot solar and wind on same graph
plt.plot(alltime,allsolar,label="Solar Power")
plt.plot(alltime,allwind,label="Wind Power")
plt.title("Power throughout the year from 6 Solar panels and 1 wind turbine")
plt.xlabel("Time (Hour)")
plt.ylabel("Power (W)")
plt.legend()
plt.show()

#plot total power output
plt.title("Combine power from the 6 Solar panels and 1 Wind turbine throughout the year")
plt.xlabel("Time (Hour)")
plt.ylabel("Power (W)")
plt.plot(alltime,totalpower)
plt.savefig("ex3_question5.pdf",format="pdf")
plt.show()

PoweredinDec = True
#checks if ther power drops below 250W in december,
# 745 is chosen as 24*31 = 744 (hours in december)
for i in range(1,745):
    if totalpower[-i] <  250:
        PoweredinDec = False
        break
if PoweredinDec:
    print("The house is always powered more than 250W.")
else:
    print("House can drop below 250W during December")