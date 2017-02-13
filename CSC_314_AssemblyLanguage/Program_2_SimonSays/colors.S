.data
	
	.equ	BLUE, 0
	.equ	RED, 1
	.equ	GREEN, 2
	.equ 	YELLOW, 3
	
	.equ	LONG_DELAY, 0x10000000
	
	.equ	DISP_DELAY, 0x10000
	.equ	FLASH_DELAY, 0x10000
	
	.text

/********************************************************************/
/* displays Blue LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl dispBlue
dispBlue:
	stmfd	sp!, {lr}
	
	bl		blueOn
	
	cmp	r0, #0
	bleq	blueSound
	
	mov	r0, #DISP_DELAY
	b		delay	
	
	bl		blueOff
	
	ldmfd	sp!, {pc}
@@@@@@@@@@
@ turns blue LED on
	.globl blueOn
blueOn:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {lr}
@@@@@@@@@@
@ turns blue LED off	
	.globl blueOff
blueOff:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {lr}
@@@@@@@@@@	
	.globl blueSound	
blueSound:
	stmfd	sp!, {lr}
	
	bl		playBlue
	
	ldmfd	sp!, {pc}
			
/********************************************************************/
/* displays Red LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl dispRed
dispRed:
	stmfd	sp!, {lr}
	
	bl		redOn
	
	cmp	r0, #0
	bleq	redSound
	
	mov	r0, #DISP_DELAY
	b		delay	
	
	bl		redOff
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl redOn
redOn:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
redOff:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {pc}	
@@@@@@@@@@	
	.globl redSound
redSound:
	stmfd	sp!, {lr}
	
	bl		playRed	

	ldmfd	sp!, {pc}	
	
/********************************************************************/
/* displays Green LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl dispGreen
dispGreen:
	stmfd	sp!, {lr}
	
	bl		greenOn
	
	cmp	r0, #0
	bleq	greenSound
	
	mov	r0, #DISP_DELAY
	b		delay	
	
	bl		greenOff
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl greenOn
greenOn:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {lr}
@@@@@@@@@@	
greenOff:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl greenSound
greenSound:
	stmfd	sp!, {lr}
	
	bl		playGreen

	ldmfd	sp!, {pc}	
	
/********************************************************************/
/* displays Yellow LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl dispYellow
dispYellow:
	stmfd	sp!, {lr}
	
	bl		yellowOn
	
	cmp	r0, #0
	bleq	yellowSound
	
	mov	r0, #DISP_DELAY
	b		delay	
	
	bl		yellowOff
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl yellowOn
yellowOn:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl yellowOff
yellowOff:
	stmfd	sp!, {lr}
	
	ldmfd	sp!, {pc}
@@@@@@@@@@
	.globl yellowSound	
yellowSound:
	stmfd	sp!, {lr}
	
	bl		playYellow
	
	ldmfd	sp!, {pc}	
	
/********************************************************************/
/*	Display's a color to an LCD.  Color is in r0.
		void dispColor ( int color );
*/
	.globl dispColor
dispColor:
	stmfd	sp!, {lr}
	
	cmp	r0, #RED
	bleq	dispRed
	beq		_dispColor_end
	
	cmp	r0, #BLUE
	bleq	dispBlue
	beq		_dispColor_end
	
	cmp	r0, #GREEN
	bleq	dispBlue
	beq		_dispColor_end
	
	cmp	r0, #YELLOW
	bleq	dispYellow
	
_dispColor_end:	
		
		
	ldmfd	sp!, {pc}
	
