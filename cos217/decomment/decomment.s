	.cpu generic+fp+simd
	.file	"decomment.c"
	.text
	.align	2
	.global	handleNormal
	.type	handleNormal, %function
handleNormal:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	x1, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 47
	bne	.L2
	mov	w0, 1
	str	w0, [x29,44]
	b	.L3
.L2:
	ldr	w0, [x29,28]
	cmp	w0, 34
	bne	.L4
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
	b	.L3
.L4:
	ldr	w0, [x29,28]
	cmp	w0, 39
	bne	.L5
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
	b	.L3
.L5:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L6
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	ldr	x0, [x29,16]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,16]
	str	w1, [x0]
	b	.L3
.L6:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
.L3:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE0:
	.size	handleNormal, .-handleNormal
	.align	2
	.global	handleStartComment
	.type	handleStartComment, %function
handleStartComment:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,44]
	str	x1, [x29,32]
	str	x2, [x29,24]
	ldr	w0, [x29,44]
	cmp	w0, 42
	bne	.L9
	mov	w0, 32
	bl	putchar
	mov	w0, 2
	str	w0, [x29,60]
	ldr	x0, [x29,32]
	ldr	w1, [x0]
	ldr	x0, [x29,24]
	str	w1, [x0]
	b	.L10
.L9:
	ldr	w0, [x29,44]
	cmp	w0, 10
	bne	.L11
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,44]
	bl	putchar
	str	wzr, [x29,60]
	ldr	x0, [x29,32]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,32]
	str	w1, [x0]
	b	.L10
.L11:
	ldr	w0, [x29,44]
	cmp	w0, 47
	bne	.L12
	mov	w0, 47
	bl	putchar
	mov	w0, 1
	str	w0, [x29,60]
	b	.L10
.L12:
	ldr	w0, [x29,44]
	cmp	w0, 34
	bne	.L13
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,44]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,60]
	b	.L10
.L13:
	ldr	w0, [x29,44]
	cmp	w0, 39
	bne	.L14
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,44]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,60]
	b	.L10
.L14:
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,44]
	bl	putchar
	str	wzr, [x29,60]
.L10:
	ldr	w0, [x29,60]
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE1:
	.size	handleStartComment, .-handleStartComment
	.align	2
	.global	handleInComment
	.type	handleInComment, %function
handleInComment:
.LFB2:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	x1, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L17
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 2
	str	w0, [x29,44]
	ldr	x0, [x29,16]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,16]
	str	w1, [x0]
	b	.L18
.L17:
	ldr	w0, [x29,28]
	cmp	w0, 42
	bne	.L19
	mov	w0, 3
	str	w0, [x29,44]
	b	.L18
.L19:
	mov	w0, 2
	str	w0, [x29,44]
.L18:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE2:
	.size	handleInComment, .-handleInComment
	.align	2
	.global	handleEndComment
	.type	handleEndComment, %function
handleEndComment:
.LFB3:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,44]
	str	x1, [x29,32]
	str	x2, [x29,24]
	ldr	w0, [x29,44]
	cmp	w0, 10
	bne	.L22
	ldr	w0, [x29,44]
	bl	putchar
	mov	w0, 2
	str	w0, [x29,60]
	ldr	x0, [x29,32]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,32]
	str	w1, [x0]
	b	.L23
.L22:
	ldr	w0, [x29,44]
	cmp	w0, 42
	bne	.L24
	mov	w0, 3
	str	w0, [x29,60]
	b	.L23
.L24:
	ldr	w0, [x29,44]
	cmp	w0, 47
	bne	.L25
	ldr	x0, [x29,24]
	str	wzr, [x0]
	str	wzr, [x29,60]
	b	.L23
.L25:
	mov	w0, 2
	str	w0, [x29,60]
.L23:
	ldr	w0, [x29,60]
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE3:
	.size	handleEndComment, .-handleEndComment
	.align	2
	.global	handleInString
	.type	handleInString, %function
handleInString:
.LFB4:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	x1, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 34
	bne	.L28
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	b	.L29
.L28:
	ldr	w0, [x29,28]
	cmp	w0, 92
	bne	.L30
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 5
	str	w0, [x29,44]
	b	.L29
.L30:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L31
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
	ldr	x0, [x29,16]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,16]
	str	w1, [x0]
	b	.L29
.L31:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
.L29:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE4:
	.size	handleInString, .-handleInString
	.align	2
	.global	handleBackslashInString
	.type	handleBackslashInString, %function
handleBackslashInString:
.LFB5:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	x1, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L34
	ldr	x0, [x29,16]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,16]
	str	w1, [x0]
.L34:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE5:
	.size	handleBackslashInString, .-handleBackslashInString
	.align	2
	.global	handleInChar
	.type	handleInChar, %function
handleInChar:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	x1, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 39
	bne	.L37
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	b	.L38
.L37:
	ldr	w0, [x29,28]
	cmp	w0, 92
	bne	.L39
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 7
	str	w0, [x29,44]
	b	.L38
.L39:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L40
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
	ldr	x0, [x29,16]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,16]
	str	w1, [x0]
	b	.L38
.L40:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
.L38:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE6:
	.size	handleInChar, .-handleInChar
	.align	2
	.global	handleBackslashInChar
	.type	handleBackslashInChar, %function
handleBackslashInChar:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	x1, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L43
	ldr	x0, [x29,16]
	ldr	w0, [x0]
	add	w1, w0, 1
	ldr	x0, [x29,16]
	str	w1, [x0]
.L43:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE7:
	.size	handleBackslashInChar, .-handleBackslashInChar
	.section	.rodata
	.align	3
.LC0:
	.string	"Error: line %d: unterminated comment\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB8:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	mov	w0, 1
	str	w0, [x29,32]
	str	wzr, [x29,28]
	str	wzr, [x29,40]
	b	.L46
.L56:
	ldr	w0, [x29,36]
	str	w0, [x29,44]
	ldr	w0, [x29,40]
	cmp	w0, 7
	bhi	.L46
	adrp	x1, .L48
	add	x1, x1, :lo12:.L48
	ldr	w2, [x1,w0,uxtw #2]
	adr	x3, .Lrtx48
	add	x2, x3, w2, sxtw #2
	br	x2
.Lrtx48:
	.section	.rodata
	.align	0
	.align	2
.L48:
	.word	(.L47 - .Lrtx48) / 4
	.word	(.L49 - .Lrtx48) / 4
	.word	(.L50 - .Lrtx48) / 4
	.word	(.L51 - .Lrtx48) / 4
	.word	(.L52 - .Lrtx48) / 4
	.word	(.L53 - .Lrtx48) / 4
	.word	(.L54 - .Lrtx48) / 4
	.word	(.L55 - .Lrtx48) / 4
	.text
.L47:
	add	x1, x29, 32
	ldr	w0, [x29,36]
	bl	handleNormal
	str	w0, [x29,40]
	b	.L46
.L49:
	add	x1, x29, 32
	add	x2, x29, 28
	ldr	w0, [x29,36]
	bl	handleStartComment
	str	w0, [x29,40]
	b	.L46
.L50:
	add	x1, x29, 32
	ldr	w0, [x29,36]
	bl	handleInComment
	str	w0, [x29,40]
	b	.L46
.L51:
	add	x1, x29, 32
	add	x2, x29, 28
	ldr	w0, [x29,36]
	bl	handleEndComment
	str	w0, [x29,40]
	b	.L46
.L52:
	add	x1, x29, 32
	ldr	w0, [x29,36]
	bl	handleInString
	str	w0, [x29,40]
	b	.L46
.L53:
	add	x1, x29, 32
	ldr	w0, [x29,36]
	bl	handleBackslashInString
	str	w0, [x29,40]
	b	.L46
.L54:
	add	x1, x29, 32
	ldr	w0, [x29,36]
	bl	handleInChar
	str	w0, [x29,40]
	b	.L46
.L55:
	add	x1, x29, 32
	ldr	w0, [x29,36]
	bl	handleBackslashInChar
	str	w0, [x29,40]
	nop
.L46:
	bl	getchar
	str	w0, [x29,36]
	ldr	w0, [x29,36]
	cmn	w0, #1
	bne	.L56
	ldr	w0, [x29,44]
	cmp	w0, 47
	bne	.L57
	ldr	w0, [x29,44]
	bl	putchar
.L57:
	ldr	w0, [x29,28]
	cmp	w0, wzr
	beq	.L58
	adrp	x0, stderr
	add	x0, x0, :lo12:stderr
	ldr	x0, [x0]
	ldr	w2, [x29,28]
	adrp	x1, .LC0
	add	x1, x1, :lo12:.LC0
	bl	fprintf
	mov	w0, 1
	bl	exit
.L58:
	mov	w0, 0
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",%progbits
