# embedded_control_nxp

**Controller Area Networking (CAN)**

 Implemented over 7 lab stations over CAN network of NXP S32K144 • Networking protocol used in time-critical applications •  Messages have unique identifiers: priorities •  Allows computation of worst case response time 
- Implemented virtual wall remotely
- Estimated network utilization 
- Virtual “daisy chain” 

**Autocode Generation (I)**

Derive a mathematical model of system to be controlled •  Develop a Simulink/Stateflow model of the system. •  Design and test a control algorithm using this model. •  Using Simulink Coder to generate C-code. •
- Multitasking – with RTOS, task states – without RTOS, nested interrupts 
- Motor Control Toolbox 
- Multirate Simulation for Code Generation 
- Device Drivers 
    - Read encoder and translate to	
  degrees
    - Convert torque to duty cycle and write to PWM
    

**Interrupt Timing and PWM Frequency Analysis**

Use interrupt timer to generate a time step for numerical differentiation and integration •  Periodically modulate duty cycle of a 20kHz PWM signal by writing an ISR that either –  Samples 100 hz sine wave.  –  Calls C sine function –  Uses lookup table •  Time ISR by toggling a bit •  Filter PWM signal to remove     20kHz switching frequency

**Virtual Spring-Mass System**

Virtual spring-mass system: reaction force F = k(w-z) •  Measure z, must obtain w by numerical integration •  Use interrupt timer to generate a time step

**Quadrature Decoding**

•  Optical encoder attached to motor generates two 90° out of phase square waves:  
•  QD function on NXP S32K144 eTimer:     decodes quadrature signal into counter •  CPU must read counter before overflow

**A/D Conversion**

•  Uses ADC on the NXP SK32K144 •  Acquire analog input from potentiometer or signal generator •  Measure time required for one conversion by toggling bit •  Investigate aliasing •  Software oscilloscope: 


 **Familiarization and Digital I/O**

•  Use General Purpose Input/Output (GPIO) on NXP SK32K144  •  Use “union” command to write C code to perform bit manipulations •  Read two 4-bit numbers set by dipswitches –  add and display on LEDS 



**Pulse Width Modulation •**  
Drive DC motor with a PWM signal –  Switching frequency 20 kHz –  Duty cycle 40% –  FlexPWM peripheral on NXP SK32K144 

