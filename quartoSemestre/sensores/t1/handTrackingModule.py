import cv2
import mediapipe as mp
from math import sqrt
import keyboard
import mouse

def distance(a, b):
    ed = sqrt((a.x - b.x)**2 + (a.y - b.y)**2)
    return ed

screenx = 1365
screeny = 780

cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils

while True:
    success, image = cap.read()
    h, w, c = image.shape
    print(h, w, "h e w")
    imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(imageRGB)
    scroll = False
    x = 0
    y = 0
    cv2.putText(image, f'Direction: {x}{y}', (40,70), cv2.FONT_HERSHEY_COMPLEX, 1, (0,0,0), 3)

    # checking whether a hand is detected
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks: # working with each hand
            mpDraw.draw_landmarks(image, handLms, mpHands.HAND_CONNECTIONS)
            if(distance(handLms.landmark[8], handLms.landmark[12]) < 0.1
                and distance(handLms.landmark[4], handLms.landmark[14]) < 0.1):
                coordinates = handLms.landmark[8]
                print(coordinates)
                x = screenx * (1-coordinates.x)
                y = screeny*coordinates.y
                mouse.move(x, y)
            else:
                scroll = False


    cv2.imshow("Output", image)
    cv2.waitKey(1)
