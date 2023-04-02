import serial
import pymysql
import time
import functools

serialPort=serial.Serial(port=’/dev/ttyS0’,baudrate=9600,timeout=.1)

while True:
	data=serialPort.readline()[:-2]
	if data.isdigit():
		dbConn=pymysql.connect(“localhost”,”pi”,””,”ultrasonic_db”)
		with dbConn:
			cursor=dbConn.cursor()
			cursor.execute(“SELECT distanceCM from distanceLog order by tempId DESC LIMIT 1”)
			dbvalue=cursor.fetchone()
			if int(data)<dbvalue[0]-2 or int(data)>dbvalue[0]+2:
				cursor.execute(“INSERT INTO distanceLog (distanceCM) VALUES (%s)”,(data))
				dbConn.commit()
				cursor.execute(“SELECT distanceCM from distanceLog order by tempId DESC LIMIT 1”)
				dbvalue=cursor.fetchone()
				print(dbvalue[0])
				if dbvalue[0]<5:
                    serialPort.write(b”b\n”)
                if dbvalue[0]>20:
	                serialPort.write(b”a\n”)
