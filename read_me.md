二分查找法
----------
### 存放路径：dichotomous_ search _visitor _mode文件夹中

### 函数定义：

    int8_t dichotomous_search(void *arr, uint32_t data_type_len, uint32_t data_len, void *target, 
      int8_t(*compare_func)(void *member_1, void *member_2), uint32_t *num) 

     *Brief :二分查找法
     *detail :
     *
     *param[in] :float *arr： 以相反的顺序排序数组
     *param[in] :uint32_t data_type_len： 数据的数量
     *param[in] :uint32_t data_len：输入数组的长度
     *param[in] :void *target： 指向目标值。
     *param[in] :int8_t(*compare_func)(void *member_1, void *member_2) :确定数组的顺序（正序/倒序）。
     *param[out] :uint32_t *num: 指向索引
     *
     *\retval :uint8_t status：
     *-1表示得到空数组   
     *-2目标值越界
     *1表示得到有效的数组

### 使用说明：
![](file:///C:/Users/dgbuaa/Desktop/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202022-07-29%20163849.png)
#### 当目标值在所寻找的数组中没有存在，则返回一个离目标值最近的左边的下标值。
#### 在函数的第二个入口参数里自定义数据类型，比如sizeof（double）

	#include "stdint.h"
	#include "stdio.h"

	int8_t g_status;
	uint32_t p_data;
	double arr[5] = {5,4,3,2,1};
	double res_value = 2;

	int main()
	{
	    g_status = dichotomous_search(arr, sizeof(double), 5, &res_value, float_compare_func ,&p_data);
	    printf("p_data:%d\n", p_data);
	    printf("g_status:%d\n", g_status);
	    return 0;
	
	}
### 输出下标值为：

#### p_data:3

#### g_status:1


