import cv2
import mediapipe as mp
from math import sqrt
import keyboard
import mouse
import configparser
import time



# while True:
#     success, image = cap.read()
#     h, w, c = image.shape
#     imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
#     results = hands.process(imageRGB)
#     tolerance = 0.25
#     start = time.time()
#     # checking whether a hand is detected
#     if results.multi_hand_landmarks:
#         for handLms in results.multi_hand_landmarks: # working with each hand
#             self.mpDraw.draw_landmarks(image, handLms, self.mpHands.HAND_CONNECTIONS)
#             c = distance(handLms.landmark[0], handLms.landmark[9], 1)
#             pinch = pinchVerification(handLms)
#             highFive = highFiveVerification(handLms)
#             ok = okVerification(handLms)
#             if(pinch):
#                 print("to aqui")
#                 coordinates = handLms.landmark[8]
#                 x = screenx * (1-coordinates.x)
#                 y = screeny*coordinates.y
#                 mouse.move(x, y, absolute=True)
#                 # print(x, y)
#                 gesture = "pinch"

#             if(highFive and gesture != "high five"):
#                 if(not counting):
#                     now = time.time()
#                     counting = True
#                 if(counting and start - now > 0.2):
#                     gesture = "high five"
#                     mouse.click()
#                     print("click!")
#                     counting = False
                    
#             if(ok and gesture != "ok"):
#                 if(not counting):
#                     now = time.time()
#                     counting = True
#                 if(counting and start - now > 0.2):
#                     gesture = "ok"
#                     counting = False
#             if(not pinch and not highFive and not ok):
#                 gesture = "none"
        
#     cv2.putText(image, gesture, (7, 70), cv2.FONT_HERSHEY_SIMPLEX, 3, (100, 255, 0), 3, cv2.LINE_AA)
#     cv2.imshow("Output", image)
#     cv2.waitKey(1)

def distance(a, b, distance_coef):
    ed = sqrt((a.x - b.x)**2 + (a.y - b.y)**2)
    ed /= distance_coef
    return ed

class HandTracking:
    def __init__(self, config_file):
        config = configparser.ConfigParser()
        config.read(config_file)

        self.screenx = int(config['var']['screenx'])
        self.screeny = int(config['var']['screeny'])
        camera = int(config['var']['camera'])

        self.cap = cv2.VideoCapture(camera)
        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands()
        self.mpDraw = mp.solutions.drawing_utils

        self.gesture = "none"
        self.counting = False
        self.tolerance = 0.25

    

    def pinchVerification(self, handLms, distance_coef):
        return (distance(handLms.landmark[8], handLms.landmark[12], distance_coef) < self.tolerance
                and distance(handLms.landmark[4], handLms.landmark[14], distance_coef) < 2*self.tolerance
                and distance(handLms.landmark[8], handLms.landmark[14], distance_coef) > self.tolerance*3)

    def middleFingerVerification(self, handLms, distance_coef):
        return (distance(handLms.landmark[8], handLms.landmark[12], distance_coef) > self.tolerance*3
                and distance(handLms.landmark[4], handLms.landmark[14], distance_coef) < self.tolerance)

    def highFiveVerification(self, handLms, distance_coef):
        return (distance(handLms.landmark[8], handLms.landmark[12], distance_coef) < self.tolerance*3
                and distance(handLms.landmark[12], handLms.landmark[16], distance_coef) < self.tolerance*3
                and distance(handLms.landmark[16], handLms.landmark[20], distance_coef) < self.tolerance*3
                and distance(handLms.landmark[12], handLms.landmark[0], distance_coef) > self.tolerance*5)

    def okVerification(self, handLms, distance_coef):
        return (distance(handLms.landmark[8], handLms.landmark[6], distance_coef) < self.tolerance*2
                and distance(handLms.landmark[12], handLms.landmark[10], distance_coef) < self.tolerance*2
                and distance(handLms.landmark[16], handLms.landmark[14], distance_coef) < self.tolerance*2
                and distance(handLms.landmark[17], handLms.landmark[4], distance_coef) > self.tolerance*5)

    def main_loop(self, show_video=True):
        while True:
            success, image = self.cap.read()
            h, w, c = image.shape
            imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            results = self.hands.process(imageRGB)
            start = time.time()
            # checking whether a hand is detected
            if results.multi_hand_landmarks:
                for handLms in results.multi_hand_landmarks: # working with each hand
                    self.mpDraw.draw_landmarks(image, handLms, self.mpHands.HAND_CONNECTIONS)
                    distance_coef = distance(handLms.landmark[0], handLms.landmark[9], 1)
                    pinch = self.pinchVerification(handLms, distance_coef)
                    highFive = self.highFiveVerification(handLms, distance_coef)
                    ok = self.okVerification(handLms, distance_coef)
                    if(pinch):
                        print("to aqui")
                        coordinates = handLms.landmark[8]
                        x = screenx * (1-coordinates.x)
                        y = screeny*coordinates.y
                        mouse.move(x, y, absolute=True)
                        # print(x, y)
                        gesture = "pinch"

                    if(highFive and gesture != "high five"):
                        if(not counting):
                            now = time.time()
                            counting = True
                        if(counting and start - now > 0.2):
                            gesture = "high five"
                            mouse.click()
                            print("click!")
                            counting = False
                            
                    if(ok and gesture != "ok"):
                        if(not counting):
                            now = time.time()
                            counting = True
                        if(counting and start - now > 0.2):
                            gesture = "ok"
                            counting = False
                    if(not pinch and not highFive and not ok):
                        gesture = "none"
            
            if(show_video): 
                self.show_image(image)   
            

    def show_image(self, image):
        cv2.putText(image, self.gesture, (7, 70), cv2.FONT_HERSHEY_SIMPLEX, 3, (100, 255, 0), 3, cv2.LINE_AA)
        cv2.imshow("Output", image)
        cv2.waitKey(1)


def main():
    loop = HandTracking("config.ini")
    loop.main_loop()

main()