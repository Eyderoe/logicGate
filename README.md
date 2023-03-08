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
>``setInput (int pin, logicGate *from, bool isOpposite, int pin_2, logicGate *from_2, bool isOpposite_2)`` 同时设置两个
## **示例**
eyderoe::logicGate a(0), b(0), c(0), d(5), e(5), f(5), g(5);\
eyderoe::logicGate * list[3]{&a, &b, &c};\
d.setInput(1,&a, true,2,&b, true);\
e.setInput(1,&a, false,2,&b, false);\
f.setInput(1,&e, false,2,&c, true);\
g.setInput(1,&d, false,2,&f, false);\
std::cout << "ABC | P" << std::endl;\
eyderoe::truthTable(list,3,&g);
