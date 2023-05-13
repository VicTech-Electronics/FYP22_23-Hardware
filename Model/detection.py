import cv2 as cv

# Image file path for testing
smartphones_img_path = 'Images/Smartphones/'
earphones_img_path = 'Images/Earphones/'

# Files path location
model_weights = 'yolo_dnn_model/yolov3.weights'
model_configurations = 'yolo_dnn_model/yolov3.cfg'
model_labels = 'yolo_dnn_model/coco.names'

net = cv.dnn.readNet(model_weights, model_configurations)
model = cv.dnn_DetectionModel(net)
model.setInputParams(
    size=(320, 320),
    scale=1/255,
    # mean=(0, 0, 0),
    # swapRB=True,
    # crop=False                                                                             h
)

label = []
with open(model_labels, 'r') as file:
    for name in file.readlines():
        name = name.strip()
        label.append(name)

image = cv.imread(smartphones_img_path + 'IMG-20230110-WA0079.jpg')
(label_ids, confidences, boxes) = model.detect(image)
for label_id, confidence, box in zip(label_ids, confidences, boxes):
    if label[int(label_id)] == 'cell phone':
        x, y, w, h = box
        _x = x + w
        _y = y + h

        detected_label = label[int(label_id)]
        cv.rectangle(
            img=image,
            pt1=(x, y),
            pt2=(_x, _y),
            color=(0, 255, 0), 
            thickness=1
        )
        cv.putText(
            img=image,
            text=detected_label,
            org=(x, y+3),
            fontFace=cv.FONT_ITALIC,
            fontScale=0.5,
            color=(0, 255, 0),
            thickness=1
        )

cv.imshow('Screen', image)
cv.waitKey(0)
cv.destroyAllWindows()