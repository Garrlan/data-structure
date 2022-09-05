# Lab week 02实验报告

姓名：林嘉鸿	学号：19335131



### 内容及目的：

给定一个正整数n的值，找出最小的N，当n>N时，有g(n)>=f(n)

1.n=1, f(n)=n, g(n)=n ln(n)

2.n=1, f(n)=n^10, g(n)=2^n

3.n=2, f(n)=2^n, g(n)=n!

用c完成，包含头文件math.h



### 实验重点：

将f(n), g(n)表示出来，并且通过预先画图了解函数的取值情况，从而简化过程。

1.通过g(n)/f(n)的方法，当算式>=1的情况即满足要求，但是在N的有效范围内，不存在符合情况。

![image-20220906000011891](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220906000011891.png)



2.表示完f，g函数之后，发现这是一个非线性方程（超越方程），所以我使用了二分法逼近N值。并且通过画图可知N<n时，仅有一点相交，问题转换成了求那个点的值。

![image-20220906000909956](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220906000909956.png)



3.n！在头文件math.h没有，所以要自己编写。又因为都是整数，0=<N<2，所以用循环即可解决。

![image-20220906001257887](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220906001257887.png)



### 结果分析：

1.N不存在



2.N= -0.937109

![image-20220906001530177](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220906001530177.png)

3.N=0

