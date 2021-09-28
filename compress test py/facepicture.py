import sys
import cv2

if __name__ == '__main__':
    if len(sys.argv) < 1:
        print(__doc__)
        sys.exit(1)

    frame =cv2.imread(sys.argv[1])
    #print(int(round(cap.get(cv2.CAP_PROP_FPS))))
    #print(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    #while (cap.isOpened()):
    if(True):
        #ret, frame = cap.read()
        newHeight = 720
        newWidth = int(frame.shape[1] * 720 / frame.shape[0])
        frame = cv2.resize(frame, (newWidth, newHeight))
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        face_cascade = cv2.CascadeClassifier(r'./haarcascade_frontalface_default.xml')
        #face_cascade = cv2.CascadeClassifier(r'./haarcascade_profileface.xml')

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

        imageOut = frame.copy()


        cv2.imshow('frame', imageOut)
        cv2.waitKey(100000)
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break

    #cap.release()
    cv2.destroyAllWindows()
