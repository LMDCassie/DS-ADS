# input #
## data.txt ##

数据来源：http://www.dis.uniroma1.it/challenge9/download.shtml.

请将待输入的数据文件命名为data.txt，放置于该程序所在文件夹中,数据格式遵照9th DIMACS数据定义

    c comment
    p sp nodeNum edgeNum
    a i j distance
    ...
## test.txt  ##
请将查询的数据文件命名为test.txt, 放置于该程序所在文件夹中，数据格式如下

    query //查询次数
    i j //shortest path from i to j
    ...

# output #
最短路径结果分别输出为minResult.txt与fibResult.txt。
运行时间也会同时在屏幕显示

## minResult.txt ##
输出用minHeap实现的最短路径，格式如下

    i:v1 to v2:dis //i-第i次查询，dis-v1到v2的最短路径
    ...
    time ms //time-运行时间的毫秒数

## fibResult.txt ##
输出用fibHeap实现的最短路径，格式如下

    i:v1 to v2:dis //i-第i次查询，dis-v1到v2的最短路径
    ...
    time ms //time-运行时间的毫秒数