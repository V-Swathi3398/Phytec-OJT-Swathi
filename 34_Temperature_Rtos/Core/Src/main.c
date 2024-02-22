#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define AHT25_ADDRESS 0x38
#define UART_TX_BUFFER_SIZE 100

float temperature;
int ch;

UART_HandleTypeDef huart2;
void TemperatureTask(void *pvParameters);

void SystemClock_Config(void);
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t data);
uint8_t I2C_ReceiveByte(void);
void AHT25_SendCommand(uint8_t command);
void AHT25_ReadData(uint8_t* data, uint8_t length);
float AHT25_ConvertTemperature(uint8_t* data);

TaskHandle_t temperature_task_handle;

void UART_Init(void)
{
    RCC->AHB1ENR |= 1;   // Enable GPIOA clock
    RCC->APB1ENR |= 0x20000;  // Enable USART2 clock

    // Configure PA2 for USART2_TX
    GPIOA->AFR[0] &= ~0x0F00;     // Clear alternate function bits
    GPIOA->AFR[0] |= 0x0700; // Set alternate function 7 for USART2_TX

    GPIOA->MODER &= ~0x0030;     // Clear mode bits
    GPIOA->MODER |= 0x0020;    // Set alternate function mode for PA2

    USART2->BRR = 0x0683;                  // 9600 baud @ 16 MHz
    USART2->CR1 = 0x0008;            // Enable transmitter
    USART2->CR2 = 0x0000;                  // 1 stop bit
    USART2->CR3 = 0x0000;                  // No flow control
    USART2->CR1 |= 0x2000;           // Enable USART2
}

void UART_TransmitString(const char* str)
{
    for (uint32_t i = 0; i < strlen(str); i++)
    {
        // Wait until UART2 transmit buffer is empty
        while (!(USART2->SR & 0x0080));

        // Write the character to the UART2 data register
        USART2->DR = (str[i] & 0xFF);
    }
}

void UART_TransmitFloat(float value)
{
    char buffer[UART_TX_BUFFER_SIZE];

    // Convert the floating-point value to a string
    sprintf(buffer, "%.2f", value);

    // Transmit the string over UART2
    UART_TransmitString(buffer);
}

int __io_putchar(const char* str)
{
	UART_TransmitString(str);
    return ch;
}

int main(void)
{
    // Initialize UART2 and other peripherals
    UART_Init();
    I2C_Init();

    // Create the Temperature Task
    BaseType_t taskCreationResult = xTaskCreate(TemperatureTask, "Temperature Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &temperature_task_handle);

    if (taskCreationResult != pdPASS) {
        // Failed to create the task. Handle the error.
        // You can add error handling code here, such as logging or resetting the system.
    }

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // The scheduler should never return, but if it does, handle the error.
    // You can add error handling code here, such as logging or resetting the system.

    while (1) {
        // This code should never be reached as the scheduler should be running the tasks.
        // You can add error handling code here, such as logging or resetting the system.
    }
}


void TemperatureTask(void *pvParameters)
{
    while (1)
    {
        // Request temperature measurement
        AHT25_SendCommand(0xAC);

        // Wait for the measurement to complete
        // You may need to adjust the delay based on the sensor's response time
        osDelay(100);

        // Read the temperature data
        uint8_t temperatureData[3];
        AHT25_ReadData(temperatureData, 3);

        // Convert and print the temperature value
        temperature = AHT25_ConvertTemperature(temperatureData);
        printf("Temperature: %.2f°C\r\n", temperature);

        // Wait for the next iteration
        osDelay(1000);
    }
}

void I2C_Init(void) {

	RCC->AHB1ENR |= 2; /* Enable GPIOB clock */
	RCC->APB1ENR |= 0x00200000; /* Enable I2C1 clock */

	/* configure PB8, PB9 pins for I2C1 */
	GPIOB->AFR[1] &= ~0x000000FF; /* PB8, PB9 I2C1 SCL, SDA */
	GPIOB->AFR[1] |= 0x00000044;

	GPIOB->MODER &= ~0x000F0000; /* PB8, PB9 use alternate function */
	GPIOB->MODER |= 0x000A0000;

	GPIOB->OTYPER |= 0x00000300; /* output open-drain */
	GPIOB->PUPDR &= ~0x000F0000; /* with pull-ups */
	GPIOB->PUPDR |= 0x00050000;

	I2C1->CR1 = 0x8000; /* software reset I2C1 */
	I2C1->CR1 &= ~0x8000;/* out of reset */
	I2C1->CR2 = 0x0010; /* peripheral clock is 16 MHz*/
	I2C1->CCR = 80; /* standard mode, 100kHz clock */
	I2C1->TRISE = 17; /* maximum rise time */
	I2C1->CR1 |= 0x0001; /* enable I2C1module */
}

// Generate I2C start condition
void I2C_Start(void) {
	while (I2C1->SR2 & I2C_SR2_BUSY);   // Wait until bus is not busy
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));
}

// Generate I2C stop condition
void I2C_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
    while (I2C1->CR1 & I2C_CR1_STOP);
}


// Send a byte over I2C
void I2C_SendByte(uint8_t data) {
    I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_TXE));
}
// Receive a byte over I2C
uint8_t I2C_ReceiveByte(void) {
    while (!(I2C1->SR1 & I2C_SR1_RXNE));
    return I2C1->DR;
}

void AHT25_ReadData(uint8_t* data, uint8_t length) {
    I2C_Start();

    I2C_SendByte((AHT25_ADDRESS << 1) | 0x01);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    for (uint8_t i = 0; i < length; i++) {
        if (i == length - 1) {
            I2C1->CR1 &= ~I2C_CR1_ACK;
        }
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        data[i] = I2C1->DR;
    }

    I2C_Stop();
}

void AHT25_SendCommand(uint8_t command) {
    I2C_Start();

    I2C_SendByte(AHT25_ADDRESS << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    I2C_SendByte(command);
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C_Stop();
}


float AHT25_ConvertTemperature(uint8_t* data) {
    float temperature = ((float)(((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5])) / 1048576.0f * 200.0f - 50.0f;
    UART_TransmitFloat(temperature);
    return temperature;
}
