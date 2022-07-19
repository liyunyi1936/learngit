## 环境依赖

+ Keil v5.23

+ STM32cubeMX6.1.2

## 主控芯片

STM32F427 VIT6


## 目录结构描述

* [doc]()
  * [databook]()
  * [schematic]()
* [src]()
  * [adc_data ]()
  * [dichotomous_search]()   
  * [get_ real _temp _value]() 
  * [ntc_table]() 
* [template]()
* [.gitignore]()
* [readme]()


## 功能概述

### - ADC采样转换得到两种NTC的阻值，利用二分查找法获取不同阻值对应的温度值

### - IO口对应说明

PC4   ---  ADC1 IN14   

PD4   ---  ADC_MUX _A0 （GPIO _OUTPUT）

PD5   ---  ADC_MUX _A1

PD6   ---  ADC_MUX _A2

PD7   ---  ADC_MUX _EN

## V2.0.0 版本内容更新

##### 1.与二分查找法直接相关的自定义源文件（.c.h）放在	src文件夹中, 更改了存放的文件夹的位置, 按照功能分类整理

##### 2. ``dichotomous_search.c`` 中改动：

+ 判0：对入口参数进行有效性判断，``dichotomous_search`` 此函数返回值从下标值更改为状态  `` uint8_t  status``。

+ 数据类型：size / target/ *num均更改为 ``uint32_t `` ，避免过大的数组传入造成数据溢出。
。
+ break：只保留一个返回值，在条件符合`` target == arr[mid]`` 跳出循环。

##### 3. ``ntc_table.c`` 中改动：

+ 温度的数组不列出，在计算最终的温度值时公式改动为
 ``*real_Temp = -70 + subs * 0.05f + ((resist_arr[subs] - value) / (resist_arr[subs] - resist_arr[subs + 1]) * 0.05f);  ``

##### 4. ``get_ real_temp_value.c`` 中改动：

+ 修复bug： ``search_and_get_value``  函数在执行过程中， ``dichotomous_search(arr, ARRAY_NUM(arr), target_value, &num)``，无法返回正确的电阻阻值数组的下标值，导致后面的计算 ``temp``  的数值不正确，原因是 “数组作为函数参数会退化为指针”。
（Refer to [https://blog.csdn.net/weixin_43737395/article/details/123233550](https://blog.csdn.net/weixin_43737395/article/details/123233550) ）
  
+  solve：在  ``search_and_get_value``  函数的入口参数新增  ``uint16 len``, 手动输入数组长度

## V2.0.1 版本内容更新

##### 1.布局上：

 - 新建 ``ntc_table`` 文件夹存放.c.h文件。

##### 2.书写规范上：

 - 去除了Dichotomous_search.c中stdio.h头文件，将系统的标准库用 include < XXX > 区分系统头文件。 
 - tap 和 space 替换


##### 3.内容修改上：

 +  **DRY原则**：  
 
<1> 在 adc_ data.c 文件中自定义了 ``resist_ val_ cal `` 函数, 调用此函数来计算各通道的阻值，减少重复计算。（ps：只有6个通道有相关计算阻值的公式）。

<2> 在 adc_ data.c 文件中 ``mux_get_ADC_channel_data`` 函数中，第一个switch计算各通道阻值，第二个switch是用作切换通道的，将切换通道的内容放到计算阻值后面，之后break，能实现正常运行，减少重复写switch结构。

（ps：尝试用while循环判断（* chan）少于 ``MUX_CHANNEL_8`` ,然后（* chan）++自加,直至 ``* chan = MUX_CHANNEL_8`` 时让 ``*chan = MUX_CHANNEL_1`` ,debug调试时发现会chan从0跳到7，阻值和温度数据没有更新，且代码运行之后在返0（通道1）的判断处加断点，能够实现chan枚举01234567，但是计算阻值没有更新）


 + **修复bug**： 在 adc_ data.c 文件中 search_ and_ get_ value 函数中的4400（此数值有误，后确定为4401）用 ``j2_form_value_num``替换，此变量定义在 `` ntc_table.c `` 的    ``uint32_t  j2_form_value_num = ARRAY_NUM(j2_form_value);`` 

 +  **中值滤波** ：？
 

​