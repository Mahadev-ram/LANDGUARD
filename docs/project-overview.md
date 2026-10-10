# Project overview

## Purpose

LANDGUARD is a low-cost ESP32-based prototype designed to monitor several indicators that may help detect conditions related to landslide risk. The project combines environmental sensing and motion detection with an embedded system that can display data and raise alerts.

The goal is not to create a certified monitoring platform, but to provide a practical learning prototype for exploring how low-cost embedded electronics can be used to observe terrain-related risk indicators.

## Problem addressed

Landslides often develop from conditions that include:
- saturation of the soil
- persistent rainfall
- slope instability
- ground vibration or sudden displacement
- changes in local terrain orientation

A low-cost system can help researchers, makers, and students examine sensor combinations and alert logic in a controlled environment before investing in more advanced or field-rated monitoring systems.

## Objectives

The project aims to:
- observe soil moisture conditions
- detect rain-related signals
- monitor vibration and motion events
- detect acceleration or tilt changes with an MPU6050
- display system status and sensor readings
- provide alerts using LEDs and a buzzer
- keep the design low-cost and easy to prototype

## System concept

The current concept is to use an ESP32 as the primary controller, with multiple sensors connected for data acquisition. Readings are intended to be processed locally and then displayed on a small OLED display, with passive or active alert behavior for abnormal conditions.

This prototype is expected to support:
- simple sensor acquisition
- basic display output
- prototypes for threshold logic
- future expansion to logging or telemetry

## Current stage of development

This project is in the early integration phase. The hardware modules are being reviewed individually before final integration. Some sensors may be tested separately, and the combined system still needs validation.

Important:
- hardware integration is still in progress
- firmware is not yet finalized
- thresholds are not yet verified
- no field deployment claims are being made

## Scope

This repository documents the project at an early stage and focuses on:
- project explanation
- component documentation
- working principle
- hardware notes
- testing context
- known limitations
- future development opportunities

## Relationship to real-world monitoring

LANDGUARD is a prototype and educational tool, not a certified early-warning system. It should not be treated as a replacement for professional landslide monitoring equipment, engineering judgment, or field-validated hazard analysis.

## References within this repository

- [Hardware components](components.md)
- [Working principle](working-principle.md)
- [Wiring and circuit notes](wiring-and-circuit.md)
- [Testing status and results](testing-results.md)
- [Limitations and future scope](limitations-and-future-scope.md)
