import requests
import json
from serial import Serial
from time import sleep

def main():
    portLinux = '/dev/ttyUSB0'
    portWindows = 'COM3'
    ser = Serial(portLinux, 115200)

    apiUrl = "http://dojot.fabiotest.online:5000"
    devideId = '/a6b59d'

    while True:
        sleep(5)

        serialData = ser.readline()
        serialData = serialData.decode()
        serialData = serialData.rstrip()
    
        print("reading = {}".format(serialData))

        jsonData = json.loads(serialData)
        response = requests.post(apiUrl+devideId, json=jsonData)
        
        print('status code = {}'.format(response.status_code))
        
if __name__ == '__main__':
    main()