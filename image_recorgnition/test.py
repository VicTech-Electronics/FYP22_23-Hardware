import keyboard
import cv2 as cv
from connection import postRequest
from image_recognition import recognition        

while True:
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

    print(f'Data from the Database: {response}')

    if keyboard.is_pressed('q'):
        print('Closed')
        break
