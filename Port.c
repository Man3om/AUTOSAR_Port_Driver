/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Abdelmonem Shinaishin
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC uint8 PORT_Status = PORT_NOT_INITIALIZED;
STATIC const Port_ConfigPin * Port_PinPtr = NULL_PTR;

/************************************************************************************
 * Service Name: Port_Init
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: initialize ALL ports and port pins with the
               configuration set pointed to by the parameter ConfigPtr.
 ************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr )
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if(ConfigPtr == NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_POINTER);
    }
    else
#endif
    {
        PORT_Status = PORT_INITIALIZED ;    /* Set the module state to initialized */
        Port_PinPtr = ConfigPtr->Pins ;     /* address of the first Pin structure --> Pins[0] */

        volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        Port_PinType Port_PinID = PORT_ZERO ;         /* refer to Port Pin Id */

        for(Port_PinID = PORT_ZERO ; Port_PinID < PORT_CONFIGURED_PINS ; Port_PinID++)
        {
            switch(Port_PinPtr[Port_PinID].PortNum)
            {
            case  0:
                Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  1:
                Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  2:
                Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  3:
                Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  4:
                Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  5:
                Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            default:
                /* Do Nothing */
                break;
            }

            if( ((Port_PinPtr[Port_PinID].PortNum == 3) && (Port_PinPtr[Port_PinID].PinNum == 7)) || ((Port_PinPtr[Port_PinID].PortNum == 5) && (Port_PinPtr[Port_PinID].PinNum == 0)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                              /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            switch(Port_PinPtr[Port_PinID].direction)
            {
            case PORT_PIN_OUT:
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(Port_PinPtr[Port_PinID].initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
                break;
            case PORT_PIN_IN:
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(Port_PinPtr[Port_PinID].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(Port_PinPtr[Port_PinID].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
                break ;
            default:
                /* Do nothing */
                break;
            }

            /* Check The mode Of Port Pin */
            if(Port_PinPtr[Port_PinID].PinMode == PORT_PIN_MODE_DIO)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Port_PinID].PinNum * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            else if(Port_PinPtr[Port_PinID].PinMode == PORT_PIN_MODE_ADC)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);        /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Port_PinID].PinNum * 4));     /* Clear the PMCx bits for this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);       /* Clear the corresponding bit in the GPIODEN register to Disable digital functionality on this pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);               /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */

                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Port_PinID].PinNum * 4));                        /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= ( Port_PinPtr[Port_PinID].PinMode << (Port_PinPtr[Port_PinID].PinNum * 4));      /* Set the PMCx bits for this pin */

                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
        }
    }
}


/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - Port Pin ID number
                   Direction - Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction.
 ************************************************************************************/
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
    boolean Error = FALSE ;
    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(PORT_Status != PORT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
        Error = STD_HIGH ;
    }
    else
    {
        /* Do Nothing */
    }

    /* Check if the used Pin is within the valid range */
    if(Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_PARAM_PIN);
        Error = TRUE ;
    }
    else
    {
        /* Do Nothing */
    }

    /* Check if the used pin configured as changeable or not */
    if(Port_PinPtr[Pin].DirectionChangeable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_DIRECTION_UNCHANGEABLE);
        Error = TRUE ;
    }
    else
    {
        /* Do Nothing */
    }
#endif

    if(Error != TRUE)
    {
        switch(Port_PinPtr[Pin].PortNum)
        {
        case  0:
            Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case  1:
            Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case  2:
            Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case  3:
            Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case  4:
            Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case  5:
            Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        default:
            /* Do Nothing */
            break;
        }

        if( ((Port_PinPtr[Pin].PortNum == 3) && (Port_PinPtr[Pin].PinNum == 7)) || ((Port_PinPtr[Pin].PortNum == 5) && (Port_PinPtr[Pin].PinNum == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                              /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PinPtr[Pin].PinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        switch(Direction)
        {
        case PORT_PIN_OUT:
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Pin].PinNum);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            break;
        case PORT_PIN_IN:
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Pin].PinNum);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            break ;
        default:
            /* Do nothing */
            break;
        }

    }
    else
    {
        /* Do Nothing */
    }
}
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: refresh the direction of all configured ports
               to the configured direction.
 ************************************************************************************/
void Port_RefreshPortDirection(void)
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(PORT_Status != PORT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_REFRESH_PIN_DIRECTION_SID,PORT_E_UNINIT);
    }
    else
#endif
    {
        volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        Port_PinType Port_PinID = PORT_ZERO ;         /* refer to Port Pin Id */

        for(Port_PinID = PORT_ZERO ; Port_PinID < PORT_CONFIGURED_PINS ; Port_PinID++)
        {
            switch(Port_PinPtr[Port_PinID].PortNum)
            {
            case  0:
                Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  1:
                Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  2:
                Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  3:
                Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  4:
                Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  5:
                Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            default:
                /* Do Nothing */
                break;
            }

            if( ((Port_PinPtr[Port_PinID].PortNum == 3) && (Port_PinPtr[Port_PinID].PinNum == 7)) || ((Port_PinPtr[Port_PinID].PortNum == 5) && (Port_PinPtr[Port_PinID].PinNum == 0)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                              /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            switch(Port_PinPtr[Port_PinID].direction)
            {
            case PORT_PIN_OUT:
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                break;
            case PORT_PIN_IN:
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Port_PinID].PinNum);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                break ;
            default:
                /* Do nothing */
                break;
            }
        }
    }
}


/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version
                                  information of this module
 * Parameters (out): None
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(versioninfo += NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID,PORT_E_PARAM_POINTER);
    }
    else
#endif
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif


/************************************************************************************
 * Service Name: Port_SetPinMode
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - Port Pin ID number
                   Mode - New Port Pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: refresh the direction of all configured ports
               to the configured direction.
 ************************************************************************************/
#if(PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
    boolean Error = FALSE ;
    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(PORT_Status != PORT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
        Error = TRUE ;
    }
    else
    {
        /* Do Nothing */
    }

    /* Check if the used Pin is within the valid range */
    if(Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_PARAM_PIN);
        Error = TRUE ;
    }
    else
    {
        /* Do Nothing */
    }

    /* Check if the used pin configured as changeable or not */
    if(Port_PinPtr[Pin].ModeChangeable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_MODE_UNCHANGEABLE);
        Error = TRUE ;
    }
    else
    {
        /* Do Nothing */
    }

    /* Check if the pin mode is valid or not  */
    if(Mode > PORT_PIN_MODE_DIO)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_PARAM_INVALID_MODE);
        Error = TRUE ;
    }
    else
    {
        /* Do Nothing */
    }
#endif

    if(Error != TRUE)
    {
        switch(Port_PinPtr[Pin].PortNum)
        {
        case  0:
            Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case  1:
            Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case  2:
            Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case  3:
            Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case  4:
            Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case  5:
            Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        default:
            /* Do Nothing */
            break;
        }

        if( ((Port_PinPtr[Pin].PortNum == 3) && (Port_PinPtr[Pin].PinNum == 7)) || ((Port_PinPtr[Pin].PortNum == 5) && (Port_PinPtr[Pin].PinNum == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                              /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PinPtr[Pin].PinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        /* Check The mode Of Port Pin */
        if(Port_PinPtr[Pin].PinMode == PORT_PIN_MODE_DIO)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Pin].PinNum);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Pin].PinNum);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Pin].PinNum * 4));     /* Clear the PMCx bits for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Pin].PinNum);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
        else if(Port_PinPtr[Pin].PinMode == PORT_PIN_MODE_ADC)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Pin].PinNum);        /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Pin].PinNum);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Pin].PinNum * 4));     /* Clear the PMCx bits for this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Pin].PinNum);       /* Clear the corresponding bit in the GPIODEN register to Disable digital functionality on this pin */
        }
        else /* Any Alternative Mode */
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Pin].PinNum);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Pin].PinNum);               /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */

            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Pin].PinNum * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= ( Mode << (Port_PinPtr[Pin].PinNum * 4));           /* Set the PMCx bits for this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Pin].PinNum);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
    }
    else
    {
        /* Do Nothing */
    }
}
#endif
