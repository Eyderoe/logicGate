# Logic Gate
逻辑门类，能够处理数值变动
## **支持类型**  
> ``单输入`` 3非\
> ``双输入`` 1或 2与 4或非 5与非 6异或 7同或\
> ``四输入`` 8与或非 9与或 10或与 11与非-与非 12或非-或非\
> ``自定义`` 其他类型逻辑门
## **操作**  
>``logicGate (int type, bool pinA=true, ...)`` 类型，初始值\
>``getOutput ()`` 获取输出值\
>``setInput (int pin, bool value)`` 输入值\
>``setInput (int pin, logicGate *frombool, bool isOpposite=false)`` 连接到其他元件的输出\
>``setInput (const int *pinList, logicGate **fromList, const bool *isOppositeList, int num)`` 数组初始化\
>``setInput (int pin, logicGate *from, bool isOpposite, int pin_2, logicGate *from_2, bool isOpposite_2)`` 同时设置两个
