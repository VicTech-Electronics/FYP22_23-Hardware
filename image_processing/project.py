import cv2 as cv
import serial
from processing import recognition
from connection import postRequest

camera = cv.VideoCapture(0)
port = serial.Serial('COM8', 9600)

while True: 
    print('Waiting for serial data')
    while port.in_waiting < 1:
        examination_data = port.readline()
        daexamination_data = examination_data.decode()

        ret, frame = camera.read()
        if not ret:
            print('Fail to capture image')
            break
        
        cv.imwrite('captured_image.jpg', frame)

        path = 'captured_image.jpg'
        code = recognition(path)

        postRequest(code, examination_data)
        