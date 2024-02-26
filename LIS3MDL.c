#include "lis3mdl.h"




// Call as lis3mdl_read_FS(
 status_t lis3mdl_read_FS(uint8_t *FSbuffer)
 {	 
	status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)LISMDL_CTRL_REG2,1, &I2C_buffer)
	if(success == STATUS_OK)
	{
		  lis3mdl_CTRL_REG2=I2Cbuffer[0];  // ONE BYTE ONLY, Update Local register struct
		  FSbuffer[0]=((IC2buffer[0] & 0x60) >> 5);	// Strip 2 bits of full-scale from register value
		  // if G required
		  // 0=4,1=8,2=12,3=16
		  //if(I2Cbuffer[0]==0) FSbuffer[0]=4;
		  //if(I2Cbuffer[0]==1) FSbuffer[0]=8;
		  //if(I2Cbuffer[0]==2) FSbuffer[0]=12;
		  //if(I2Cbuffer[0]==3) FSbuffer[0]=16;	  
		  return STATUS_OK;		  
	}
	else
		return STATUS_ERROR;
 
 
 status_t lis3mdl_read_ODR(uint8_t *ODRbuffer)
 {
	status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)LISMDL_CTRL_REG1,1, &I2C_buffer);
		if(success == STATUS_OK)
	{
		  lis3mdl_CTRL_REG1=I2Cbuffer[0];  // ONE BYTE ONLY, Update Local register struct
		  ODRbuffer[0]=((I2Cbuffer[0] & 0x1C) >> 2);	// Strip 3 bits of data rate into buffer
		  
		  return STATUS_OK;		  
	}
	else
		return STATUS_ERROR;
	 
 }
 
  uint8_t lis3mdl_read_AXIS_DATA(uint8_t axis,uint16_t *AXISbuffer) // BUFFER 16 BIT
  {
	  uint16_t inter=0;
	  	  
	  if((axis=='x') || (axis=='X'))
	  {
	  status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)OUT_X_H,1, &I2C_buffer);
	  if(success == STATUS_OK)
	  {
		  
		inter=I2Cbuffer[0]<8;  // ONE BYTE ONLY, Update Local register struct
		status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)OUT_X_L,1, &I2C_buffer);	  
			if(success == STATUS_OK)
			{
				inter+=buffer[0];
				AXISbuffer=inter;
			}
			else RETURN STATUS_ERROR;
		else RETURN STATUS_ERROR;
	  }
	  
	  	  if(axis=='y') || (axis=='Y')
	  {
	  status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)OUT_Y_H,1, &I2C_buffer);
	  if(success == STATUS_OK)
	  {
		  
		inter=I2Cbuffer[0]<8;  // ONE BYTE ONLY, Update Local register struct
		status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)OUT_Y_L,1, &I2C_buffer);	  
			if(success == STATUS_OK)
			{
				inter+=buffer[0];
				AXISbuffer=inter;
			}
			else RETURN STATUS_ERROR;
		else RETURN STATUS_ERROR;
	  }
	  
	  	  if((axis=='z') || (axis=='Z'))
	  {
	  status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)OUT_Z_H,1, &I2C_buffer);
	  if(success == STATUS_OK)
	  {
		  
		inter=I2Cbuffer[0]<8;  // ONE BYTE ONLY, Update Local register struct
		status_t success=i2c_read((uint8_t)LIS3MDL_address,(uint8_t)OUT_Z_L,1, &I2C_buffer);	  
			if(success == STATUS_OK)
			{
				inter+=buffer[0];
				AXISbuffer=inter;
			}
			else RETURN STATUS_ERROR;
		else RETURN STATUS_ERROR;
	  }
	  
  }
 
  uint8_t lis3mdl_write_ODR(uint8_t *ODRbuffer); // 0-6 
  {
	  I2C_buffer[0]=ODRbuffer;
	  if(I2C_buffer > 6) return STATUS_ERROR;
	  
	  I2Cbuffer[0]=(lis3mdl_CTRL_REG1 | (ODR_buffer << 2));	// Strip 3 bits of data rate into buffer
	  
	  status_t success=i2c_write((uint8_t)LIS3MDL_address,(uint8_t)LISMDL_CTRL_REG1,1, &I2C_buffer);  
	  		if(success == STATUS_OK)
			{
				lis3mdl_CTRL_REG1=I2Cbuffer[0];  // ONE BYTE ONLY, Update Local register struct						  
				return STATUS_OK;		  
			}
			else
				return STATUS_ERROR;
	  
  }
 
 
  uint8_t lis3mdl_enable_INTERRUPT_PIN(void)
  {
	  
	lis3mdl_INT_CFG.IEN=1;
	I2C_buffer[0]=(uint8_t)lis3mdl_INT_CFG;
	status_t success=i2c_write((uint8_t)LIS3MDL_address,(uint8_t)INT_CFG_REG,1, &I2C_buffer); 
	
	if(success == STATUS_OK)return STATUS_OK;					  
	else return STATUS_ERROR;
		
  }
  
  uint8_t lis3mdl_disable_INTERRUPT_PIN(void)
  {
	lis3mdl_INT_CFG.IEN=0;
	I2C_buffer[0]=(uint8_t)lis3mdl_INT_CFG;
	status_t success=i2c_write((uint8_t)LIS3MDL_address,(uint8_t)INT_CFG_REG,1, &I2C_buffer); 
	
	if(success == STATUS_OK)return STATUS_OK;					  
	else return STATUS_ERROR;
	  
  }
  
 