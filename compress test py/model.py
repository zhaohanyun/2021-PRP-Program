import numpy as np
import tensorflow as tf
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation, Flatten
from keras.layers import Convolution2D, MaxPooling2D
from keras.utils import np_utils
from tensorflow.keras.optimizers import SGD
from tensorflow.keras.models import Model
import sklearn

class my_model(kera):
def build_model(self, dataset, nb_classes=2) :
    # 构建一个空的网络模型，它是一个线性堆叠模型，各神经网络层会被顺序添加，专业名称为序贯模型或线性堆叠模型
    self.model = Sequential()

    # 以下代码将顺序添加CNN网络需要的各层，一个add就是一个网络层
    self.model.add(Convolution2D(32, 3, 3, border_mode='same',
                                 input_shape=dataset.input_shape))  # 1 2维卷积层
    self.model.add(Activation('relu'))  # 2 激活函数层

    self.model.add(MaxPooling2D(pool_size=(2, 2)))  # 5 池化层
    self.model.add(Dropout(0.25))  # 6 Dropout层

    self.model.add(Convolution2D(64, 3, 3, border_mode='same'))  # 7  2维卷积层
    self.model.add(Activation('relu'))  # 8  激活函数层

    self.model.add(MaxPooling2D(pool_size=(2, 2)))  # 11 池化层
    self.model.add(Dropout(0.25))  # 12 Dropout层

    self.model.add(Flatten())  # 13 Flatten层
    self.model.add(Dense(512))  # 14 Dense层,又被称作全连接层
    self.model.add(Activation('relu'))  # 15 激活函数层
    self.model.add(Dropout(0.5))  # 16 Dropout层
    self.model.add(Dense(nb_classes))  # 17 Dense层
    self.model.add(Activation('softmax'))  # 18 分类层，输出最终结果

    # 输出模型概况
    self.model.summary()

    sgd = SGD(lr=0.01, decay=1e-6,momentum=0.9, nesterov=True)  # 采用SGD+momentum的优化器进行训练，首先生成一个优化器对象

    self.model.compile(loss='categorical_crossentropy',
                           optimizer=sgd,
                           metrics=['accuracy'])  # 完成实际的模型配置工作

    # labels=np.array()
    labels = np.array([0 if label.endswith('zhyPhoto') else 1 for label in labels])

if __name__ == '__main__' :
    batch_size = 32

    train_ds = tf.keras.preprocessing.image_dataset_from_directory(
        "zhyTODO",
        validation_split=0.2,
        subset="training",
        seed=1337,
        image_size=(TODO),
        batch_size=batch_size,
    )

    test_ds = tf.keras.preprocessing.image_dataset_from_directory(
        "zhyTODO",
        validation_split=0.2,
        subset="testing",
        seed=1337,
        image_size=(TODO),
        batch_size=batch_size,
    )

    # for image, label in train_ds:
    # dataset = Dataset('D:\PyCharm-Community\Workplace\Face_Recognition\\face_data')
    # dataset.load()
    model = Model()
    model.build_model(dataset)
    model.train(dataset)
# 此处地址是你保存训练好模型的地址
    model.save_model(file_path='D:\PyCharm-Community\Workplace\Face_Recognition\\face_data\model\jianxin_face_model.h5')
    model.evaluate(dataset)

