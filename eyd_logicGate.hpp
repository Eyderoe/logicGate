#include <iostream>

namespace eyderoe {

const int maxPinInput = 4;

class logicGate
{
    private:
        bool inputValue[maxPinInput]{};
        logicGate *inputClass[maxPinInput]{}; //每个端口输入唯一
        bool inputOpposite[maxPinInput]{false};
        bool output{};
        logicGate **outputList{};   //每个元件输出不唯一
        int outputNum{};
        int outputMax{};
        int type{};

        int setValue (bool value, logicGate *from);
        int fresh ();
        int disconnect (logicGate *to);
        int addOutput (logicGate *to);
    public:
        logicGate (int type, bool pinA, bool pinB, bool pinC, bool pinD);
        bool getOutput () const;
        int setInput (int pin, bool value);
        int setInput (int pin, logicGate *from, bool isOpposite, int pin_2, logicGate *from_2, bool isOpposite_2);
};
logicGate::logicGate (int type, bool pinA = true, bool pinB = true, bool pinC = true, bool pinD = true)
{
    this->type = type;
    inputValue[0] = pinA;
    inputValue[1] = pinB;
    inputValue[2] = pinC;
    inputValue[3] = pinD;
    for (int i = 4 ; i < maxPinInput ; ++i) {
        inputValue[i] = true;
    }
    for (auto &inputClas : inputClass) {
        inputClas = nullptr;
    }
    outputNum = 0;
    outputMax = 2;
    outputList = new logicGate *[outputMax]{nullptr};
    fresh();
}
int logicGate::fresh ()
{
    switch (type) {
        // 0导线 1或 2与 3非 4或非 5与非 6异或 7同或
        case 0:output = inputValue[0];
            break;
        case 1:output = inputValue[0] || inputValue[1];
            break;
        case 2:output = inputValue[0] && inputValue[1];
            break;
        case 3:output = !inputValue[0];
            break;
        case 4:output = !(inputValue[0] || inputValue[1]);
            break;
        case 5:output = !(inputValue[0] && inputValue[1]);
            break;
        case 6:output = inputValue[0] != inputValue[1];
            break;
        case 7:output = inputValue[0] == inputValue[1];
            break;
            // 8与或非 9与或 10或与 11与非-与非 12或非-或非
        case 8:output = !((inputValue[0] && inputValue[1]) || (inputValue[2] && inputValue[3]));
            break;
        case 9:output = (inputValue[0] && inputValue[1]) || (inputValue[2] && inputValue[3]);
            break;
        case 10:output = (inputValue[0] || inputValue[1]) && (inputValue[2] || inputValue[3]);
            break;
        case 11:output = !(!(inputValue[0] && inputValue[1]) && !(inputValue[2] && inputValue[3]));
            break;
        case 12:output = !(!(inputValue[0] || inputValue[1]) || !(inputValue[2] || inputValue[3]));
            break;
    }
    for (int i = 0 ; i < outputNum ; ++i) {
        outputList[i]->setValue(output, this);
        outputList[i]->fresh();
    }
    return 0;
}
int logicGate::setValue (bool value, logicGate *from)
{
    for (int i = 0 ; i < maxPinInput ; ++i) {
        if (inputClass[i] == from) {
            // inputValue[i] = !(inputOpposite[i]) ? value : !value;
            inputValue[i] = !(inputOpposite[i]) == value;
            break;
        }
    }
    return 0;
}
bool logicGate::getOutput () const
{
    return output;
}
int logicGate::disconnect (logicGate *to)
{
    for (int i = 0 ; i < outputNum ; ++i) {
        if (outputList[i] == to) {
            for (int j = i ; j < outputNum - 1 ; ++j) {
                outputList[j] = outputList[j + 1];
            }
            break;
        }
    }
    outputNum -= 1;
    outputList[outputNum] = nullptr;
    return 0;
}
int logicGate::setInput (int pin, bool value)
{
    inputValue[pin - 1] = value;
    if (inputClass[pin - 1] != nullptr) {
        inputClass[pin - 1]->disconnect(this);
        inputClass[pin - 1] = nullptr;
    }
    fresh();
    return 0;
}
int logicGate::setInput (int pin, logicGate *from, bool isOpposite = false, \
                        int pin_2 = -1, logicGate *from_2 = nullptr, bool isOpposite_2 = false)
{
    inputValue[pin - 1] = !isOpposite ? from->output : -(from->output);
    inputOpposite[pin - 1] = isOpposite;
    if (inputClass[pin - 1] != nullptr) {
        inputClass[pin - 1]->disconnect(this);
        inputClass[pin - 1] = nullptr;
    }
    inputClass[pin - 1] = from;
    from->addOutput(this);
    fresh();
    if (pin_2 != -1) {
        inputValue[pin_2 - 1] = !isOpposite_2 ? from_2->output : -(from_2->output);
        inputOpposite[pin_2 - 1] = isOpposite_2;
        if (inputClass[pin_2 - 1] != nullptr) {
            inputClass[pin_2 - 1]->disconnect(this);
            inputClass[pin_2 - 1] = nullptr;
        }
        inputClass[pin_2 - 1] = from_2;
        from_2->addOutput(this);
        fresh();
        return 0;
    }
    return 0;
}
int logicGate::addOutput (logicGate *to)
{
    logicGate * *newList = nullptr;
    if (to->outputNum == to->outputMax) {
        newList = new logicGate *[outputMax + 2];
        for (int i = 0 ; i < outputNum ; ++i) {
            newList[i] = outputList[i];
        }
        delete[] outputList;
        outputList = newList;
        newList = nullptr;
        outputMax += 2;
    }
    outputList[outputNum] = to;
    outputNum += 1;
    return 0;
}

int truthTable(logicGate * *input, int
inputNum,
logicGate *output
) {
int caseNum = 1, caseNum_copy, base;  // 排列组合方式，最大表示的数为case-1，base每次输入端表示的数
for (
int i = 0;
i<inputNum;
++i) {
caseNum *= 2;
}
caseNum_copy = caseNum;
bool *inputList;
inputList = new bool[inputNum];

for (
int i = 0;
i<caseNum;
++i) {
caseNum_copy = i;   // 输入端表示的值
for (
int j = 0;
j<inputNum;
++j) {  // 求二进制
inputList[inputNum - 1 - j] =
bool(caseNum_copy
&1);
caseNum_copy >>= 1;
}
for (
int j = 0;
j<inputNum;
++j) {
std::cout << inputList[j];
}
std::cout << " | ";
for (
int j = 0;
j<inputNum;
++j)    // 设置值
(*(input + j))->setInput(1, inputList[j]);
std::cout << output->
getOutput ()
<<
std::endl;
}
return 0;
}

}
