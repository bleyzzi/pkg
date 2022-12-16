import numpy as np
import cv2 as cv
import imutils
from tkinter import ttk
from tkinter import *
from scipy import ndimage as ndi
from skimage.filters import edges
from skimage.feature import peak_local_max
from skimage.segmentation import watershed
from PIL import ImageTk, Image
from copy import deepcopy

class MainSolution():
    def __init__(self):
        self.image = cv.imread("coins.jpg")
        self.imgray = None
        self.trsh1 = None
        self.trsh2 = None

    def filt(self):
        self.imgray = cv.cvtColor(cv.pyrMeanShiftFiltering(
            self.image, 15, 50), cv.COLOR_BGR2GRAY)
        img = Image.fromarray(self.imgray)
        img = img.resize((300, 300))
        return ImageTk.PhotoImage(img)

    def global_threshold(self):
      ret, thresh1 = cv.threshold(self.imgray, 0, 255, cv.THRESH_BINARY_INV | cv.THRESH_OTSU)
      self.trsh1 = deepcopy(thresh1)
      img = Image.fromarray(thresh1)
      img = img.resize((300, 300))
      return ImageTk.PhotoImage(img)

    def adaptive_threshold(self):
      thresh2 = cv.adaptiveThreshold(self.imgray, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 11, 2)
      self.trsh2 = deepcopy(thresh2)
      img = Image.fromarray(thresh2)
      img = img.resize((300, 300))
      return ImageTk.PhotoImage(img)
    
    def segmentation(self):
      dist = ndi.distance_transform_edt(self.trsh1)
      local_max = peak_local_max(dist, indices=False, min_distance=20, labels=self.trsh1)
      markers = ndi.label(local_max, structure=np.ones((3, 3)))[0]
      labels = watershed(-dist, markers, mask=self.trsh1)
      for label in np.unique(labels):
        if label == 0:
          continue
        mask = np.zeros(self.imgray.shape, dtype="uint8")
        mask[labels == label] = 255
        contours = cv.findContours(mask.copy(), cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
        contours = imutils.grab_contours(contours)
        c = max(contours, key=cv.contourArea)

        ((x, y), r) = cv.minEnclosingCircle(c)
        cv.circle(self.image, (int(x), int(y)), int(r), (255, 0, 0), 7)

      self.image = Image.fromarray(self.image)
      self.image = self.image.resize((300, 300))
      return ImageTk.PhotoImage(self.image)

if __name__ == "__main__":
    root = Tk()
    ms = MainSolution()
    w, h = root.winfo_screenwidth(), root.winfo_screenheight()
    root.geometry(f"700x700")
    lbl_text1 = ttk.Label(text="Глобальная пороговая обработка")
    lbl_text1.place(x=250, y=10)
    img1 = ms.filt()
    lbl1 = ttk.Label(image=img1)
    lbl1.image = img1
    lbl1.place(x=30, y=40, width=300, height=300)
    img2 = ms.global_threshold()
    lbl2 = ttk.Label(image=img2)
    lbl2.image = img2
    lbl2.place(x=370, y=40, width=300, height=300)
    lbl_text2 = ttk.Label(text="Адаптивная пороговая обработка")
    lbl_text2.place(x=90, y=360)
    img3 = ms.adaptive_threshold()
    lbl3 = ttk.Label(image=img3)
    lbl3.image = img3
    lbl3.place(x=30, y=390, width=300, height=300)
    lbl_text3 = ttk.Label(text="Сегментация")
    lbl_text3.place(x=480, y=360)
    img4 = ms.segmentation()
    lbl4 = ttk.Label(image=img4)
    lbl4.image = img4
    lbl4.place(x=370, y=390, width=300, height=300)
    root.mainloop()
