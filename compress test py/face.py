import cv2

if __name__ == '__main__':
   image = cv2.imread('keru.jpg')
   #cv2.imshow('input', image)
   newHeight = 480
   newWidth = int(image.shape[1] * 480 / image.shape[0])
   image = cv2.resize(image, (newWidth, newHeight))

   gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

   face_cascade = cv2.CascadeClassifier(r'./haarcascade_frontalface_default.xml')

   faces = face_cascade.detectMultiScale(
      gray,
      scaleFactor = 1.15,
      minNeighbors = 5,
      minSize = (5,5),
      flags = cv2.CASCADE_SCALE_IMAGE
   )
   print("find {} faces".format(len(faces)))
   while True:
      for(x,y,w,h) in faces:
         cv2.rectangle(image,(x,y),(x+w,y+w),(0,255,0),2)

      imageOut = image.copy()
      cv2.imshow("Output", imageOut)

      # record key press
      k = cv2.waitKey(0) & 0xFF

      # q is pressed
      if k == 113:
         break

   cv2.destroyAllWindows()
