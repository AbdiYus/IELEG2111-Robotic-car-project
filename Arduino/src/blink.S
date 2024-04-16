#define __SFR_OFFSET 0x00
#include "avr/io.h"
;------------------------
.global start
.global led
;------------------------
start:
    SBI   DDRB, 6             ;sett PB4 (D12) som utgang
    RET                       ;returner til setup()-funksjonen
;---------------------------------------------------------------------------
led:
    CPI   R24, 0x00           ;verdien i R24 gitt av kalleren sammenlignet med 0
    BREQ  ledOFF              ;hopp (branch) hvis lik til underprosedyren ledOFF
    SBI   PORTB, 6            ;sett D12 til høy
    RCALL myDelay
    RET                       ;returner til loop()-funksjonen
;---------------------------------------------------------------------------
ledOFF:
    CBI   PORTB, 6            ;sett D12 til lav
    RCALL myDelay
    RET                       ;returner til loop()-funksjonen
;---------------------------------------------------------------------------
.equ  delayVal, 10000         ;initial tellerverdi for indre løkke
;---------------------------------------------------------------------------
myDelay:
    LDI   R20, 100            ;initial tellerverdi for ytre løkke
outerLoop:
    LDI   R30, lo8(delayVal)  ;lav byte av delayVal i R30
    LDI   R31, hi8(delayVal)  ;høy byte av delayVal i R31
innerLoop:
    SBIW  R30, 1              ;trekk 1 fra 16-bits verdien i R31, R30
    BRNE  innerLoop           ;hopp hvis countVal ikke er lik 0
    ;--------------
    SUBI  R20, 1              ;trekk 1 fra R20
    BRNE  outerLoop           ;hopp hvis R20 ikke er lik 0
    RET
;---------------------------------------------------------------------------
