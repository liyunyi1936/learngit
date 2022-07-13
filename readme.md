##环境依赖

+ Keil v5.23

+ STM32cubeMX6.1.2

##主控芯片

STM32F427 VIT6


##目录结构描述

* [doc]()
  * [databook]()
  * [schematic]()
* [src]()
  * [adc_data ]()
  * [dichotomous_search]()   
  * [get_ real _temp _value]() 
* [template]()
* [.gitignore]()
* [readme]()


##功能概述
###- ADC采样转换得到两种NTC的阻值，利用二分查找法获取不同阻值对应的温度值
###- IO口对应说明
PC4   ---  ADC1 IN14   

PD4   ---  ADC_MUX _A0 （GPIO _OUTPUT）

PD5   ---  ADC_MUX _A1

PD6   ---  ADC_MUX _A2

PD7   ---  ADC_MUX _EN

##V2.0.0 版本内容更新

#####1.与二分查找法直接相关的自定义源文件（.c.h）放在	src文件夹中, 更改了存放的文件夹的位置, 按照功能分类整理

#####2. ``dichotomous_search.c`` 中改动：

+ 判0：对入口参数进行有效性判断，``dichotomous_search`` 此函数返回值从下标值更改为状态  `` uint8_t  status``。

+ 数据类型：size / target/ *num均更改为 ``uint32_t `` ，避免过大的数组传入造成数据溢出。
。
+ break：只保留一个返回值，在条件符合`` target == arr[mid]`` 跳出循环。

#####3. ``ntc_table.c`` 中改动：

+ 温度的数组不列出，在计算最终的温度值时公式改动为
 ``*real_Temp = -70 + subs * 0.05f + ((resist_arr[subs] - value) / (resist_arr[subs] - resist_arr[subs + 1]) * 0.05f);  ``

#####4. ``get_ real_temp_value.c`` 中改动：

+ 修复bug： ``search_and_get_value``  函数在执行过程中， ``dichotomous_search(arr, ARRAY_NUM(arr), target_value, &num)``，无法返回正确的电阻阻值数组的下标值，导致后面的计算 ``temp``  的数值不正确，原因是 “数组作为函数参数会退化为指针”。
（Refer to [https://blog.csdn.net/weixin_43737395/article/details/123233550](https://blog.csdn.net/weixin_43737395/article/details/123233550) ）
  
+  solve：在  ``search_and_get_value``  函数的入口参数新增  ``uint16 len``, 手动输入数组长度