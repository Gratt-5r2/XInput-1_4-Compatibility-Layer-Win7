# XInput compatibility layer for Windows 7
A simple XInput proxy library for applications that depend on XInput 1.4.
This library allows these applications to run on Windows 7 by providing partial compatibility via XInput 1.1-1.3.
Or if these libraries are missing, this proxy can work as a placeholder, allowing the program to run even without a gamepad functions.

# XInput version comparison
Functions from version 1.4 will work in older versions if they are matched in the following list.  
|              v1.1              |              v1.2              |              v1.3              |             v1.4              |
|--------------------------------|--------------------------------|--------------------------------|-------------------------------|
|**XInputEnable**                |**XInputEnable**                |**XInputEnable**                |**XInputEnable**               |
|**XInputGetState**              |**XInputGetState**              |**XInputGetState**              |**XInputGetState**             |
|**XInputSetState**              |**XInputSetState**              |**XInputSetState**              |**XInputSetState**             |
|**XInputGetCapabilities**       |**XInputGetCapabilities**       |**XInputGetCapabilities**       |**XInputGetCapabilities**      |
|XInputGetDSoundAudioDeviceGuids |XInputGetDSoundAudioDeviceGuids |XInputGetDSoundAudioDeviceGuids |---                            |
|---                             |---                             |**XInputGetBatteryInformation** |**XInputGetBatteryInformation**|
|---                             |---                             |**XInputGetAudioDeviceIds**     |**XInputGetAudioDeviceIds**    |
|---                             |---                             |---                             |**XInputGetKeystroke**         |

# License
This library is licensed under [MIT license](https://github.com/Gratt-5r2/XInput-1_4-Compatibility-Layer-Win7/blob/master/LICENSE.txt)
