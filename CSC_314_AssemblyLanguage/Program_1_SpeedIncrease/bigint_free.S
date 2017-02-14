	
	@bigint_free function
	@Author: Lyndon Engel

	.equ	 bi_blks,0	@ offset to block pointer
	.equ	bi_size,4	@ offset to size int
	.equ	bi_struct_sz,8	@ size of the bigint struct

	.equ	NULL,0

	.text
	.global	bigint_free
        .type	bigint_free, %function

bigint_free:

	stmfd    sp!,{r4-r11,lr}
	
	ldr	r6,[r0,#bi_blks] @load b->blks into r6
	mov	r5,r0		 @move b into r5
	cmp	r5,#NULL	 @compare r5 to NULL
	bne	.next		 @if not equal go to next

.next:	
	cmp	r6,#NULL	 @compare r6 to NULL
	bne	.next2		 @if not equal go to next2

.next2:
	mov	r0,r6		 @move r6 into r0 and free
	bl	free
	mov	r0,r5		 @move r5 into r0 and free
	bl	free

	ldmfd    sp!, {r4-r11,pc} @return
