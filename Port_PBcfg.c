/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Abdelmonem Shinaishin
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


#include "Port.h"

/* AUTOSAR Version checking between Port_PBcfg.h and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_PBvfg.h and port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

const Port_ConfigType PinType = {
                                 PortConf_PIN1,PortConf_PORTF_ID,PORT_PIN_OUT,OFF,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN4,PortConf_PORTF_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,

                                 PortConf_PIN0,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN1,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN2,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN3,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN4,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN5,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN6,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN7,PortConf_PORTA_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,

                                 PortConf_PIN0,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN1,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN2,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN3,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN4,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN5,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN6,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN7,PortConf_PORTB_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,

                                 PortConf_PIN4,PortConf_PORTC_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN5,PortConf_PORTC_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN6,PortConf_PORTC_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN7,PortConf_PORTC_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,

                                 PortConf_PIN0,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN1,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN2,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN3,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN4,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN5,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN6,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN7,PortConf_PORTD_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,

                                 PortConf_PIN0,PortConf_PORTE_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN1,PortConf_PORTE_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN2,PortConf_PORTE_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN3,PortConf_PORTE_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN4,PortConf_PORTE_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN5,PortConf_PORTE_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,

                                 PortConf_PIN0,PortConf_PORTF_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN2,PortConf_PORTF_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
                                 PortConf_PIN3,PortConf_PORTF_ID,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_LOW,STD_OFF,STD_OFF,PORT_PIN_MODE_DIO,
};
