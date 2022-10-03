import cv2
import mediapipe as mp
from math import sqrt
import keyboard

def distance(a, b):
    ed = sqrt((a.x - b.x)**2 + (a.y - b.y)**2)
    return ed

cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils

while True:
    success, image = cap.read()
    h, w, c = image.shape
    imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(imageRGB)
    scroll = False
    direction = 0
    cv2.putText(image, f'Direction: {int(direction*1000)}', (40,70), cv2.FONT_HERSHEY_COMPLEX, 1, (0,0,0), 3)

    # checking whether a hand is detected
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks: # working with each hand
            mpDraw.draw_landmarks(image, handLms, mpHands.HAND_CONNECTIONS)
            if(distance(handLms.landmark[8], handLms.landmark[12]) < 0.1
                and distance(handLms.landmark[4], handLms.landmark[14])):
                print("to aq")
                if(not scroll):
                    old_y = handLms.landmark[8].y
                    scroll = True
                    command = "No Command"

                else:
                    direction = (handLms.landmark[8].y - old_y) 
                    
                    if(direction > 0):
                        keyboard.send('page up')
                        command = "Page Up"
                    else:
                        keyboard.send('page down')
                        command = "Page Down"
                    old_y = handLms.landmark[8].y
                    scroll = False
            else:
                print("uai")
                scroll = False


    cv2.imshow("Output", image)
    cv2.waitKey(1)
