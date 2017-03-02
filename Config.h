// -----------------------------------------------------------------------------------
// Configuration (G11)

/*
 * For more information on setting OnStep up see http://www.stellarjourney.com/index.php?r=site/equipment_onstep and 
 * join the OnStep yahoo group at https://groups.yahoo.com/neo/groups/onsteptelescope/info
 * 
 * The Arduino Mega2560 and Teensy3.1/3.2 use USB for power and communication with the host computer
 * some Launchpad TM4C devices are also supported (thanks to Luka,) see OnStep.ino for pin definitions
 *
 * The RA/Az (Axis1) and Dec/Alt (Axis2) stepper driver minimum connection is as follows:
 * RA/Az :  37,35 = Dir,Step (Teensy3.2 14,15)
 * Dec/Alt: 22,24 = Dir,Step (Teensy3.2  2, 3)
 *
 * Optionally, a bluetooth or WiFi adapter (HC05, RN42, or ESP8266 for example) plugs into pins Tx1/Rx1.
 * +5VDC is normally used for the BT Adapter and +3.3VDC for the ESP8266 (make sure the regulator is sufficient to supply required current.)
 * I use two 2-wire cables for 0.1" headers.  Remember Rx goes to Tx and Tx goes to Rx. If using a Mega2560
 * be sure to get a BT module designed for 5 volt operation and signaling otherwise you'll have to design
 * and implement the level conversion hardware yourself.
*/

// ******************* These new pin assignments aren't well tested and mistakes might have been made, a mistake might damage your MCU etc. Use at your own risk. *****************
//
// This must be _ON to use the pin assignments given in this Config.h!  The Launchpad TM4C123GH6PM and LM4F120H5QR also have alternate pin assignments in this mode, see OnStep.ino
// this allows minimal wiring for Pololu style stepper driver modules and also frees SPI pins to allow use of the Arduino Ethernet Shield on the Teensy3.2 and Launchpad TM4C123GXL
//
#define ALTERNATE_PINMAP_ON
// ******************* These new pin assignments aren't well tested and mistakes might have been made, a mistake might damage your MCU etc. Use at your own risk. *****************

// -------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES --------------------------------------------------------------

// turns debugging on, used during testing, default=OFF
#define DEBUG_OFF

// turns W5100 ethernet shield support on (SPI interface,) default=OFF (if _ON you must also uncomment the #include "EthernetPlus.h" line near the beginning of OnStep.ino for now)
// configure the interface IP address and subnet mask in Ethernet.ino
// see forum below for good technical info. about using an Arduino Ethernet Shield:
// https://forum.pjrc.com/threads/25050-Teensy-3-0-3-1-W5100-ethernet-shield
#define W5100_OFF
// default IP,Gateway,subnet are in the Network.ino file
// if ethernet is available DHCP is used to obtain the IP address (default addresses are overridden), default=OFF
#define ETHERNET_USE_DHCP_OFF

// ESP8266 reset and GPIO0 control, this sets run mode for normal operation.  Uploading programmer firmware to the OpStep MCU can then enable sending new firmware to the ESP8266-01
// Only supported on the Teensy3.2, Pin 18 (Aux1) for Rst and Pin 5 (Aux2) for GPIO0 control.  Choose only one feature on Aux1/2.
#define ESP8266_CONTROL_OFF

// allows syncing anywhere, default=ON
#define SYNC_ANYWHERE_ON

// Mount type, default is _GEM (German Equatorial) other options are _FORK, _FORK_ALT.  _FORK switches off Meridian Flips after (1, 2 or 3 star) alignment is done.  _FORK_ALT disables Meridian Flips (1 star align.)
// _ALTAZM is for Alt/Azm mounted 'scopes (1 star align only.)
#define MOUNT_TYPE_GEM

// ST4 interface on pins 47, 43, 45, 49.  Pin 47 is RA- (West), Pin 43 is Dec- (South), Pin 45 is Dec+ (North), Pin 49 is RA+ (East.)  (Teensy3.2 pins 24, 25, 26, 27)
// ST4_ON enables the interface.  ST4_PULLUP enables the interface and any internal pullup resistors.  default=OFF
// It is up to you to create an interface that meets the electrical specifications of any connected device, use at your own risk.
// ST4_HAND_CONTROL_ON allows guide rates >1x while SEPERATE_PULSE_GUIDE_RATE_ON is enabled
// ST4_ALTERNATE_PINS_ON moves the interface (Teensy3.2 only) to pins 10, 11, 12, 13.  Pin 10 is RA- (West), Pin 11 is Dec- (South), Pin 12 is Dec+ (North), Pin 13 is RA+ (East.)  The default SPI interface is then unavailable.
#define ST4_PULLUP
#define ST4_HAND_CONTROL_ON
#define ST4_ALTERNATE_PINS_ON
// PPS sense rising edge on pin 21 for optional precision clock source (GPS, for example), default=OFF (Teensy3.2 Pin 28)
#define PPS_SENSE_OFF
// PEC sense on pin 2 or threshold value on analog 1 (pin 23/analog 9 on Teensy3.2) use _ON or _PULLUP to enable the input and use the built-in pullup resistor, default=OFF
// Analog values range from 0 to 1023 which indicate voltages from 0-5VDC (or 0-3.3VDC) on the analog pin, for example "PEC_SENSE 600" would detect an index when the voltage exceeds 2.92V (or 1.93V)
// with either index detection method, once triggered 60s must expire before another detection can happen.  This gives time for the index magnet to pass by the detector before another cycle begins.
// Ignored on Alt/Azm mounts.
#define PEC_SENSE_ON
// PEC sense, rising edge (default with PEC_SENSE_STATE HIGH, use LOW for falling edge, ex. PEC_SENSE_ON) ; for optional PEC index
#define PEC_SENSE_STATE LOW
// switch close (to ground) on pin 3 for optional limit sense (stops gotos and/or tracking), default=OFF (Teensy3.2 Pin 4)
#define LIMIT_SENSE_ON
// light status LED by sink to ground (pin 9) and source +5V (pin 8), default=ON.  (Teensy3.2 Pin 19, no V+ pin)
// _ON and OnStep keeps this illuminated to indicate that the controller is active.  When sidereal tracking this LED will rapidly flash
#define STATUS_LED_PINS_ON
// lights 2nd status LED by sink to ground (pin 7), default=OFF. (Teensy3.2 Pin 22)
// _ON sets this to blink at 1 sec intervals when PPS is synced
#define STATUS_LED2_PINS_ON
// lights reticule LED by sink to ground (pin 44), default=OFF.  (Teensy3.2 Pin 22, don't use with STATUS_LED2_PINS_ON)
// RETICULE_LED_PINS n, where n=0 to 255 activates this feature and sets default brightness
#define RETICULE_LED_PINS_OFF

// optionally adjust tracking rate to compensate for atmospheric refraction, default=OFF (limited testing done)
// can be turned on/off with the :Te# and :Td# commands regardless of this setting
#define TRACK_REFRACTION_RATE_DEFAULT_OFF

// use seperate pulse-guide rate so centering and guiding don't disturb each other, default=ON
#define SEPERATE_PULSE_GUIDE_RATE_ON

// ADJUST THE FOLLOWING TO MATCH YOUR MOUNT --------------------------------------------------------------------------------
#define RememberMaxRate_ON           // set to ON and OnStep will remember rates set in the ASCOM driver or Android App, default=OFF 
#define MaxRate                   40 // this is the minimum number of micro-seconds between micro-steps
                                     // minimum* (fastest goto) is around 16 (Teensy3.2) or 32 (Mega2560), default=96 higher is ok
                                     // too low and OnStep communicates slowly and/or freezes as the motor timers use up all the MCU time
                                     // * = minimum can be lower, when both AXIS1/AXIS2_MODE_GOTO are used by AXIS1/AXIS2_STEP_GOTO times
                                     
#define DegreesForAcceleration  15.0 // approximate number of degrees for full acceleration or deceleration: higher values=longer acceleration/deceleration
                                     // Default=5.0, too low (about <1) can cause gotos to never end if micro-step mode switching is enabled.
#define DegreesForRapidStop      2.5 // approximate number of degrees required to stop when requested or if limit is exceeded during a slew: higher values=longer deceleration
                                     // Default=1.0, too low (about <1) can cause gotos to never end if micro-step mode switching is enabled.

#define BacklashTakeupRate        25 // backlash takeup rate (in multipules of the sidereal rate): too fast and your motors will stall,
                                     // too slow and the mount will be sluggish while it moves through the backlash
                                     // for the most part this doesn't need to be changed, but adjust when needed.  Default=25

                                     // Axis1 is for RA/Az
#define StepsPerDegreeAxis1  12800.0 // calculated as    :  stepper_steps * micro_steps * gear_reduction1 * (gear_reduction2/360)
                                     // G11              :  400           * 32          * 1               *  360/360              = 12800
                                     // Axis2 is for Dec/Alt
#define StepsPerDegreeAxis2  12800.0 // calculated as    :  stepper_steps * micro_steps * gear_reduction1 * (gear_reduction2/360)
                                     // G11              :  400           * 32          * 1               *  360/360              = 12800
                                     // the EM10b has two spur gears that drive the RA/Dec worms, they give an additional 1.25:1 reduction
                                     // in addition to the 18:1 gear heads on the steppers for a 22.5:1 final ratio before the worm/wheels at 144:1
                                     
                                     // PEC, number of steps for a complete worm rotation (in RA), (StepsPerDegreeAxis1*360)/gear_reduction2.  Ignored on Alt/Azm mounts.
#define StepsPerWormRotationAxis1 12800L
                                     // G11              : (12800*360)/360 = 12800

#define PECBufferSize           824  // PEC, buffer size, max should be no more than 3384, your required buffer size >= StepsPerAxis1WormRotation/(StepsPerDegeeAxis1/240)
                                     // for the most part this doesn't need to be changed, but adjust when needed.  824 seconds is the default.  Ignored on Alt/Azm mounts.

#define REVERSE_AXIS1_OFF            // reverse the direction of movement for the HA/RA axis, adjust as needed or reverse your wiring so things move in the right direction
#define REVERSE_AXIS2_OFF            // reverse the direction of movement for the Dec axis (both reversed for my EM10b, both normal for G11)

#define MinutesPastMeridianE     -30 // for goto's, how far past the meridian to allow before we do a flip (if on the East side of the pier) - one hour of RA is the default = 60.  Sometimes used for Fork mounts in Align mode.  Ignored on Alt/Azm mounts.
#define MinutesPastMeridianW      60 // as above, if on the West side of the pier.  If left alone, the mount will stop tracking when it hits the this limit.  Sometimes used for Fork mounts in Align mode.  Ignored on Alt/Azm mounts.
#define UnderPoleLimit            11 // maximum allowed hour angle (+/-) under the celestial pole. Default=12.  Ignored on Alt/Azm mounts.
                                     // If left alone, the mount will stop tracking when it hits this limit.  Valid range is 10 to 12 hours.
#define MinDec                   -91 // minimum allowed declination, default = -91 (off)  Ignored on Alt/Azm mounts.
#define MaxDec                   +91 // maximum allowed declination, default =  91 (off)  Ignored on Alt/Azm mounts.
                                     // For example, a value of +80 would stop gotos/tracking near the north celestial pole.
                                     // For a Northern Hemisphere user, this would stop tracking when the mount is in the polar home position but
                                     // that can be easily worked around by doing an alignment once and saving a park position (assuming a 
                                     // fork/yolk mount with meridian flips turned off by setting the minutesPastMeridian values to cover the whole sky)
#define MaxAzm                   180 // Alt/Az mounts only. +/- maximum allowed Azimuth, default =  180.  Allowed range is 180 to 360

// ADDITIONAL STEPPER DRIVER CONTROL: --------------------------------------------------------------------------------------

// Stepper driver Enable support is always on, just wire Enable to Pins 23 (Axis1) and 36 (Axis2) and OnStep will pull these HIGH (Teensy3.2 Pins 9,14)
// to disable stepper drivers on startup and when Parked or Homed.  An Align or UnPark will enable the drivers.  Adjust below if you need these pulled LOW to disable the drivers.
#define AXIS1_DISABLED_HIGH
#define AXIS2_DISABLED_HIGH
// For equatorial mounts, _ON powers down the Declination axis when it's not being used to help lower power use.  During low rate guiding (<=1x) the axis stays enabled
// for 10 minutes after any guide on either axis.  Otherwise, the Dec axis is disabled (powered off) 10 seconds after movement stops.
#define AUTO_POWER_DOWN_AXIS2_OFF

/* Stepper driver Mode control
// M0, M1, and M2 are on Pins 25,27, and 29 for RA (Teensy3.2 Pins 15,16,17.)  M0, M1, M2 are on Pins 34,32,30 for Dec (Teensy3.2 Pins 8,7,6.)
// values 0 to 7 (0b000 to 111): for example "#define AXIS1_MODE 4" is the same as "#define AXIS1_MODE 0b100" which sets M2 to HIGH, M1 to LOW, and M0 to LOW
//                                                                                                      / | \
//                                                                                                    M2  M1 M0
// DRV8825 or A4988 or RAPS128:
// use MODE_SWITCH_BEFORE_SLEW_OFF
// micro-stepping modes: 5=32x, 4=16x, 3=8x, 2=4x, 1=2x, 0=1x (RAPS128 also supports 6=64x, 7=128x)
//
// SilentStepStick TMC2100/2130 configurations (M0 is CFG1, M1 is CFG2, M2 is CFG3):
// use MODE_SWITCH_BEFORE_SLEW_ON
// I recommend keeping CFG3 and CFG2 open (not connected) CFG1 can then be pulled low for 16x micro-stepping (256x intpol) in spreadCycle mode (0b110000 = 48 = OPEN/OPEN/OUTPUT, ignore/ignore/LOW)
// or keep CFG3 and CFG1 open (not connected) and CFG2 can be pulled high for 4x micro-stepping (256x intpol) in spreadCycle mode (0b101010 = 42 = OPEN/OUTPUT/OPEN, ignore/HIGH/ignore)
//
// SilentStepStick TMC2130 SPI configurations:
// use MODE_SWITCH_BEFORE_SLEW_SPI.  Default operation in spreadCycle and with 256x interpolation on:
// AXISn_MODE and AXISn_MODE_GOTO can be set to 0-8 where 0=256x, 1=128x, 2=64x, 3=32x, 4=16x, 5=8x, 6=4x, 7=2x, 8=1x
// You can also turn stealthChop on (TMC_STEALTHCHOP) and/or disable 256x interpolation (TMC_NINTPOL.) For example 32x mode with stealthChop:
// AXIS1_MODE (3|TMC_STEALTHCHOP)
// Another option allows setting 50% power while tracking (TMC_LOWPWR.)  As above, with this option on too:
// AXIS1_MODE (3|TMC_STEALTHCHOP|TMC_LOWPWR)
*/
#define AXIS1_MODE 5                 // programs the RA/Az uStep mode M0/M1/M2, optional and default _OFF.
#define AXIS1_MODE_GOTO 5            // programs the RA/Az uStep mode M0/M1/M2, used during gotos, optional and default _OFF.
#define AXIS1_STEP_GOTO 1            // 1=goto mode is same as normal mode: for example if normal tracking mode is 32x and goto is 8x this would be 4
#define AXIS2_MODE 5                 // programs the Dec/Alt uStep mode M0/M1/M2, optional and default _OFF.
#define AXIS2_MODE_GOTO 5            // programs the Dec/Alt uStep mode M0/M1/M2, used during gotos, optional and default _OFF.
#define AXIS2_STEP_GOTO 1            // 1=goto mode is same as normal mode: for example if normal tracking mode is 32x and goto is 8x this would be 4
#define MODE_SWITCH_BEFORE_SLEW_OFF  // _ON for _MODE and _MODE_GOTO settings to start/stop just before/after the slew, otherwise they are active during the slew at <128uS/step speeds)
                                     // _SPI as above but uses SPI (on M0/M1/M2/Aux) to do the switching (TMC2130.)  Uses Teensy3.2 Pins 18 (Aux1) and 5 (Aux2,) choose only one feature on Aux1/2.

// Secondary stepper driver decay control (for both Axis, the _DECAY_MODE and _DECAY_MODE_GOTO settings always start/stop just before/after the slew)
// typically used for the DRV8825 or A9488 where decay control is seperate from the micro-step mode control.  The driver modules usually need to be modified to accomplish this.
// Axis1 decay mode is on Pin 41 and Axis2 decay mode is on Pin 40.  Options are _HIGH, _LOW, _OPEN, default is _OFF (not supported on Teensy3.2)
// MODE_SWITCH_BEFORE_SLEW must be _OFF if using this.
#define DECAY_MODE_OFF
#define DECAY_MODE_GOTO_OFF

// if the decay/micro-step mode switch happens before/after a slew, inserts a 3ms delay before the motors take a step
#define MODE_SWITCH_SLEEP_ON

// Stepper driver Fault detection, just wire the driver Fault signal to Pins 39 (Axis1) and 38 (Axis2), default=OFF.  Teensy3.2 Pins 18 (Aux1) and 5 (Aux2,) choose only one feature to use on Aux1/2.
// other settings are LOW, HIGH, SPI (Teensy3.2 applies internal pullup if _LOW and pulldown if _HIGH.)  The SPI interface (on M0/M1/M2/Aux) can be used to detect errors on the TMC2130.
#define AXIS1_FAULT_OFF
#define AXIS2_FAULT_OFF

// THAT'S IT FOR USER CONFIGURATION!

// -------------------------------------------------------------------------------------------------------------------------

