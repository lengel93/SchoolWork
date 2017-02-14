	
	@Unsigned Multiply
	@Author: Lyndon Engel
	



	.equ	bi_blks,0	@ offset to block pointer
	.equ	bi_size,4	@ offset to size int
	.equ	bi_struct_sz,8	@ size of the bigint struct

	.equ	NULL,0

	.text
	.global	bigint_mul_uint
        .type	bigint_mul_uint, %function
	
bigint_mul_uint:

	stmfd	sp!,{r4-r11,lr}	    @store everything

	ldr	r11, [r0, #bi_size] @load size into r11
	ldr	r10, [r0, #bi_blks] @load memory address of l
	mov	r9,r1		    @mov r into r9

	add	r0,r11,#1	    @add one to size
	bl	bigint_alloc	    @allocate a new array
	mov	r6,r0		    @Store the new array in r6
	
	ldr	r8,[r6,#bi_blks]    @create a pointer to the array

	mov	r0,#0		    @move 0 into the first spot of the array
	
	str	r0,[r8,r0,lsl#2]    @store the 0

	mov	r5,#0	   	    @set counter to 0

.loop:
	@@ r2  : lower bits
	@@ r3  : upper bits
	@@ r4  : used for solutions/place holders
	@@ r5  : i
	@@ r6  : contains sum array
	@@ r8  : contains the pointer to the sum array
	@@ r9  : holds r
	@@ r10 : holds l memory address
	@@ r11 : holds size of l
	
	ldr	r4,[r10,r5,lsl#2]	@loading value of l into r4
	
	umull	r2,r3,r9,r4	 	@unsigned multiply r2-lowerbits r3-higher bits

	ldr	r4,[r8,r5,lsl#2] 	@loading sum value into r4

	add	r2,r2,r4	 	@Add lowerbits in r2 to sum value in r4

	str	r2,[r8,r5,lsl#2] 	@store the sum above back into the array

	add	r4,r5,#1	 	@Increase array position

	str	r3,[r8,r4,lsl#2] 	@stores higherbits in next array spot

	add	r5,r5,#1		@increment counter

	cmp	r5,r11			@compare counter to size

	blt	.loop			@loop if less than
	
	mov	r0,r6			@move sum array into r0

	ldmfd	sp!,{r4-r11,pc}		@return
	
	.size   bigint_mul_uint, .-bigint_mul_uint
	
	

	

