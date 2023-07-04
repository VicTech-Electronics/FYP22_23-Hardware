from recorgnition import plateNumberRecorgnition
from connection import post
import cv2 as cv
import keyboard
import serial
import os

# serial_port = serial.Serial('COM8', 9600)
camera = cv.VideoCapture(0)

# Load the Image
base_dir = r'V:\Office\Projects\FYP_2022_23\FYP22_23_projects\Hardware\VS code'
defaut_image = base_dir + 'images\images.jpeg'
print(f'Default image path: {defaut_image}')

while True:
    # while serial_port.in_waiting < 1:
    #     data = serial_port.readline()
    #     data = data.decode()

    data = "Detected"
    if data == "Detected":
        # Delete pre existing images if availables
        if os.path.exists(base_dir + f'images\captured_image.jpeg'):
            print('Delete available images')
            os.remove(base_dir + f'images\captured_image.jpeg')

        ret, frame = camera.read()
        if not ret:
            print("Fail to capture Image from the camera")
            print('Lets use the Image from the local disk of the computer')
            full_path = defaut_image
        else:
            image_name = f'images\captured_image.jpeg'
            print('Successfull get image from the Camera')
            cv.imwrite(image_name, frame)
            full_path = base_dir + "\\" + image_name
            print(f'Full path {full_path}')
        
        plate_number_recorgized = plateNumberRecorgnition(full_path)
        # post(plate_number_recorgized)
        break

    if keyboard.is_pressed('q'):
        print('Project is closed')
        break
# serial_port.close()
camera.release()