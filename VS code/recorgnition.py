import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np
import easyocr
import imutils

# Load the Image
image = cv.imread(r'C:\Users\VicTech Electronics\Desktop\Milcah Project Notebook\images.jpeg')
gray_image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
# plt.show(cv.cvtColor(gray_image, cv.COLOR_BGR2RGB)) # show the image

# Detect edges from the Image
bfilter = cv.bilateralFilter(gray_image, 11, 17, 17) #Noise reduction
edged = cv.Canny(bfilter, 30, 200)  # Edge detection
# plt.imshow(cv.cvtColor(edged, cv.COLOR_BGR2RGB)) 

# Find contours and Apply Mask
# Contours
keyPoints = cv.findContours(edged.copy(), cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
contours = imutils.grab_contours(keyPoints)
contours = sorted(contours, key=cv.contourArea, reverse=True)[:10]
# contours # Print contours

location = None
for contour in contours:
    approx = cv.approxPolyDP(contour, 10, True)
    if len(approx) == 4:
        location = approx
        break

# Mask
mask = np.zeros(gray_image.shape, np.uint8)
new_image = cv.drawContours(mask, [location], 0, 255, -1)
new_image =cv.bitwise_and(image, image, mask=mask)
# plt.imshow(cv.cvtColor(new_image, cv.COLOR_BGR2RGB))

# Crop the Image
(x, y) = np.where(mask==255)
(x1, y1) = (np.min(x), np.min(y))
(x2, y2) = (np.max(x), np.max(y))
cropped_image = gray_image[x1:x2+1, y1:y2+1]
# plt.imshow(cv.cvtColor(cropped_image, cv.COLOR_BGR2RGB))

#Use Easy OCR to read text
reader = easyocr.Reader(['en'])
result = reader.readtext(reader)
result #Print results

#Render result
text = result[0][-2]
font = cv.FONT_HERSHEY_SCRIPT_SIMPLEX
res = cv.putText(image, text=text, org=(approx[0][0][0], approx[1][0][1]+60), fontFace=font, fontScale=1, color=(0, 255, 0), thickness=2, lineType=cv.LINE_AA)
res = cv.rectangle(image, tuple(approx[0][0], approx[2][0]), (0, 255, 0), 3)
# plt.imshow(cv.cvtColor(res, cv.COLOR_BGR2RGB))

print(f'Plate number: {text}')