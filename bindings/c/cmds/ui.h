/**
 * @file
 * With the _User Interface_ command group, you can control the reader's feedback to the card holder, e.g. via LEDs and beeper.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_UI_H__
#define __BRP_BALTECH_SDK_CMDS_UI_H__
#include "../typedefs.h"
/**
 * The specified port isn't available or it doesn't support the desired operation.
 */
#define BRP_UI_ErrInvalidPort BRP_ERR_STATUS(0x0A00, 0x01)
typedef struct {
	brp_protocol protocol;
	brp_IoPort Port;
} brp_UI_Enable_t;
/**
 * This command enables a specific port of the reader. 
 * 
 * Depending on the type of the selected port, it does one of the following:
 * 
 *   * Drive an output pin high (GPIO)
 *   * Activate a peripheral component (beeper, relay)
 *   * Switch an LED to a certain color
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) I/O pins of the reader that can be controlled by the user.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Enable(brp_protocol protocol, brp_IoPort _input_Port);
#else
brp_errcode brp_UI_Enable(brp_UI_Enable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_IoPort Port;
} brp_UI_Disable_t;
/**
 * This command disables a specific port of the reader. 
 * 
 * Depending on the type of the selected port, it does one the following:
 * 
 *   * Drive an output pin low (GPIO)
 *   * Deactivate a peripheral component (beeper, relay)
 *   * Switch an LED off
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) I/O pins of the reader that can be controlled by the user.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Disable(brp_protocol protocol, brp_IoPort _input_Port);
#else
brp_errcode brp_UI_Disable(brp_UI_Disable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_IoPort Port;
	unsigned ToggleCount;
	unsigned Timespan1;
	unsigned Timespan2;
	brp_UI_Toggle_Polarity Polarity;
} brp_UI_Toggle_t;
/**
 * This command toggles the output state of a specific port. 
 * 
 * A single toggle consists of 2 state changes: From the initial state to the inverse state and back. The initial state is defined by the _Polarity_ parameter. This is also the state of the port at the end of the toggling operation. 
 * 
 * To stop the toggling, call UI.Enable or UI.Disable for this port.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) I/O pins of the reader that can be controlled by the user.
 *   - **ToggleCount** (in) The number of toggles. To toggle forever, choose 0xFF.
 *   - **Timespan1** (in) The time in ms that the port is to stay in the inverse state.
 *   - **Timespan2** (in) The time in ms that the port is to stay in the initial state.
 *   - **Polarity** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Toggle(brp_protocol protocol, brp_IoPort _input_Port, unsigned _input_ToggleCount, unsigned _input_Timespan1, unsigned _input_Timespan2, brp_UI_Toggle_Polarity _input_Polarity);
#else
brp_errcode brp_UI_Toggle(brp_UI_Toggle_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_IoPort Port;
	brp_UI_Sense_PortState* PortState;
} brp_UI_Sense_t;
/**
 * This command retrieves the logical state of a specific reader port. 
 * 
 * Only input ports are supported, e.g., InputX, GpioX, TamperAlarm.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) I/O pins of the reader that can be controlled by the user.
 *   - **PortState** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Sense(brp_protocol protocol, brp_IoPort _input_Port, brp_UI_Sense_PortState* PortState);
#else
brp_errcode brp_UI_Sense(brp_UI_Sense_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_LedBitMask LedState;
	unsigned RgbColor;
	unsigned TransitionTime;
} brp_UI_SetRgbLed_t;
/**
 * This command changes the RGB color of a single LED or a group of LEDs. The color may be activated instantly or smoothly by a sine-wave approximated fading transition. 
 * 
 * If the addressed LEDs are already active when this command is called, the color first fades to black (off), before the transition to the new color starts. 
 * 
 * **This command gives you direct control of the reader's LEDs. It competes with the command UI.Enable , which can be used to switch LEDs via Virtual LED port definitions (VLEDs)._UI.Enable_ operates on a higher abstraction level. Don't mix the 2 commands as this may result in inconsistent behavior.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LedState** (in) A bitmask containing the physical LEDs you want to switch.
 *   - **RgbColor** (in) The target RGB color (0x00RRGGBB).
 *   - **TransitionTime** (in) The time for the fading transition to activate the target RGB color in ms. If a color is currently activated, this is also the time for the transition to deactivate this color first. For an immediate color activation, set the value to 0.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_SetRgbLed(brp_protocol protocol, brp_LedBitMask _input_LedState, unsigned _input_RgbColor, unsigned _input_TransitionTime);
#else
brp_errcode brp_UI_SetRgbLed(brp_UI_SetRgbLed_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_LedBitMask LedState;
	unsigned RgbColor1;
	unsigned RgbColor2;
	unsigned TransitionTime;
	unsigned Period;
} brp_UI_PulseRgbLed_t;
/**
 * This command starts to pulse a single LED or a group of multiple LEDs continuously by performing smooth sine-wave approximated transitions between 2 RGB colors. 
 * 
 * To stop the pulsing, call the command UI.SetRgbLed. 
 * 
 * **This command gives you direct control of the reader's LEDs. It competes with the command UI.Enable , which can be used to switch LEDs via Virtual LED port definitions (VLEDs)._UI.Enable_ operates on a higher abstraction level. Don't mix the 2 commands as this may result in inconsistent behavior.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LedState** (in) A bitmask containing the physical LEDs you want to switch.
 *   - **RgbColor1** (in) The first RGB color of the desired pulse signal (0x00RRGGBB).
 *   - **RgbColor2** (in) The second RGB color of the desired pulse signal (0x00RRGGBB).
 *   - **TransitionTime** (in) The time for the fading transition to activate the first RGB color in ms. If a color is currently activated, this is also the time to deactivate this color first. For an immediate color activation, choose the value 0.
 *   - **Period** (in) The period of the pulse signal in ms. This is the time to transition from the first RGB color to the second and back to the first.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_PulseRgbLed(brp_protocol protocol, brp_LedBitMask _input_LedState, unsigned _input_RgbColor1, unsigned _input_RgbColor2, unsigned _input_TransitionTime, unsigned _input_Period);
#else
brp_errcode brp_UI_PulseRgbLed(brp_UI_PulseRgbLed_t params);
#endif
#endif
/**
 * @}
 */