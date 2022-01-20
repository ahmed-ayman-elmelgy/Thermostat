/*
 * DIO.c
 *
 *  Created on: Jan 2, 2022
 *      Author: Micheal-Onsy
 */

#include "DIO.h"

ERROR_STATE_t DIO_setPortDirection(uint8_t PortID, uint8_t PortDirection)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	//Check for the ports if it is between 0 to 3
    switch (PortID)
    {
    case PORTa :
        DDRA = PortDirection;
        break;
    case PORTb :
        DDRB = PortDirection;
        break;
    case PORTc :
        DDRC = PortDirection;
        break;
    case PORTd :
        DDRD = PortDirection;
        break;
    default:
        u8_ERROR_STAT = ERROR_NOK;
        break;
    } //END of SWITCH
    return u8_ERROR_STAT ;
}	  //END DIO_setPortDirection

/********************************************************************
*  API to Set Pin Direction                                         *
*  *****************************************************************/
ERROR_STATE_t DIO_setPinDirection(uint8_t PortID, uint8_t PinNumber,uint8_t PinDirection)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	if ((PinNumber >= PIN0 )&& (PinNumber <= PIN7 ))
	{
		if (DIO_u8_OUTPUT==PinDirection)
		{
			switch (PortID)
			{
			case PORTa :
				Set_Bit(DDRA, PinNumber);
				break;
			case PORTb :
				Set_Bit(DDRB, PinNumber);
				break;
			case PORTc :
				Set_Bit(DDRC, PinNumber);
				break;
			case PORTd :
				Set_Bit(DDRD, PinNumber);
				break;
            default:
                u8_ERROR_STAT = ERROR_NOK;
                break;
			} //END of SWITCH
		} // END of IF that check for the direction if it is INPUT

		else if (DIO_u8_INPUT == PinDirection)
		{
			switch (PortID)
			{
			case PORTa :
				Clr_Bit(DDRA, PinNumber);
				break;
			case PORTb :
				Clr_Bit(DDRB, PinNumber);
				break;
			case PORTc :
				Clr_Bit(DDRC, PinNumber);
				break;
			case PORTd :
				Clr_Bit(DDRD, PinNumber);
				break;
            default:
                u8_ERROR_STAT = ERROR_NOK;
                break;
			} //END of SWITCH
		} // END of ELSE IF that check for the direction if it is INPUT
		else
		{
			u8_ERROR_STAT = ERROR_NOK;
		} //END OF ELSE
	}	  //END of IF That checking the port and pin number
	else
	{
		u8_ERROR_STAT = ERROR_NOK;

	}	  //END of ELSE
	return u8_ERROR_STAT;
}	  //END DIO_setPinDirection

/* API to Write Port  Value */
ERROR_STATE_t DIO_writePortValue(uint8_t PortID, uint8_t PortValue)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
    switch (PortID)
    {
    case PORTa :
        PORTA = PortValue;
        break;
    case PORTb :
        PORTB = PortValue;
        break;
    case PORTc :
        PORTC = PortValue;
        break;
    case PORTd :
        PORTD = PortValue;
        break;
    default:
        u8_ERROR_STAT = ERROR_NOK;
        break;
    } //END of SWITCH
    return u8_ERROR_STAT ;
}	  //END DIO_writePortValue

/* API to Write Pin  Value */
ERROR_STATE_t DIO_writePinValue(uint8_t PortID, uint8_t PinNumber,uint8_t PinDirection)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
    /*CHECK IF VALID PIN NUMBER*/
	if ( (PinNumber >= PIN0 )&& (PinNumber <= PIN7 ))
	{
		if (DIO_u8_HIGH==PinDirection)
		{
			switch (PortID)
			{
			case PORTa :
				Set_Bit(PORTA, PinNumber);
				break;
			case PORTb :
				Set_Bit(PORTB, PinNumber);
				break;
			case PORTc :
				Set_Bit(PORTC, PinNumber);
				break;
			case PORTd :
				Set_Bit(PORTD, PinNumber);
				break;
            default:
                u8_ERROR_STAT = ERROR_NOK;
                break;
			} //END of SWITCH
		} // END of IF that check for the direction if it is INPUT
		else if (DIO_u8_LOW==PinDirection)
		{
			switch (PortID)
			{
			case PORTa :
				Clr_Bit(PORTA, PinNumber);
				break;
			case PORTb :
				Clr_Bit(PORTB, PinNumber);
				break;
			case PORTc :
				Clr_Bit(PORTC, PinNumber);
				break;
			case PORTd :
				Clr_Bit(PORTD, PinNumber);
				break;
            default:
                /*INVALID PORT NUMBER*/
                u8_ERROR_STAT = ERROR_NOK;
                break;
			} //END of SWITCH
		} // END OF ELSE IF
		else
        {
            /*INVALID PIN DIRECTION*/
			u8_ERROR_STAT = ERROR_NOK;
		} //END OF ELSE
	}	  //END OF IF
	else
	{
        /*INVALID PIN NUMBER*/
		u8_ERROR_STAT = ERROR_NOK;
	}	  //END of ELSE
	return u8_ERROR_STAT ;
}	  //END of DIO_writePinValue

/* API to Read Port  Value */
ERROR_STATE_t DIO_readPort(uint8_t PortID, uint8_t* PortState)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
    /*CHECK IF PinState=NULL POINTER*/
	if(NULL_PTR==PortState)
    {
        u8_ERROR_STAT = ERROR_NOK;
	}
	else
	{
    switch (PortID)
    {
    case PORTa :
        *(PortState) = PINA;
        break;
    case PORTb :
        *(PortState) = PINB;
        break;
    case PORTc :
        *(PortState) = PINC;
        break;
    case PORTd :
        *(PortState) = PIND;
        break;
    default:
            /*INVALID PORT NUMBER*/
        u8_ERROR_STAT = ERROR_NOK;
        break;

		} //END of SWITCH
	}
	return u8_ERROR_STAT ;
}	  //END of DIO_readPort

/* API to Read Pin  Value */
ERROR_STATE_t DIO_readPin(uint8_t PortID, uint8_t PinNumber,uint8_t* PinState)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
    /*CHECK IF PinState=NULL POINTER*/
	if(NULL_PTR==PinState)
    {
        u8_ERROR_STAT = ERROR_NOK;
	}
	else
	{
        /*CHECK IF INVALID PIN NUMBER*/
        if ((PinNumber >= PIN0 )&& (PinNumber <= PIN7 ))
        {
            switch (PortID)
            {
            case PORTa :
                *(PinState) = Get_Bit(PINA, PinNumber);
                break;
            case PORTb :
                *(PinState) = Get_Bit(PINB, PinNumber);
                break;
            case PORTc :
                *(PinState) = Get_Bit(PINC, PinNumber);
                break;
            case PORTd :
                *(PinState) = Get_Bit(PIND, PinNumber);
                break;
            default:
                /*INVALID PORT NUMBER*/
                u8_ERROR_STAT = ERROR_NOK;
                break;
            } //END of SWITCH
        }	  //END of IF That checking the port and pin number
        else
        {
            u8_ERROR_STAT = ERROR_NOK;
        }	  //END of ELSE
	}
    return u8_ERROR_STAT ;
}    //END of DIO_readPint
/*
 * API to toggle pin
 * */
ERROR_STATE_t DIO_TogglePin(uint8_t PortID, uint8_t PinNumber)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
    /*CHECK IF VALID PIN NUMBER*/
    if ((PinNumber >= PIN0 )&& (PinNumber <= PIN7 ))
    {
        switch (PortID)
        {
        case PORTa :
            Toggle_Bit(PORTA, PinNumber);
            break;
        case PORTb :
            Toggle_Bit(PORTB, PinNumber);
            break;
        case PORTc :
            Toggle_Bit(PORTC, PinNumber);
            break;
        case PORTd :
            Toggle_Bit(PORTD, PinNumber);
            break;
        default:
            /*INVALID PORT NUMBER*/
            u8_ERROR_STAT = ERROR_NOK;
            break;
        } //END OF SWITCH
    }	  //END OF IF
    else {
        /*INVALID PIN NUMBER*/
        u8_ERROR_STAT = ERROR_NOK;
    }	  //END of ELSE
    return u8_ERROR_STAT ;
}
ERROR_STATE_t DIO_SetPullupRes(uint8_t PortID, uint8_t PinNumber)
{
    ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
    /*CHECK IF VALID PIN NUMBER*/
    if ((PinNumber >= PIN0 )&& (PinNumber <= PIN7 ))
    {
        switch (PortID)
        {
        case PORTa :
            if(DIO_u8_INPUT==Get_Bit(DDRA, PinNumber))
            {
                Set_Bit(PORTA, PinNumber);
            }// END of IF which checking if the  pin is INPUT
            else
            {
                u8_ERROR_STAT = ERROR_NOK;
            }
            break;
        case PORTb :
            if(DIO_u8_INPUT==Get_Bit(DDRB, PinNumber))
            {
                Set_Bit(PORTB, PinNumber);
            }// END of IF which checking if the  pin is INPUT
            else
            {
                u8_ERROR_STAT = ERROR_NOK;
            }
            break;
        case PORTc :
            if(DIO_u8_INPUT==Get_Bit(DDRC, PinNumber))
            {
                Set_Bit(PORTC, PinNumber);
            }// END of IF which checking if the  pin is INPUT
            else
            {
                u8_ERROR_STAT = ERROR_NOK;
            }
            break;
        case PORTd :
            if(DIO_u8_INPUT==Get_Bit(DDRD, PinNumber))
            {
                Set_Bit(PORTD, PinNumber);
            }// END of IF which checking if the  pin is INPUT
            else
            {
                u8_ERROR_STAT = ERROR_NOK;
            }
            break;
        default:
            /*INVALID PORT NUMBER*/
            u8_ERROR_STAT = ERROR_NOK;
            break;
        } //END OF SWITCH
    }	  //END OF IF

    else
    {
        /*INVALID PIN NUMBER*/
        u8_ERROR_STAT = ERROR_NOK;
    } //END of ELSE
    return u8_ERROR_STAT ;
}
