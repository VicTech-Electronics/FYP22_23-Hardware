import serial
import keyboard
import cv2 as cv
from connection import postRequest
from image_recognition import recognition

port = serial.Serial('COM8', 9600)

while True: 
    print('Waiting for serial data')
    while port.in_waiting > 0:
        data = port.readline()
        data = data.decode()
        data = data.strip()

        if data == "capture":
            camera = cv.VideoCapture(0)
            if not camera.isOpened():
                print('Camera fail to open')
                break

            ret, frame = camera.read()
            if not ret:
                print('Fail to capture image')
                break

            cv.imwrite('image/captured_image.jpg', frame)
            path = 'image/captured_image.jpg'
            plate_number = recognition(path)
            data_to_post = {
                'type': 'plate',
                'number': str(plate_number)
            }
            response = str(postRequest(data_to_post))
            response.encode()

            if(response == 'exist'):
                port.write(response)
            else:
                port.write(response)

        else:
            data_to_post = {
                'type': 'card',
                'number': str(data)
            }
            response = str(postRequest(data_to_post))
            response.encode()

            if(response == 'exist'):
                port.write(response)
            else:
                port.write(response)
    
    if keyboard.is_pressed('q'):
        print('Closed')
        break
