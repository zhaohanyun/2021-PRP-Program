import cv2
import sys

if __name__ == '__main__':
    if len(sys.argv) < 1:
        print(__doc__)
        sys.exit(1)

    #tracker = cv2.TrackerMedianFlow_create()

    tracker=cv2.TrackerCSRT_create()


    cap = cv2.VideoCapture(sys.argv[1])
    print(int(round(cap.get(cv2.CAP_PROP_FPS))))
    print(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    state=0
    cnt=0
    faces=[]
    while (cap.isOpened()):
        ret, frame = cap.read()
        # newHeight = 480
        # newWidth = int(frame.shape[1] * 480 / frame.shape[0])
        # frame = cv2.resize(frame, (newWidth, newHeight))
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        face_cascade = cv2.CascadeClassifier(r'./haarcascade_frontalface_default.xml')
        #face_cascade = cv2.CascadeClassifier(r'./haarcascade_profileface.xml')

        if cnt==0:
            faces = face_cascade.detectMultiScale(
                gray,
                scaleFactor=1.15,
                minNeighbors=5,
                minSize=(5, 5),
                flags=cv2.CASCADE_SCALE_IMAGE
            )

        #print("find {} faces".format(len(faces)))

            for (x, y, w, h) in faces:
                cv2.rectangle(frame, (x, y), (x + w, y + w), (0, 255, 0), 2)

            if len(faces)==0:
                state=0

        if state==0 and cnt==0:
            if len(faces)==1:
                tracker.init(frame, faces[0])
                state+=1
        else:
            ok, bbox = tracker.update(frame)

            if ok:
                p1 = (int(bbox[0]), int(bbox[1]))
                p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
                cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
        cnt+=1
        if cnt==5:
            cnt=0
        imageOut = frame.copy()
        cv2.imshow('frame', imageOut)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
