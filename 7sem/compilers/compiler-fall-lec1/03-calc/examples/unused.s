	.text
	.file	"calc.expr"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movl	$.Lx.str, %edi
	callq	calc_read@PLT
	movl	%eax, %ebx
	movl	$.Ly.str, %edi
	callq	calc_read@PLT
	movl	%eax, %ebp
	movl	$.Lunused.str, %edi
	callq	calc_read@PLT
	addl	%ebx, %ebp
	movl	%ebp, %edi
	callq	calc_write@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.Lx.str,@object                 # @x.str
	.section	.rodata,"a",@progbits
.Lx.str:
	.asciz	"x"
	.size	.Lx.str, 2

	.type	.Ly.str,@object                 # @y.str
.Ly.str:
	.asciz	"y"
	.size	.Ly.str, 2

	.type	.Lunused.str,@object            # @unused.str
.Lunused.str:
	.asciz	"unused"
	.size	.Lunused.str, 7

	.section	".note.GNU-stack","",@progbits
