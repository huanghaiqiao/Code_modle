import numpy as np
import tensorflow as tf
# from tensorflow.examples.tutorials.mnist import input_data
# mnist = input_data.read_data_sets('MNIST_data/', one_hot=True)

def train_data(images, labels):
    # 打乱训练数据
    state = np.random.get_state()
    np.random.shuffle(images)
    np.random.set_state(state)
    np.random.shuffle(labels)
    return(images,labels)

def simple_layer(inputs, input_size, output_size):
    """
    封装一层神经网络
    :param inputs: 数据
    :param input_size: 行数
    :param output_size: 列数
    :return: 无
    """
    w = tf.Variable(tf.truncated_normal([input_size,output_size]))
    # w = tf.Variable(tf.random_normal([input_size,output_size]))
    b = tf.Variable(tf.zeros([output_size])+0.1)
    return tf.matmul(inputs,w) + b

def get_every_accuracy(infer_each, truth_each):
    list_rate = []
    for i in range(10):
        # 真实
        each_type_index= np.where(truth_each == i)
        T_N = each_type_index[0].shape[0]

        # 推理
        truth = infer_each[each_type_index]
        P_N = np.where(truth==i)[0].shape[0]   
        list_rate.append(P_N/T_N)
    return list_rate

def load_data(file_path):
    # 加载数据
    train_images = np.load(file_path + "/" + "images.npy")
    train_labels = np.load(file_path + "/" + "labels.npy")
    return(train_images, train_labels)

#参数设置
learning_rate = 0.01   #学习率
train_epochs = 500  #训练轮数
batch_size = 100   #一批数据的大小为100
display_step = 50   #展示的步长


if __name__ == "__main__":
    train_images, train_labels = load_data("55000_train_data")
    test_images, test_labels = load_data("test_data")
    total_batch = train_images.shape[0]//batch_size

    x = tf.placeholder(tf.float32, [None, 784])   #mnist 维度28*28 = 784
    y = tf.placeholder(tf.float32, [None, 10])    #表示0-9个数字的

    #预测层
    pred = tf.nn.softmax(simple_layer(x,784,10))
    #反向传播，将生成的pred与y进行一次交叉熵运算最小化误差cost
    loss = tf.reduce_mean(-tf.reduce_sum(y * tf.log(pred), reduction_indices=1))   #reduce_sum是按列求和
    #梯度下降优化器
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss)

    init = tf.global_variables_initializer()
    with tf.Session() as sess:
        sess.run(init)    #初始化全部的值
        for epoch in range(train_epochs):
            for i in range(total_batch):
                batch_xs, batch_ys = train_images[batch_size*i:batch_size*(i+1)],train_labels[batch_size*i:batch_size*(i+1)]
                sess.run(optimizer,feed_dict={x:batch_xs,y:batch_ys})
                train_loss = sess.run(loss, feed_dict={x:batch_xs, y:batch_ys})
                # train_correct = sess.run(accuracy, feed_dict={x:batch_xs, y:batch_ys})

            if (epoch+1) % display_step == 0:
                m= pred.eval({x:test_images, y:test_labels})
                infer_each = sess.run(tf.argmax(m, 1))
                truth_each = sess.run(tf.argmax(test_labels, 1))
                list_rate = get_every_accuracy(infer_each, truth_each)
                print(list_rate, "=======")

        #测试model
        correct_prediction = tf.equal(tf.argmax(pred, 1), tf.argmax(y, 1))
        #计算准确率
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
        print("测试集准确率:", accuracy.eval({x:test_images, y:test_labels}))
