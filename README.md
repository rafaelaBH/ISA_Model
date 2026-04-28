# ISA Temperature Model (0–25 km)

## Overview

This project implements a temperature model based on the **International Standard Atmosphere (ISA)**.
The model calculates air temperature as a function of altitude above sea level.

The implementation is written in **C++**, with an additional **Python script** used for visualization and validation.

---

## Features

* Piecewise implementation of ISA temperature model:

  * Troposphere (0–11 km)
  * Tropopause (11–20 km)
  * Stratosphere (20–25 km)
* Supports multiple altitude units:

  * Kilometers (km)
  * Meters (m)
  * Feet (ft)
* Automatic unit detection from input files
* CSV output generation for analysis
* Graph visualization using Python (matplotlib)

---

## Model Description

The ISA model defines temperature variation with altitude:

* **Troposphere (0–11 km)**
  Temperature decreases linearly:
  [
  T = 15 - 6.5h
  ]

* **Tropopause (11–20 km)**
  Temperature is constant:
  [
  T = -56.5
  ]

* **Stratosphere (20–25 km)**
  Temperature increases linearly:
  [
  T = -56.5 + (h - 20)
  ]

Where:

* (T) is temperature in °C
* (h) is altitude in kilometers

---

## Assumptions and Limitations

* Model is valid for altitudes between **0–25 km**
* Standard atmospheric conditions are assumed
* Temperature depends only on altitude (no weather effects)
* Inputs outside the valid range return `NaN`

---
