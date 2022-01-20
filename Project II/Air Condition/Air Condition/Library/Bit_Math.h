#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define Set_Bit(REG,bit)                        (REG |=   (1<<bit))
#define Clr_Bit(REG,bit)                        (REG &= ~ (1<<bit))
#define Toggle_Bit(REG,bit)                     (REG ^=   (1<<bit))

#define setBits(REG,BM)							((REG) |=  (BM))
#define clearBits(REG,BM)						((REG) &= ~(BM))
#define toggleBits(REG,BM)						((REG) ^=  (BM))

#define setAllBits(REG)							((REG)  =  (0xFF))
#define clearAllBits(REG)						((REG)  =  (0x00))
#define toggleAllBits(REG)						((REG) ^=  (0xFF))

#define Get_Bit(REG,bit)                        (((REG>>bit)&(0x01)))

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Read a certain bit in any register */
#define READ_BIT(REG,BIT) ((REG & (1<<BIT)) >> BIT)

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif /* BIT_MATH_H_ */