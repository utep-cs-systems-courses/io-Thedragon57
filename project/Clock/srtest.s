	.arch msp430g2553
	.p2align 1,0
	.text

	;;  routines to access sr

	.global set_srtest
set_srtest: nop
	mov r12, r2
	nop
	ret

	.global get_srtest
get_srtest: mov r2, r12
	ret

	.global or_srtest
or_srtest: nop
	bis r12, r2
	nop
	ret

	.global and_srtest
and_srtest: nop
	and r12, r2
	nop
	ret
