from recorgnition import plateNumberRecorgnition
import cv2 as cv
import keyboard
import serial

serial_port = serial.Serial('COM8', 9600)
camera = cv.VideoCapture(0)

# Load the Image
path = r'C:\Users\VicTech Electronics\Desktop\Jupyter notebook\images1.jpeg'

while True:
    while serial_port.in_waiting < 1:
        data = serial_port.readline()
        data = data.decode()
    if data == "Detected":
        ret, frame = camera.read()
        if not ret:
            print("Fail to capture Image from the camera")
            print('Lets use the Image from the local disk of the computer')
            image = cv.imread(path)
        else:
            print('Successfull get image from the Camera')
            image = frame
        
        plate_number = plateNumberRecorgnition(image)


    if keyboard.is_pressed('q'):
        print('Project is closed')
        break
serial_port.close()
camera.release()
camera.destroyAllWindows()