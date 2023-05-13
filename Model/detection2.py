import cv2 as cv

# frame file path for testing
smartphones_img_path = 'frames/Smartphones/'
earphones_img_path = 'frames/Earphones/'

# Files path location
model_weights = 'yolo_dnn_model/yolov3.weights'
model_configurations = 'yolo_dnn_model/yolov3.cfg'
model_labels = 'yolo_dnn_model/coco.names'

net = cv.dnn.readNet(model_weights, model_configurations)
model = cv.dnn_DetectionModel(net)
model.setInputParams(
    size=(320, 320),
    scale=1/255,
)

label = []
with open(model_labels, 'r') as file:
    for name in file.readlines():
        name = name.strip()
        label.append(name)


cap = cv.VideoCapture(0)
while True:
    is_captured, frame = cap.read()
    if is_captured is None:
        break

    (label_ids, confidences, boxes) = model.detect(frame)
    for label_id, confidence, box in zip(label_ids, confidences, boxes):
        if label[int(label_id)] == 'cell phone':
            x, y, w, h = box
            detected_label = label[int(label_id)]
            cv.rectangle(
                img=frame,
                pt1=(x, y),
                pt2=(x+w, y+h),
                color=(0, 255, 0), 
                thickness=1
            )
            cv.putText(
                img=frame,
                text=detected_label,
                org=(x, y-3),
                fontFace=cv.FONT_ITALIC,
                fontScale=0.5,
                color=(0, 255, 0),
                thickness=1
            )
    
    cv.imshow('Screen', frame)