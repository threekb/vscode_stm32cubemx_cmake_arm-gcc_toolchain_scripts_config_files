int _write(int fd, char *pBuffer, int size)
{
    // 避免串口发送过程中的死循环，加入超时机制
    const uint32_t timeout = 100000;  // 超时周期，假设最多等待 100,000 次
    uint32_t timeout_counter = 0;
    
    for (int i = 0; i < size; i++)
    {
        // 等待直到串口的数据寄存器空
        while ((USART1->SR & 0x40) == 0)    //修改成你的串口
        {
            timeout_counter++;
            if (timeout_counter >= timeout)
            {
                // 如果超过超时限制，可以跳出并返回错误，或者做其他处理
                return -1;  // 返回错误
            }
        }
        USART1->DR = (uint8_t) pBuffer[i];  // 写入数据寄存器，发送字符
    }
    
    return size;  // 返回成功发送的字符数量
}


# 使用方法
# 将这个函数放到usart.c文件的用户代码区域中，然后在main.c文件中调用printf函数即可。main.c文件需要包含stdio.h头文件。
