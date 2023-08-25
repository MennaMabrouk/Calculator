#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_VidSendCommand(u8 Copy_u8Command);
void LCD_VidSendData(u8 Copy_u8Data);
void LCD_VidInit(void);
void LCD_VidSendString(u8 * Copy_u8ptrString);

void LCD_VidSendNumber(u16 Copy_u16Number);

void LCD_VidSetPosition(u8 Copy_u8Row , u8 Copy_u8Column);
void LCD_VidWriteExtraCharacter(u8 *Copy_u8ptrArr,u8 Copy_u8BlockNo,u8 Copy_u8RowPostion,u8 Copy_u8ColumnPostion);


#endif
