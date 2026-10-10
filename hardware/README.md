# Hardware notes

This directory is reserved for hardware-related documentation, prototype notes, and circuit-related materials.

## Current project status

The hardware is still being assembled and evaluated. The final circuit layout and full pin map remain pending.

## Known current setup

The current known hardware includes:
- ESP32
- SH1106 128×64 OLED
- MPU6050
- soil moisture sensor
- rain sensor
- vibration sensor
- LEDs
- buzzer

The current confirmed I²C setup is:
- SDA: GPIO21
- SCL: GPIO22

This applies to the OLED and MPU6050 in the current test setup.

## Important caution

No final circuit diagram or final sensor pin assignments are claimed here. This directory is intended for documentation of the evolving prototype rather than a completed hardware blueprint.

## Related documentation

- [Project overview](../docs/project-overview.md)
- [Hardware components](../docs/components.md)
- [Wiring and circuit notes](../docs/wiring-and-circuit.md)
