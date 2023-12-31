 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Abdelmonem Shinaishin
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for Set Pin Directions API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for Set Pin Mode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* Number of the configured Pins */
#define PORT_CONFIGURED_PINS                 (39U)

/* Port Pin Index in the array of structures in Port_PBcfg.c */
#define PortConf_PortF_Pin1_ID_INDEX         (Port_PinType)0x00
#define PortConf_PortF_Pin4_ID_INDEX         (Port_PinType)0x01
#define PortConf_PortA_Pin0_ID_INDEX         (Port_PinType)0x02
#define PortConf_PortA_Pin1_ID_INDEX         (Port_PinType)0x03
#define PortConf_PortA_Pin2_ID_INDEX         (Port_PinType)0x04
#define PortConf_PortA_Pin3_ID_INDEX         (Port_PinType)0x05
#define PortConf_PortA_Pin4_ID_INDEX         (Port_PinType)0x06
#define PortConf_PortA_Pin5_ID_INDEX         (Port_PinType)0x07
#define PortConf_PortA_Pin6_ID_INDEX         (Port_PinType)0x08
#define PortConf_PortA_Pin7_ID_INDEX         (Port_PinType)0x09
#define PortConf_PortB_Pin0_ID_INDEX         (Port_PinType)0x10
#define PortConf_PortB_Pin1_ID_INDEX         (Port_PinType)0x11
#define PortConf_PortB_Pin2_ID_INDEX         (Port_PinType)0x12
#define PortConf_PortB_Pin3_ID_INDEX         (Port_PinType)0x13
#define PortConf_PortB_Pin4_ID_INDEX         (Port_PinType)0x14
#define PortConf_PortB_Pin5_ID_INDEX         (Port_PinType)0x15
#define PortConf_PortB_Pin6_ID_INDEX         (Port_PinType)0x16
#define PortConf_PortB_Pin7_ID_INDEX         (Port_PinType)0x17
#define PortConf_PortC_Pin4_ID_INDEX         (Port_PinType)0x18
#define PortConf_PortC_Pin5_ID_INDEX         (Port_PinType)0x19
#define PortConf_PortC_Pin6_ID_INDEX         (Port_PinType)0x20
#define PortConf_PortC_Pin7_ID_INDEX         (Port_PinType)0x21
#define PortConf_PortD_Pin0_ID_INDEX         (Port_PinType)0x22
#define PortConf_PortD_Pin1_ID_INDEX         (Port_PinType)0x23
#define PortConf_PortD_Pin2_ID_INDEX         (Port_PinType)0x24
#define PortConf_PortD_Pin3_ID_INDEX         (Port_PinType)0x25
#define PortConf_PortD_Pin4_ID_INDEX         (Port_PinType)0x26
#define PortConf_PortD_Pin5_ID_INDEX         (Port_PinType)0x27
#define PortConf_PortD_Pin6_ID_INDEX         (Port_PinType)0x28
#define PortConf_PortD_Pin7_ID_INDEX         (Port_PinType)0x29
#define PortConf_PortE_Pin0_ID_INDEX         (Port_PinType)0x30
#define PortConf_PortE_Pin1_ID_INDEX         (Port_PinType)0x31
#define PortConf_PortE_Pin2_ID_INDEX         (Port_PinType)0x32
#define PortConf_PortE_Pin3_ID_INDEX         (Port_PinType)0x33
#define PortConf_PortE_Pin4_ID_INDEX         (Port_PinType)0x34
#define PortConf_PortE_Pin5_ID_INDEX         (Port_PinType)0x35
#define PortConf_PortF_Pin0_ID_INDEX         (Port_PinType)0x36
#define PortConf_PortF_Pin2_ID_INDEX         (Port_PinType)0x37
#define PortConf_PortF_Pin3_ID_INDEX         (Port_PinType)0x38

/* PORT Configured Port ID's  */
#define PortConf_PORTA_ID                 (uint8)0 /* PORTA */
#define PortConf_PORTB_ID                 (uint8)1 /* PORTB */
#define PortConf_PORTC_ID                 (uint8)2 /* PORTC */
#define PortConf_PORTD_ID                 (uint8)3 /* PORTD */
#define PortConf_PORTE_ID                 (uint8)4 /* PORTE */
#define PortConf_PORTF_ID                 (uint8)5 /* PORTF */

/* PORT Configured Pin ID's */
#define PortConf_PIN0                     (uint8)0 /* Pin 0 */
#define PortConf_PIN1                     (uint8)1 /* Pin 1 */
#define PortConf_PIN2                     (uint8)2 /* Pin 2 */
#define PortConf_PIN3                     (uint8)3 /* Pin 3 */
#define PortConf_PIN4                     (uint8)4 /* Pin 4 */
#define PortConf_PIN5                     (uint8)5 /* Pin 5 */
#define PortConf_PIN6                     (uint8)6 /* Pin 6 */
#define PortConf_PIN7                     (uint8)7 /* Pin 7 */

#endif /* PORT_CFG_H_ */
