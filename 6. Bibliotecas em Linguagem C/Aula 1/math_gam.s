	.build_version macos, 26, 0	sdk_version 27, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_math_clamp                     ; -- Begin function math_clamp
	.p2align	2
_math_clamp:                            ; @math_clamp
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	s0, [sp, #8]
	str	s1, [sp, #4]
	str	s2, [sp]
	ldr	s0, [sp, #8]
	ldr	s1, [sp, #4]
	fcmp	s0, s1
	b.pl	LBB0_2
	b	LBB0_1
LBB0_1:
	ldr	s0, [sp, #4]
	str	s0, [sp, #12]
	b	LBB0_5
LBB0_2:
	ldr	s0, [sp, #8]
	ldr	s1, [sp]
	fcmp	s0, s1
	b.le	LBB0_4
	b	LBB0_3
LBB0_3:
	ldr	s0, [sp]
	str	s0, [sp, #12]
	b	LBB0_5
LBB0_4:
	ldr	s0, [sp, #8]
	str	s0, [sp, #12]
	b	LBB0_5
LBB0_5:
	ldr	s0, [sp, #12]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_math_colisao_circulos          ; -- Begin function math_colisao_circulos
	.p2align	2
_math_colisao_circulos:                 ; @math_colisao_circulos
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	s0, [x29, #-4]
	stur	s1, [x29, #-8]
	stur	s2, [x29, #-12]
	str	s3, [sp, #16]
	str	s4, [sp, #12]
	str	s5, [sp, #8]
	ldur	s0, [x29, #-4]
	ldur	s1, [x29, #-8]
	ldr	s2, [sp, #16]
	ldr	s3, [sp, #12]
	bl	_calcular_distancia_quadrada
	str	s0, [sp, #4]
	ldur	s0, [x29, #-12]
	ldr	s1, [sp, #8]
	fadd	s0, s0, s1
	str	s0, [sp]
	ldr	s0, [sp, #4]
	ldr	s1, [sp]
	ldr	s2, [sp]
	fmul	s1, s1, s2
	fcmp	s0, s1
	cset	w0, ls
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function calcular_distancia_quadrada
_calcular_distancia_quadrada:           ; @calcular_distancia_quadrada
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	s0, [sp, #28]
	str	s1, [sp, #24]
	str	s2, [sp, #20]
	str	s3, [sp, #16]
	ldr	s0, [sp, #20]
	ldr	s1, [sp, #28]
	fsub	s0, s0, s1
	str	s0, [sp, #12]
	ldr	s0, [sp, #16]
	ldr	s1, [sp, #24]
	fsub	s0, s0, s1
	str	s0, [sp, #8]
	ldr	s0, [sp, #12]
	ldr	s1, [sp, #12]
	ldr	s2, [sp, #8]
	ldr	s3, [sp, #8]
	fmul	s2, s2, s3
	fmadd	s0, s0, s1, s2
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
