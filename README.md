# ASL Hand

## Overview

**ASL Hand** is a robotics project designed to bridge the gap between Large Language Models (LLMs) and the Deaf and Hard of Hearing community. The goal of this project is to allow users to communicate with AI systems through **American Sign Language (ASL)** and receive responses through a **robotic hand capable of signing back**.

While conversational AI has rapidly advanced, accessibility for sign language users has not been a primary design consideration. This project aims to address that gap by creating a low-cost, open-source robotic hand platform capable of interpreting and reproducing ASL gestures.

This repository contains the software and hardware control infrastructure required to drive a robotic ASL hand using servo-actuated fingers. The companion project responsible for **computer vision-based sign language interpretation and LLM integration** can be found here:

[sign-language-interpreter repository](https://github.com/MiddleSender45/sign-language-interpreter.git?utm_source=chatgpt.com)


<img width="3213" height="5712" alt="IMG_9224 (1)" src="https://github.com/user-attachments/assets/0376661b-2455-4627-8e88-a6f768659e68" />


---

## Features

* Control of a robotic hand using PWM-driven actuators
* Support for standard servo motors and linear actuators
* Finger position sensing using flex resistors
* Integration with Arduino-compatible microcontrollers
* Expandable architecture for ASL gesture playback
* Designed to interface with AI-powered sign language recognition systems

---

## Hardware Requirements

### Actuation

* 4 × PQ12 linear actuators *(or any PWM-compatible servo motors)*

### Control Electronics

* 1 × Arduino-compatible microcontroller
* 1 × PCA9685 PWM controller board

### Sensors

* 4 × Flex resistors
* 4 × 10kΩ (or greater) resistors

### User Interface

* 2 × Push buttons

### Power

* External power supply appropriate for the selected actuators

### Miscellaneous

* Breadboard
* Jumper wires
* Optional 3D-printed hand components

---

## System Architecture

The complete ASL communication pipeline consists of two major components:

### 1. Sign Language Interpretation

A computer vision system detects and classifies user ASL gestures, then forwards the interpreted text to a Large Language Model.

### 2. Robotic Sign Language Generation

This repository receives the generated response and converts it into motor commands that drive a robotic hand capable of reproducing ASL gestures.

```
User Signs
     ↓
Computer Vision Model
     ↓
Text Interpretation
     ↓
Large Language Model
     ↓
ASL Translation
     ↓
Robotic Hand Controller
     ↓
Physical Sign Language Output
```

---

## Repository Purpose

This repository specifically contains:

* Robotic hand control software
* Servo and actuator control logic
* Finger position sensing
* Hardware integration code
* ASL gesture playback infrastructure

The machine learning, computer vision, and LLM interaction pipeline are maintained separately.

---

## Future Development

Planned improvements include:

* Full ASL alphabet support
* Dynamic gesture transitions
* Word-level signing optimization
* Improved finger trajectory interpolation
* Additional degrees of freedom
* Bidirectional conversational interfaces
* Expanded accessibility features

---

## Motivation

Communication accessibility remains an underexplored area of artificial intelligence. By combining computer vision, robotics, and large language models, this project aims to create a platform where sign language users can interact with AI systems using their native mode of communication.

This project is open-source to encourage collaboration, experimentation, and further development of accessible human-AI interfaces.

---

## License

This project is distributed under the license provided in this repository.
