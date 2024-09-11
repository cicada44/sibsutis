	.text
	.file	"calc.expr"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$.Lx.str, %edi
	callq	calc_read@PLT
	movl	%eax, %ebx
	movl	$.Ly.str, %edi
	callq	calc_read@PLT
	movl	%eax, %ecx
	movl	%ebx, %eax
	imull	%ecx, %eax
	subl	%ebx, %ecx
	cltd
	idivl	%ecx
	movl	%eax, %edi
	callq	calc_write@PLT
	xorl	%eax, %eax
	popq	%rbx
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

	.section	".note.GNU-stack","",@progbits
