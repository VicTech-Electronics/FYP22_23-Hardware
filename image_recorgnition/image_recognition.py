import cv2 as cv
import easyocr

def recognition(image_path):
    image = cv.imread(image_path)
    gray_image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)

    #Use Easy OCR to read text
    reader = easyocr.Reader(['en'])
    result = reader.readtext(gray_image)
    print(f'Results: {result}') #Print results

    if not result:
        return 'No plate detected' 
    
    #Render result
    # text = result[0][-2] + ' ' +  result[1][-2]
    text = result[0][-2]
    print(f'Plate number detected: {text}') 
    return text