	.data
	
	.equ	BLUE, 0
	.equ	RED, 1
	.equ	GREEN, 2
	.equ 	YELLOW, 3
	
	.equ	BLUE_LED, 0x20000
	.equ	YELLOW_LED, 0x40000
	.equ	RED_LED, 0x8000000
	.equ	GREEN_LED, 0x10000 	
	
	.equ	BLUE_BUTTON, 22
	.equ	YELLOW_BUTTON, 23
	.equ	RED_BUTTON, 24
	.equ	GREEN_BUTTON, 25
	
	.equ	WAIT_DELAY, 0x50	

	.equ	LONG_DELAY, 0x10000000
	.equ	MEDIUM_MEDIUM_LONG_DELAY, 0x2000000
	.equ	MEDIUM_DELAY, 1000
	.equ	SHORT_DELAY, 50
	
	.equ	DISP_DELAY, 100
	
	.equ	BUTTON_DELAY, 0x10000

	.equ	FLASH_DELAY, 0x1000000
	.equ	FLASH_COUNT, 5
	
	.equ	GPFSEL0,   0x0000
	.equ	GPFSEL1,   0x0004
	.equ	GPFSEL2,   0x0008
	.equ	GPFSEL3,   0x000C
	.equ	GPFSEL4,   0x0010
	.equ	GPFSEL5,   0x0014
	.equ	GPSET0,    0x001C
	.equ	GPSET1,    0x0020
	.equ	GPCLR0,    0x0028	
	.equ	GPCLR1,    0x002c	
	.equ	GPLEV0,    0x0034

	.equ	GPPUD,     0x0094
	.equ	GPPUDCLK0, 0x0098
 	.equ	GPPUDCLK1, 0x009C 
 	
 	 int:
 	.asciz	"%d\n"
 	.align	2	
 
 blueStr:
 	.asciz	 "aplay /home/pi/Dropbox-Uploader/CSC314/P2/E4.wav"
 	.align	2
 yellowStr:
 	.asciz	 "aplay /home/pi/Dropbox-Uploader/CSC314/P2/C#5.wav"
 	.align	2
 greenStr:
 	.asciz	"aplay /home/pi/Dropbox-Uploader/CSC314/P2/E5.wav"
 	.align	2
 redStr:
 	.asciz	"aplay /home/pi/Dropbox-Uploader/CSC314/P2/A4.wav"
 	.align	2
success:
	 .asciz	"aplay /home/pi/Dropbox-Uploader/CSC314/P2/Party_Horn_Sound_Effect.wav"
	.align	2
fail:
	.asciz	"aplay /home/pi/Dropbox-Uploader/CSC314/P2/Raspberry.wav"
	.align 	2
 	 	
	.text

/********************************************************************/
	.globl	setup
setup:
	stmfd	sp!, {lr}
	
	mov	r0, #0
	bl		time
	bl		srand
	
	bl		IO_init
	
	@ led outputs
	mov	r0, #16	@ green LED
	bl	gpio_dir_output 
	mov	r0,#17 @ blue LED
	bl	gpio_dir_output
	mov	r0,#18	@ yellow LED
	bl	gpio_dir_output
	mov	r0,#27	@ red LED
	bl	gpio_dir_output
		
	@ button inputs
	mov	r0,#BLUE_BUTTON	@ blue button
	bl	gpio_dir_input
	mov	r0,#YELLOW_BUTTON	@ yellow button
	bl	gpio_dir_input
	mov	r0,#RED_BUTTON	@ red buton
	bl	gpio_dir_input	
	mov	r0, #GREEN_BUTTON	@ green button
	bl	gpio_dir_input
	
	mov	r0,#BLUE_BUTTON
	mov	r1,#2
	bl	set_pud

	mov	r0,#YELLOW_BUTTON
	mov	r1,#2
	bl	set_pud

	mov	r0,#GREEN_BUTTON
	mov	r1,#2
	bl	set_pud
	
	mov	r0, #RED_BUTTON
	mov	r1, #2
	bl	set_pud
	
	ldmfd	sp!, {pc}

/********************************************************************/
@ displays Blue LED
	.globl	dispBlue
dispBlue:
	stmfd	sp!, {r4, lr}
	mov	r4, r0
	
	cmp	r4, #BLUE
	bleq	blueOn
	bleq	blueSound
	
	cmp	r4, #YELLOW
	bleq	blueSound
		
	cmp	r4, #RED
	bleq	blueOn
	moveq	r0, #LONG_DELAY
	bleq	delay

	mov	r0, #DISP_DELAY
	bl		delay	
	
	bl		blueOff
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	ldmfd	sp!, {r4, pc}
@@@@@@@@@@
@ turns blue LED on
	.globl	blueOn
blueOn:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #BLUE_LED
	
	str		r1, [r0, #GPCLR0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@
@ turns blue LED off	
	.globl blueOff
blueOff:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #BLUE_LED
	
	str		r1, [r0, #GPSET0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl	blueSound	
blueSound:
	stmfd	sp!, {lr}
	
	ldr		r0, =blueStr
	bl		system
	
	ldmfd	sp!, {pc}
			
/********************************************************************/
@ displays Red LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl	dispRed
dispRed:
	stmfd	sp!, {r4-r5, lr}
	mov	r4, r0
	mov	r5, r0
	
	cmp	r4, #BLUE
	bleq	redOn
	bleq	redSound
	
	cmp	r4, #YELLOW
	bleq	redSound
		
	cmp	r4, #RED
	bleq	redOn
	moveq	r0, #LONG_DELAY
	bleq	delay
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	bl		redOff
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	ldmfd	sp!, {r4-r5, pc}
@@@@@@@@@@
	.globl	redOn	
redOn:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #RED_LED
	
	str		r1, [r0, #GPCLR0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@
	.globl	redOff	
redOff:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #RED_LED
	
	str		r1, [r0, #GPSET0]
	
	ldmfd	sp!, {pc}	
@@@@@@@@@@
	.globl	redSound	
redSound:
	stmfd	sp!, {lr}
	
	ldr		r0, =redStr
	bl		system	

	ldmfd	sp!, {pc}	
	
/********************************************************************/
@displays Green LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl	dispGreen
dispGreen:
	stmfd	sp!, {r4,lr}
	mov	r4, r0	
	
	cmp	r4, #BLUE
	bleq	greenOn
	bleq	greenSound
	
	cmp	r4, #YELLOW
	bleq	greenSound
		
	cmp	r4, #RED
	bleq	greenOn
	moveq	r0, #LONG_DELAY
	bleq	delay
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	bl		greenOff
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	ldmfd	sp!, {r4, pc}
@@@@@@@@@@
	.globl	greenOn	
greenOn:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #GREEN_LED
	
	str		r1, [r0, #GPCLR0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl	greenOff
greenOff:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #GREEN_LED
	
	str		r1, [r0, #GPSET0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl	greenSound
greenSound:
	stmfd	sp!, {lr}
	
	ldr		r0, =greenStr
	bl		system

	ldmfd	sp!, {pc}	
	
/********************************************************************/
@ displays Yellow LED.  if r0 is not equal to 0, it will play the appropriate sound
	.globl	dispYellow
dispYellow:
	stmfd	sp!, {r4, lr}
	mov	r4, r0
	
	cmp	r4, #BLUE
	bleq	yellowOn
	bleq	yellowSound
	
	cmp	r4, #YELLOW
	bleq	yellowSound
		
	cmp	r4, #RED
	bleq	yellowOn
	moveq	r0, #LONG_DELAY
	bleq	delay
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	bl		yellowOff
	
	mov	r0, #DISP_DELAY
	bl		delay	
	
	ldmfd	sp!, {r4, pc}
@@@@@@@@@@	
	.globl	yellowOn
yellowOn:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #YELLOW_LED
	
	str		r1, [r0, #GPCLR0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@	
	.globl	yellowOff
yellowOff:
	stmfd	sp!, {lr}
	
	ldr		r0, =gpiobase
	ldr		r0, [r0]
	
	mov	r1, #YELLOW_LED
	
	str		r1, [r0, #GPSET0]
	
	ldmfd	sp!, {pc}
@@@@@@@@@@
	.globl	yellowSound	
yellowSound:
	stmfd	sp!, {lr}
	
	ldr		r0, =yellowStr
	bl		system
	
	ldmfd	sp!, {pc}	
	
/********************************************************************/
/*	Display's a color to an LCD.  Color is in r0.
		void dispColor ( int color, int mode );
*/
	.globl	dispColor
dispColor:
	stmfd	sp!, {lr}
	
	cmp	r0, #RED
	moveq	r0, r1
	bleq	dispRed
	beq		_dispColor_end
	
	cmp	r0, #BLUE
	moveq	r0, r1
	bleq	dispBlue
	beq		_dispColor_end
	
	cmp	r0, #GREEN
	moveq	r0, r1
	bleq	dispGreen
	beq		_dispColor_end
	
	cmp	r0, #YELLOW
	moveq	r0, r1
	bleq	dispYellow
	
_dispColor_end:	
		
		
	ldmfd	sp!, {pc}
	
/********************************************************************/	
@ r0 = # of long delays	
	.globl	delay
delay:
	stmfd	sp!,{lr}

	mov	r1, #WAIT_DELAY

_wait:
	subs	r1, r1, #1
	bcc		_wait
	
	sub		r0, r0, #1
	cmp	r0, #0
	movgt	r1, #WAIT_DELAY
	bgt		_wait

	ldmfd	sp!, {pc}
	
/********************************************************************/
/* returns the color number of the button pressed*/
	.globl	getButton
getButton:
	stmfd	sp!, {r4, lr}
	mov	r3, r0
	ldr		r2, =gpiobase
	ldr		r2, [r2]
	
_button_loop:

	ldr		r1, [r2, #GPLEV0]
	
	tst		r1, #(1 << 22)
	moveq	r0, #BLUE
	beq 	_buttonloop2
	
	tst		r1, #(1 <<25)
	moveq	r0, #GREEN
	beq		_buttonloop2
	
	tst		r1, #(1 << 23)
	moveq	r0, #YELLOW
	beq		_buttonloop2
	
	tst		r1, #(1 << 24)
	moveq	r0, #RED
	beq		_buttonloop2
	
	b		_button_loop
	
_buttonloop2:
	ldr		r1, [r2, #GPLEV0]
	
	tst		r1, #(1 << 22)
	beq		_buttonloop2
	
	tst 		r1, #(1<<23)
	beq		_buttonloop2
	
	tst		r1, #(1<<24)
	beq		_buttonloop2
	
	tst		r1, #(1<<25)
	beq		_buttonloop2
	
_button_end:
	mov	r4, r0
	mov	r1, r3
	bl	dispColor
	
	mov	r0, #MEDIUM_DELAY
	bl		delay
	mov	r0, r4
	
	ldmfd	sp!, {r4, pc}

/********************************************************************/
	.globl	correctSound
correctSound:
	stmfd	sp!, {lr}

	ldr		r0, =success
	bl		system

	ldmfd	sp!, {pc}
	
	.globl	incorrectSound
incorrectSound:
	stmfd	sp!, {lr}
	
	ldr		r0, =fail
	bl		system
	
	ldmfd	sp!, {pc}


/********************************************************************/
	.globl	flashLEDs
flashLEDs:
	stmfd	sp!, {r4, lr}
	
	mov	r4, #FLASH_COUNT
_flash_loop:
	
	bl		blueOn	
	bl		redOn
	bl		yellowOn
	bl		greenOn
		
	mov	r0, #FLASH_DELAY
	bl		delay
		
	bl		blueOff
	bl		redOff
	bl		yellowOff	
	bl		greenOff

	mov	r0, #FLASH_DELAY
	bl		delay
		
	sub		r4, r4, #1
	cmp	r4, #0
	bgt		_flash_loop
	
	ldmfd	sp!, {r4, pc}
	
	.globl	displayLEDs
displayLEDs:
	stmfd	sp!, {r4, lr}
	
	mov	r4, r0
	
	mov	r0, r4
	bl		dispBlue
	mov	r0, #SHORT_DELAY
	bl		delay

	mov	r0, r4
	bl		dispRed
	mov	r0, #SHORT_DELAY
	bl		delay
	
	mov	r0, r4
	bl		dispYellow
	mov	r0, #SHORT_DELAY
	bl		delay

	mov	r0, r4
	bl		dispGreen
	mov	r0, #SHORT_DELAY
	bl		delay
	
	ldmfd	sp!, {r4, pc}


/********************************************************************/
