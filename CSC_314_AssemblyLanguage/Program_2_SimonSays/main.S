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
 	 	
 mode:
 	.word	0
 	.align	2
 	 	
	.text

	.globl	main
main:
	stmfd	sp!, {r4-r11, lr}

	bl		setup
	mov	r11, sp
	
	@@@@@@@@@@@@@@@@@@@@@@@@
	@			Choose Mode
	@@@@@@@@@@@@@@@@@@@@@@@@
	@	BLUE - 0 = REGULAR
	@	RED - 1 = NO SOUND
	@	YELLOW - 2 = NO LIGHTS
	
	mov	r0, #0
	bl		getButton
	mov	r10, r0
	
	@@@@@@@@@@@@@@@@@@@@@@@@
	@			Flash Lights - All   
	@@@@@@@@@@@@@@@@@@@@@@@@

_main_flash:
	mov	r0, r10
	bl		flashLEDs

	@@@@@@@@@@@@@@@@@@@@@@@@
	@			Delay   
	@@@@@@@@@@@@@@@@@@@@@@@@
	mov	r0, #LONG_DELAY
	bl		delay

	@@@@@@@@@@@@@@@@@@@@@@@@
	@			Flash Lights - Individual   
	@@@@@@@@@@@@@@@@@@@@@@@@
_start:			
	mov	r0, r10
	bl		displayLEDs	
	
	mov	r0, #LONG_DELAY
	bl		delay
	
	@@@@@

	@@@@@@@@@@@@@@@@@@@@@@@@
	@			Run Game
	@@@@@@@@@@@@@@@@@@@@@@@@
	@	r4 = static counter of number of items
	@    r5 = dynamic counter of number of items
	@	r6 = save of the color to check against
	
	mov	r4, #0

_new_num:

	bl		rand
	and		r0, r0, #3	@ thanks to Aaron
	
	@ create a spot on the stack for the new number
	add		r4, r4, #1
	
	@ store the new number
	stmfd	sp!, {r0}
	
	mov	r5, r4
	
	@ run game
_run_through:
	sub		r5, r5, #1	
	cmp	r5, #0
	movlt	r5, r4
	blt		_play
	
	lsl		r7, r5, #2
	ldr		r0, [sp, r7]
	
	mov	r1, r10
	bl		dispColor
	
	mov	r0, #MEDIUM_MEDIUM_LONG_DELAY
	bl		delay
	
	bl		blueOff
	bl		greenOff
	bl		redOff
	bl		yellowOff
	
	b		_run_through	
_play:
	@ check to see if all numbers have been checked
	bl		blueOff
	bl		greenOff
	bl		redOff
	bl		yellowOff
	
	sub		r5, r5, #1	
	cmp	r5, #0
	blt		_correct	
	
	lsl		r7, r5, #2
	ldr		r6, [sp, r7]
	
	mov	r0, r10
	bl		getButton
	mov	r8, r0
	
	mov	r0, #BUTTON_DELAY
	bl		delay
	
	cmp	r8, r6
	bne		_incorrect
	beq		_play
	
_correct:
	mov	r0, #MEDIUM_MEDIUM_LONG_DELAY
	bl		delay
	bl	correctSound
	bl	flashLEDs
	b	_new_num
	
_incorrect:
	mov	r0,#MEDIUM_MEDIUM_LONG_DELAY
	bl		delay
	
	bl	incorrectSound
	bl	flashLEDs
	bl	flashLEDs
	bl	flashLEDs

_reset:
	mov	sp, r11
	b		_start
	
	
	ldmfd	sp!, {r4-r11, pc}
	
/********************************************************************/
