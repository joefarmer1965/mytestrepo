//LIS3MDL.h

#ifndef LIS3MDL_HEADER_H
#define LIS3MDL_HEADER_H

#include <stdint.h>

typedef enum {
    STATUS_OK,
    STATUS_ERROR
} status_t;

uint8_t I2C_buffer[5]={0,0,0,0,0};

//Hardware Adress selection
// Comment out the relevant define to select
#define LIS3MDL_address		001 1100b // Assuming SDO/SA1 is connected to ground
//#define LIS3MDL_address	001 1110b // Assuming SDO/SA1 is connected to V+

// ======  REGISTER DEFINITIONS ========

//AXES DATA READ REGISTERS 
#define OUT_X_L 0x28
#define OUT_X_H 0x29
  
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B

#define OUT_Z_L ox2C
#define OUT_Z_H 0x2D



//CONTROL REGISTER 1
#define LISMDL_CTRL_REG1             0x20
typedef struct
{
uint8_t Self-test		: 1;
uint8_t FAST_ODR		: 1; // HIGH=FIXED HS DATARATE, DEPENDS ON OPERATING MODE
uint8_t DataRate		: 3; // def 100
uint8_t OperMode		: 2; // 0 = LP, 1=
uint8_t Temp            : 1;
} lis3mdl_ctrl_reg1_t;
//0001 1100

//CONTROL REGISTER 2
#define LISMDL_CTRL_REG2             0x21
typedef struct
{
  uint8_t unused_1              : 2; // note - both bits need to be a zero
  uint8_t Soft_reset            : 1;
  uint8_t Reboot                : 1;
  uint8_t unused_2              : 1; // note - bit needs to be a zero
  uint8_t Full-scale            : 2;
  uint8_t bdu               	: 1;
} lis3mdl_ctrl_reg2_t;

#define INT_CFG_REG 				0x30;
typedef struct
{
  uint8_t IEN        : 1; 
  uint8_t LIR	     : 1;
  uint8_t IEA        : 1;
  uint8_t unused     : 2; // note - bit needs to be 01 To operate correctly
  uint8_t ZIEN       : 1;
  uint8_t YIEN       : 1;
   uint8_t ZIEN      : 1;
} lis3mdl_int_cfg_reg_t;


// 	instantiate & initialise required variables with default states
lis3mdl_ctrl_reg4_t lis3mdl_CTRL_REG1=0b00010000;	// Requred for datarate settings
lis3mdl_ctrl_reg2_t lis3mdl_CTRL_REG2=0b00000000;	// required for FULL-SCALE settings
lis3mdl_int_cfg_reg_t lis3mdl_INT_CFG=0b11101000; 	// required for Int pin enable



// ==== READ FUNCTION PROTOTYPES ====
 uint8_t lis3mdl_read_FS(uint8_t *FSbuffer);
 uint8_t lis3mdl_read_ODR(uint8_t *ODRbuffer);
 uint8_t lis3mdl_read_AXIS_DATA(uint8_t axis, uint16_t *AXISbuffer);
 
 // ==== WRITE FUNCTION PROTOTYPES ====
 uint8_t lis3mdl_write_ODR(uint8_t *ODRbuffer);
  uint8_t lis3mdl_enable_INTERRUPT_PIN(void);
  uint8_t lis3mdl_disable_INTERRUPT_PIN(void);
  
 


 #endif
