/**
 * @file      : main.c
 * @brief     : 程序入口文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-04 15:26:26
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-04 huenrong        创建文件
 *
 */

#include <stdio.h>

#include "./linux_serial/serial.h"

/**
 * @brief  发送, 接收数据测试
 * @param  serial_name: 输入参数, 串口名
 * @return 成功: 0
 *         失败: -1
 */
int send_and_recv_data_test(const char *serial_name)
{
    int ret = -1;
    uint8_t send_data[] = {0xAA, 0x01, 0x03, 0x11, 0x22, 0x33, 0xA8};
    uint32_t send_data_len = 7;
    uint8_t recv_data[10] = {0};

    // 打印发送数据
    printf("serial %s write data[len = %d]: ", serial_name, send_data_len);
    for (uint8_t i = 0; i < send_data_len; i++)
    {
        printf("0x%02X ", send_data[i]);
    }
    printf("\n");

    // 串口发送数据
    ret = serial_write_data(serial_name, send_data, send_data_len);
    if (ret < 0)
    {
        printf("serial %s send data fail\n", serial_name);

        // 关闭串口
        serial_close(serial_name);

        return -1;
    }

    // 清空输入, 输出缓存
    if (!serial_flush_both_cache(serial_name))
    {
        printf("serial %s flush both data fail\n", serial_name);

        // 关闭串口
        serial_close(serial_name);

        return -1;
    }

    // 串口接收数据
    ret = serial_read_data(recv_data, serial_name, send_data_len, 1000);
    if (ret > 0)
    {
        printf("serial %s read data[len = %d]: ", serial_name, ret);
        for (uint8_t i = 0; i < ret; i++)
        {
            printf("0x%02X ", recv_data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("serial %s recv data fail\n", serial_name);

        // 关闭串口
        serial_close(serial_name);

        return -1;
    }

    return 0;
}

/**
 * @brief  : 程序入口
 * @param  : argc: 输入参数, 参数个数
 * @param  : argv: 输入参数, 参数列表
 * @return : 成功: 0
 *           失败: 其它
 */
int main(int argc, char *argv[])
{
    const char *serial_name_0 = "/dev/ttyS0";
    const char *serial_name_1 = "/dev/ttyUSB0";

    if (!serial_open(serial_name_0, E_SERIAL_BAUD_RATE_115200, 0, E_SERIAL_DATA_BIT_8, E_SERIAL_PARITY_BIT_N,
                     E_SERIAL_STOP_BIT_1))
    {
        printf("open %s fail\n", serial_name_0);

        return -1;
    }

    if (!serial_open(serial_name_1, E_SERIAL_BAUD_RATE_115200, 0, E_SERIAL_DATA_BIT_8, E_SERIAL_PARITY_BIT_N,
                     E_SERIAL_STOP_BIT_1))
    {
        printf("open %s fail\n", serial_name_1);

        return -1;
    }

    send_and_recv_data_test(serial_name_0);
    printf("\n******************************************************\n");

    send_and_recv_data_test(serial_name_1);
    printf("\n******************************************************\n");

    serial_close(serial_name_0);
    printf("close serial %s\n", serial_name_0);

    serial_close(serial_name_1);
    printf("close serial %s\n", serial_name_1);

    return 0;
}
