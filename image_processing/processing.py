import cv2 as cv
import easyocr

def recognition(image_path):
    image = cv.imread(image_path)
    gray_image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)

    #Use Easy OCR to read text
    reader = easyocr.Reader(['en'])
    result = reader.readtext(gray_image)
    print(f'Results: {result}') #Print results

    #Render result
    text = result[0][-2]
    print(f'Serial number: {text}')
    return text