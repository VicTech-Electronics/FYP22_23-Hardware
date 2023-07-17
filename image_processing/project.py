import cv2 as cv
import serial
import time
import keyboard
from processing import recognition
from connection import postRequest

camera = cv.VideoCapture(0)
port = serial.Serial('COM8' , 9600)

while True: 
    print('Waiting for serial data')
    time.sleep(0.1)

    if port.in_waiting > 0:
        examination_data = port.readline()
        examination_data = examination_data.decode()
        examination_data.strip()

        ret, frame = camera.read()
        if not ret:
            print('Fail to capture image')
            break
        
        cv.imwrite('captured_image.jpg', frame)

        path = 'captured_image.jpg'
        code = recognition(path)

        response = postRequest(code, examination_data)
        print(f'WEB response: {response}')

    
    if keyboard.is_pressed('q'):
        print("Program closed")
        break
        