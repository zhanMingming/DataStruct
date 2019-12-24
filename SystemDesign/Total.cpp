/*

https://segmentfault.com/a/1190000006025876?utm_source=tag-newest

*/

面试题1: 

1. CoreDump  bt调用栈乱序 怎么调试  gcc有参数: -fstack-protector 和 -fstack-protector-all,强烈建议开启.
 手动还原backtrace
手动记录backtrace





2. 怎么监测内存泄漏的情况，如果是内存泄漏比较缓慢，怎么办？

3.一千万个数，如何高效求和

4. 不用数学库，求2开平方的值，精确到小数点儿后10位

-----------------------------

# 1.设计榜单，以及自己的排名

思路：
榜单比如只需要top 1000, 维护一个 top1000 的大堆排序， 当用户积分更新的时候，如果比 排在1000名的积分要多，则将此用户替换 旧的 第1000名， 然后再重新调整顺序
自己的排名， 利用redis中的有序集合， 【 用户ID、 用户分数 】 利用分数排名




# 2. 秒杀系统 

 一个常规的秒杀系统从前到后，依次有：前端浏览器秒杀页面=》中间代理服务=》后端服务层=》数据库层

限流：屏蔽掉无用的流量，允许少部分流量流向后端。

削峰：瞬时大流量峰值容易压垮系统，解决这个问题是重中之重。常用的消峰方法有异步处理、缓存和消息中间件等技术。

异步处理：秒杀系统是一个高并发系统，采用异步处理模式可以极大地提高系统并发量，其实异步处理就是削峰的一种实现方式。

内存缓存：秒杀系统最大的瓶颈一般都是数据库读写，由于数据库读写属于磁盘IO，性能很低，如果能够把部分数据或业务逻辑转移到内存缓存，效率会有极大地提升。

可拓展：当然如果我们想支持更多用户，更大的并发，最好就将系统设计成弹性可拓展的，如果流量来了，拓展机器就好了。像淘宝、京东等双十一活动时会增加大量机器应对交易高峰。

消息队列：消息队列可以削峰，将拦截大量并发请求，这也是一个异步处理过程，后台业务根据自己的处理能力，从消息队列中主动的拉取请求消息进行业务处理。

充分利用缓存：利用缓存可极大提高系统读写速度。 





# 3. 附近的人



# 4. Feed 流系统设计



# 5.  TB级别的文件，统计ip访问次数

分治方法：
将ip 地址转成 32 位 二进制
IP地址一般是一个32位的二进制数意思就是如果将IP地址转换成二进制表示应该有32为那么长，
但是它通常被分割为4个“8位二进制数”（也就是4个字节每，每个代表的就是小于2的8 次方）。
IP地址通常用“点分十进制”表示成（a.b.c.d）的形式，其中，a,b,c,d都是0~255之间的十进制整数。
例：点分十进IP地址（100.4.5.6），实际上是32位二进制数（01100100.00000100.00000101.00000110）

可以按32位中低8位，将文件hash成 2^8 个文件， 保证了相同ip 会被hash 到同一个文件中。


# 6.