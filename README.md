# CAN-Based Automotive Dashboard

A real-time automotive dashboard system simulating ECU communication across a CAN bus network on the PIC18F4580 microcontroller. Three ECU nodes exchange speed, RPM, gear position, and turn-indicator data over a shared bus, replicating the data-flow architecture of real automotive embedded systems under strict timing and error-handling requirements.

## Features

- 3-node simulated ECU network communicating over a shared CAN bus
- Real-time transmission of speed, RPM, gear position, and turn indicators
- Interrupt-driven firmware architecture
- Register-level CAN module configuration with acceptance filters and masks
- Character LCD dashboard display with flicker-free refresh via hardware timers
- Bus-off fault and frame-error recovery

## Technologies Used

- Embedded C
- PIC18F4580
- CAN Protocol (Controller Area Network)
- GPIO, Timers
- Interrupt-Driven Architecture
- Character LCD Interfacing
- Register-Level Peripheral Configuration

## Hardware Used

- 3× PIC18F4580 microcontroller boards (one per ECU node)
- CAN transceiver modules (e.g. MCP2551) with bus wiring and 120Ω termination resistors
- Character LCD per node for dashboard display
- Sensors/switches simulating speed, RPM, gear, and turn-indicator inputs
- Crystal oscillators + standard power supply per node

## Folder Structure

```
CAN_AUTOMATIVE_DASHBOARD/
├── ECU_1.X/                # Node 1 — RPM + speed sensing, transmits over CAN
│   ├── main.c
│   ├── can.c / can.h
│   ├── adc.c / adc.h
│   ├── dkp.c / dkp.h        # Drive/gear keypad input
│   ├── ECU1_sensor.h
│   ├── msg_id.h              # Shared CAN message IDs (SPEED/GEAR/RPM/INDICATOR)
│   ├── Makefile
│   └── nbproject/
├── ECU_2.X/                # Node 2 — gear + turn-indicator sensing, transmits over CAN
│   ├── main.c
│   ├── can.c / can.h
│   ├── adc.c / adc.h
│   ├── dkp.c / dkp.h
│   ├── ECU2_sensor.h
│   ├── msg_id.h
│   ├── Makefile
│   └── nbproject/
└── ECU_3.X/                # Node 3 — receives CAN frames, drives the LCD dashboard
    ├── main.c
    ├── can.c / can.h
    ├── clcd.c / clcd.h
    ├── isr.c
    ├── message_handler.c / message_handler.h
    ├── timer.c / timer.h
    ├── msg_id.h
    ├── Makefile
    └── nbproject/
```

> Each `ECU_*.X` folder is its own MPLAB X project (also produces its own `build/`/`dist/` output, omitted above — worth `.gitignore`-ing).

## How to Build / Run

1. In **MPLAB X IDE**, open each of `ECU_1.X`, `ECU_2.X`, and `ECU_3.X` as separate projects (`File → Open Project`, pointing at each folder). All three target **PIC18F4580** with the XC8 compiler.
2. Build each project individually (`Production → Build Main Project`) to generate its `dist/default/production/ECU_n.X.production.hex`.
3. Flash each `.hex` to its own PIC18F4580 board via tinymultibootloader — `ECU_1.X`/`ECU_2.X` are the sensor nodes, `ECU_3.X` is the display node.
4. Wire all three boards onto a shared CAN bus (CANH/CANL) through CAN transceivers, with 120Ω termination resistors at both ends.
5. Connect the character LCD only to the `ECU_3.X` board and power on all three nodes simultaneously.
6. Observe live speed/RPM/gear/turn-indicator values updating on the LCD as `ECU_1.X`/`ECU_2.X` transmit CAN frames that `ECU_3.X` receives and renders.

## Key Learnings

- Resolved CAN bus-off fault states and frame errors by precisely matching baud rates and message IDs across all nodes, achieving stable continuous multi-node communication.
- Configured the PIC18F4580 CAN module at register level, setting acceptance filters and masks so each node received only its designated message IDs, eliminating spurious message processing.
- Interfaced a character LCD for real-time dashboard display, managing refresh timing via hardware timers to prevent flickering under continuous data updates.

## Demo / Output

*Add a photo or video of the three boards running together, with the LCDs showing live synchronized dashboard values.*
