# Zephyr RTOS Sensor Pipeline (Simulation)

A real-time embedded systems project built with Zephyr RTOS and tested in simulation using native targets.  
This project demonstrates task scheduling, inter-thread communication, synchronization, and sensor data flow without requiring physical hardware.

## Overview

This application simulates a sensor monitoring pipeline where one thread periodically produces sensor readings and another thread consumes/processes the data.

The goal of the project is to showcase core RTOS concepts commonly used in embedded systems:

- Multithreading
- Periodic tasks
- Producer-consumer design pattern
- Thread synchronization
- Deterministic timing
- Logging and debugging
- Hardware-independent validation using simulation

## Features

- Periodic producer thread generates simulated sensor values
- Consumer thread receives and processes data
- FIFO / queue-based inter-thread communication
- Real-time scheduling using Zephyr kernel APIs
- Structured logs for debugging and verification
- Portable design for future hardware deployment

## Technologies Used

- Zephyr RTOS
- C
- West build system
- Native simulation target
- VS Code

## Project Structure

```text
.
├── src/
│   └── main.c
├── prj.conf
├── CMakeLists.txt
└── README.md
