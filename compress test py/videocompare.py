import sys
import cv2

def faceDetect(cap):
    ret, frame = cap.read()
    # newHeight = 360
    # newWidth = int(frame.shape[1] * newHeight / frame.shape[0])
    # frame = cv2.resize(frame, (newWidth, newHeight))
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    face_cascade = cv2.CascadeClassifier(r'./haarcascade_frontalface_default.xml')

    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.15,
        minNeighbors=5,
        minSize=(5, 5),
        flags=cv2.CASCADE_SCALE_IMAGE
    )
    return faces

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    # python videocompare.py luoxiang.mp4 luoxiang50quality.mp4
    capOri = cv2.VideoCapture(sys.argv[1])
    capCom = cv2.VideoCapture(sys.argv[2])
    resolution=int(sys.argv[3])
    frameNum = int(round(capOri.get(cv2.CAP_PROP_FPS)))
    sumOfAreaOri=0
    sumOfAreaOverlap=0
    cnt=0
    iter=min(capOri.get(cv2.CAP_PROP_FRAME_COUNT),capCom.get(cv2.CAP_PROP_FRAME_COUNT))
    while (cnt<iter-1):
        faceOri=faceDetect(capOri)
        faceCom=faceDetect(capCom)
        rectList=[]
        #print("find {} faces".format(len(faces)))
        for (x, y, w, h) in faceOri:
            sumOfAreaOri += w * h
            rectList.append((x,y,w,h))

        for (x2, y2, w2, h2) in faceCom:
            x2 *= (1080 / resolution)
            y2 *= (1080 / resolution)
            w2 *= (1080 / resolution)
            h2 *= (1080 / resolution)
            for (x1,y1,w1,h1) in faceOri:
                if (x2+w2 <= x1 or x1+w1 < x2) and (y2+h2 <= y1 or y1+h1 < y2):
                    continue
                else:
                    width=min(x1+w1,x2+w2) - max(x1,x2)
                    height=min(y1+h1,y2+h2) - max(y1,y2)
                    sumOfAreaOverlap += width*height


        #imageOut = frame.copy()
        #cv2.imshow('frame', imageOut)
        print(cnt,'/',iter)
        cnt+=1
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    capOri.release()
    capCom.release()
    print(sys.argv[2], "correct rate", sumOfAreaOverlap/sumOfAreaOri)
    cv2.destroyAllWindows()

