# mark_description "Intel(R) C Intel(R) 64 Compiler XE for applications running on Intel(R) 64, Version 14.0 Build 20131008";
# mark_description "-S -align -Ofast -march=native -lfftw3 -restrict -vec-report=2 -O2";
	.file "spect.c"
	.text
..TXTST0:
# -- Begin  mkwi
# mark_begin;
       .align    16,0x90
	.globl mkwi
mkwi:
..B1.1:                         # Preds ..B1.0
..___tag_value_mkwi.1:                                          #9.12
        pushq     %rbp                                          #9.12
..___tag_value_mkwi.3:                                          #
        movq      %rsp, %rbp                                    #9.12
..___tag_value_mkwi.4:                                          #
        andq      $-32, %rsp                                    #9.12
        xorb      %dil, %dil                                    #12.3
        movl      $-4, %eax                                     #12.3
        xorl      %esi, %esi                                    #
        vmovdqu   .L_2il0floatpacket.0(%rip), %xmm12            #12.3
        vmovupd   .L_2il0floatpacket.1(%rip), %ymm11            #14.29
        vmovupd   .L_2il0floatpacket.2(%rip), %ymm10            #14.29
        vmovd     %eax, %xmm0                                   #12.3
        vpshufd   $0, %xmm0, %xmm13                             #12.3
        vmovupd   .L_2il0floatpacket.3(%rip), %ymm9             #14.36
        vmovupd   .L_2il0floatpacket.4(%rip), %ymm14            #13.16
        vmovupd   .L_2il0floatpacket.5(%rip), %ymm8             #13.19
                                # LOE rbx rsi r12 r13 r14 r15 dil xmm12 xmm13 ymm8 ymm9 ymm10 ymm11 ymm14
..B1.2:                         # Preds ..B1.6 ..B1.1
        vcvtdq2pd %xmm12, %ymm1                                 #14.27
        vaddpd    %ymm1, %ymm10, %ymm2                          #14.29
        vmulpd    %ymm2, %ymm11, %ymm0                          #14.33
        call      __svml_sin4                                   #14.17
                                # LOE rbx rsi r12 r13 r14 r15 dil xmm12 xmm13 ymm0 ymm8 ymm9 ymm10 ymm11 ymm14
..B1.6:                         # Preds ..B1.2
        vmovapd   %ymm0, %ymm2                                  #14.17
        addb      $4, %dil                                      #12.3
        vmulpd    %ymm2, %ymm8, %ymm3                           #13.24
        vpaddd    %xmm13, %xmm12, %xmm12                        #13.5
        vmulpd    %ymm2, %ymm9, %ymm0                           #14.36
        vdivpd    %ymm3, %ymm14, %ymm4                          #13.24
        vextractf128 $1, %ymm0, %xmm1                           #14.5
        vextractf128 $1, %ymm4, %xmm5                           #13.5
        vmovlpd   %xmm0, 248+IWEIGHTS(%rsi)                     #14.5
        vmovhpd   %xmm0, 240+IWEIGHTS(%rsi)                     #14.5
        vmovlpd   %xmm1, 232+IWEIGHTS(%rsi)                     #14.5
        vmovhpd   %xmm1, 224+IWEIGHTS(%rsi)                     #14.5
        vmovlpd   %xmm4, 248+WEIGHTS(%rsi)                      #13.5
        vmovhpd   %xmm4, 240+WEIGHTS(%rsi)                      #13.5
        vmovlpd   %xmm5, 232+WEIGHTS(%rsi)                      #13.5
        vmovhpd   %xmm5, 224+WEIGHTS(%rsi)                      #13.5
        addq      $-32, %rsi                                    #12.3
        cmpb      $32, %dil                                     #12.3
        jb        ..B1.2        # Prob 82%                      #12.3
                                # LOE rbx rsi r12 r13 r14 r15 dil xmm12 xmm13 ymm8 ymm9 ymm10 ymm11 ymm14
..B1.3:                         # Preds ..B1.6
        vzeroupper                                              #16.1
        movq      %rbp, %rsp                                    #16.1
        popq      %rbp                                          #16.1
..___tag_value_mkwi.6:                                          #
        ret                                                     #16.1
        .align    16,0x90
..___tag_value_mkwi.8:                                          #
                                # LOE
# mark_end;
	.type	mkwi,@function
	.size	mkwi,.-mkwi
	.data
# -- End  mkwi
	.text
# -- Begin  plddx
# mark_begin;
       .align    16,0x90
	.globl plddx
plddx:
# parameter 1: %rdi
..B2.1:                         # Preds ..B2.0
..___tag_value_plddx.9:                                         #18.21
        pushq     %rbp                                          #18.21
..___tag_value_plddx.11:                                        #
        subq      $16, %rsp                                     #18.21
..___tag_value_plddx.13:                                        #
        movq      %rdi, %rbp                                    #18.21
        movl      $32, %edi                                     #21.12
        movl      $TY, %edx                                     #21.12
        movl      $5, %ecx                                      #21.12
        movl      $8, %r8d                                      #21.12
        movl      $5, (%rsp)                                    #19.27
        movq      (%rbp), %rsi                                  #21.12
        movl      $8, 4(%rsp)                                   #19.27
..___tag_value_plddx.14:                                        #21.12
        call      fftw_plan_r2r_1d                              #21.12
..___tag_value_plddx.15:                                        #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B2.2:                         # Preds ..B2.1
        movl      $32, %edi                                     #22.12
        movl      $TY+8, %esi                                   #22.12
        movl      $9, %r8d                                      #22.12
        movl      4(%rsp), %ecx                                 #22.12
        movq      8(%rbp), %rdx                                 #22.12
        movq      %rax, 16(%rbp)                                #21.4
..___tag_value_plddx.16:                                        #22.12
        call      fftw_plan_r2r_1d                              #22.12
..___tag_value_plddx.17:                                        #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B2.3:                         # Preds ..B2.2
        movq      %rax, 24(%rbp)                                #22.4
        addq      $16, %rsp                                     #23.1
..___tag_value_plddx.18:                                        #
        popq      %rbp                                          #23.1
..___tag_value_plddx.20:                                        #
        ret                                                     #23.1
        .align    16,0x90
..___tag_value_plddx.21:                                        #
                                # LOE
# mark_end;
	.type	plddx,@function
	.size	plddx,.-plddx
	.data
# -- End  plddx
	.text
# -- Begin  plint
# mark_begin;
       .align    16,0x90
	.globl plint
plint:
# parameter 1: %rdi
..B3.1:                         # Preds ..B3.0
..___tag_value_plint.22:                                        #25.21
        pushq     %rbp                                          #25.21
..___tag_value_plint.24:                                        #
        subq      $16, %rsp                                     #25.21
..___tag_value_plint.26:                                        #
        movq      %rdi, %rbp                                    #25.21
        movl      $9, %ecx                                      #27.11
        movl      $32, %edi                                     #27.11
        movl      $TY+8, %edx                                   #27.11
        movl      %ecx, %r8d                                    #27.11
        movl      $9, (%rsp)                                    #26.26
        movq      (%rbp), %rsi                                  #27.11
        movl      $4, 4(%rsp)                                   #26.26
..___tag_value_plint.27:                                        #27.11
        call      fftw_plan_r2r_1d                              #27.11
..___tag_value_plint.28:                                        #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B3.2:                         # Preds ..B3.1
        movl      $32, %edi                                     #28.11
        movl      $TY, %esi                                     #28.11
        movl      $9, %r8d                                      #28.11
        movl      4(%rsp), %ecx                                 #28.11
        movq      8(%rbp), %rdx                                 #28.11
        movq      %rax, 16(%rbp)                                #27.3
..___tag_value_plint.29:                                        #28.11
        call      fftw_plan_r2r_1d                              #28.11
..___tag_value_plint.30:                                        #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B3.3:                         # Preds ..B3.2
        movq      %rax, 24(%rbp)                                #28.3
        addq      $16, %rsp                                     #29.1
..___tag_value_plint.31:                                        #
        popq      %rbp                                          #29.1
..___tag_value_plint.33:                                        #
        ret                                                     #29.1
        .align    16,0x90
..___tag_value_plint.34:                                        #
                                # LOE
# mark_end;
	.type	plint,@function
	.size	plint,.-plint
	.data
# -- End  plint
	.text
# -- Begin  plintp
# mark_begin;
       .align    16,0x90
	.globl plintp
plintp:
# parameter 1: %rdi
..B4.1:                         # Preds ..B4.0
..___tag_value_plintp.35:                                       #31.22
        pushq     %rbp                                          #31.22
..___tag_value_plintp.37:                                       #
        subq      $16, %rsp                                     #31.22
..___tag_value_plintp.39:                                       #
        movq      %rdi, %rbp                                    #31.22
        movl      $32, %edi                                     #33.11
        movl      $TY+8, %edx                                   #33.11
        movl      $9, %ecx                                      #33.11
        movl      $8, %r8d                                      #33.11
        movl      $9, (%rsp)                                    #32.26
        movq      8(%rbp), %rsi                                 #33.11
        movl      $4, 4(%rsp)                                   #32.26
..___tag_value_plintp.40:                                       #33.11
        call      fftw_plan_r2r_1d                              #33.11
..___tag_value_plintp.41:                                       #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B4.2:                         # Preds ..B4.1
        movl      $32, %edi                                     #34.11
        movl      $TY, %esi                                     #34.11
        movl      $9, %r8d                                      #34.11
        movl      4(%rsp), %ecx                                 #34.11
        movq      8(%rbp), %rdx                                 #34.11
        movq      %rax, 16(%rbp)                                #33.3
..___tag_value_plintp.42:                                       #34.11
        call      fftw_plan_r2r_1d                              #34.11
..___tag_value_plintp.43:                                       #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B4.3:                         # Preds ..B4.2
        movq      %rax, 24(%rbp)                                #34.3
        addq      $16, %rsp                                     #35.1
..___tag_value_plintp.44:                                       #
        popq      %rbp                                          #35.1
..___tag_value_plintp.46:                                       #
        ret                                                     #35.1
        .align    16,0x90
..___tag_value_plintp.47:                                       #
                                # LOE
# mark_end;
	.type	plintp,@function
	.size	plintp,.-plintp
	.data
# -- End  plintp
	.text
# -- Begin  exddx
# mark_begin;
       .align    16,0x90
	.globl exddx
exddx:
# parameter 1: %rdi
..B5.1:                         # Preds ..B5.0
..___tag_value_exddx.48:                                        #37.21
        pushq     %rbp                                          #37.21
..___tag_value_exddx.50:                                        #
        movq      %rsp, %rbp                                    #37.21
..___tag_value_exddx.51:                                        #
        andq      $-32, %rsp                                    #37.21
        pushq     %r14                                          #37.21
        subq      $24, %rsp                                     #37.21
..___tag_value_exddx.53:                                        #
        movq      %rdi, %r14                                    #37.21
        vmovsd    32(%r14), %xmm0                               #38.12
        movq      16(%r14), %rdi                                #39.3
        vmovsd    %xmm0, (%rsp)                                 #38.12
..___tag_value_exddx.54:                                        #39.3
        call      fftw_execute                                  #39.3
..___tag_value_exddx.55:                                        #
                                # LOE rbx r12 r13 r14 r15
..B5.2:                         # Preds ..B5.1
        vmovsd    (%rsp), %xmm0                                 #43.3
        movl      $4, %eax                                      #46.5
        vmulsd    .L_2il0floatpacket.10(%rip), %xmm0, %xmm3     #43.3
        vmovsd    16+TY(%rip), %xmm5                            #45.8
        vmovd     %eax, %xmm10                                  #46.5
        vmovsd    24+TY(%rip), %xmm8                            #45.8
        movb      $3, %al                                       #44.3
        vmulsd    .L_2il0floatpacket.11(%rip), %xmm5, %xmm6     #46.5
        vsubsd    8+TY(%rip), %xmm3, %xmm4                      #45.5
        vmulsd    .L_2il0floatpacket.12(%rip), %xmm8, %xmm9     #46.5
        vmovupd   .L_2il0floatpacket.14(%rip), %ymm3            #46.12
        vsubsd    %xmm5, %xmm4, %xmm7                           #45.5
        vxorpd    %ymm2, %ymm2, %ymm2                           #38.11
        vsubsd    %xmm8, %xmm7, %xmm0                           #45.5
        vmovapd   %ymm2, %ymm1                                  #38.11
        vmovsd    %xmm6, 16+TY(%rip)                            #46.5
        vmovsd    %xmm9, 24+TY(%rip)                            #46.5
        vpshufd   $0, %xmm10, %xmm5                             #46.5
        vmovdqu   .L_2il0floatpacket.13(%rip), %xmm4            #46.5
                                # LOE rbx r12 r13 r14 r15 al xmm0 xmm4 xmm5 ymm1 ymm2 ymm3
..B5.3:                         # Preds ..B5.3 ..B5.2
        vcvtdq2pd %xmm4, %ymm7                                  #46.12
        movb      %al, %dl                                      #45.8
        vpaddd    %xmm5, %xmm4, %xmm4                           #46.5
        incb      %dl                                           #45.8
        addb      $4, %al                                       #44.3
        movzbl    %dl, %ecx                                     #45.8
        vcmpltpd  %ymm2, %ymm7, %ymm6                           #46.12
        vmovupd   TY(,%rcx,8), %ymm10                           #45.8
        vandpd    %ymm6, %ymm3, %ymm8                           #46.12
        vaddpd    %ymm8, %ymm7, %ymm9                           #46.12
        vsubpd    %ymm10, %ymm1, %ymm1                          #45.5
        vmulpd    %ymm10, %ymm9, %ymm11                         #46.5
        vmovupd   %ymm11, TY(,%rcx,8)                           #46.5
        cmpb      $31, %al                                      #44.3
        jb        ..B5.3        # Prob 82%                      #44.3
                                # LOE rbx r12 r13 r14 r15 al xmm0 xmm4 xmm5 ymm1 ymm2 ymm3
..B5.4:                         # Preds ..B5.3
        vextractf128 $1, %ymm1, %xmm2                           #38.11
        vaddpd    %xmm2, %xmm1, %xmm3                           #38.11
        vunpckhpd %xmm3, %xmm3, %xmm4                           #38.11
        vaddsd    %xmm4, %xmm3, %xmm5                           #38.11
        vaddsd    %xmm0, %xmm5, %xmm6                           #38.11
        vmovsd    .L_2il0floatpacket.15(%rip), %xmm0            #48.12
        vmulsd    TY(%rip), %xmm0, %xmm7                        #48.15
        vsubsd    %xmm7, %xmm6, %xmm8                           #48.15
        vmovsd    %xmm8, 256+TY(%rip)                           #48.3
        movq      24(%r14), %rdi                                #50.3
        vzeroupper                                              #50.3
..___tag_value_exddx.56:                                        #50.3
        call      fftw_execute                                  #50.3
..___tag_value_exddx.57:                                        #
                                # LOE rbx r12 r13 r14 r15
..B5.5:                         # Preds ..B5.4
        xorb      %al, %al                                      #53.3
        .align    16,0x90
                                # LOE rbx r12 r13 r14 r15 al
..B5.6:                         # Preds ..B5.6 ..B5.5
        movb      %al, %dil                                     #54.6
        addb      %al, %dil                                     #54.6
        incb      %al                                           #53.3
        negb      %dil                                          #54.6
        movb      %dil, %dl                                     #54.6
        addb      $30, %dil                                     #54.6
        addb      $31, %dl                                      #54.6
        movzbl    %dl, %esi                                     #54.6
        movq      8(%r14), %rcx                                 #54.6
        movzbl    %dil, %r9d                                    #54.6
        vmovsd    (%rcx,%rsi,8), %xmm0                          #54.6
        vmulsd    WEIGHTS(,%rsi,8), %xmm0, %xmm1                #54.6
        vmovsd    %xmm1, (%rcx,%rsi,8)                          #54.6
        movq      8(%r14), %r8                                  #54.6
        vmovsd    (%r8,%r9,8), %xmm2                            #54.6
        vmulsd    WEIGHTS(,%r9,8), %xmm2, %xmm3                 #54.6
        vmovsd    %xmm3, (%r8,%r9,8)                            #54.6
        cmpb      $16, %al                                      #53.3
        jb        ..B5.6        # Prob 63%                      #53.3
                                # LOE rbx r12 r13 r14 r15 al
..B5.7:                         # Preds ..B5.6
        addq      $24, %rsp                                     #56.1
..___tag_value_exddx.58:                                        #56.1
        popq      %r14                                          #56.1
        movq      %rbp, %rsp                                    #56.1
        popq      %rbp                                          #56.1
..___tag_value_exddx.59:                                        #
        ret                                                     #56.1
        .align    16,0x90
..___tag_value_exddx.61:                                        #
                                # LOE
# mark_end;
	.type	exddx,@function
	.size	exddx,.-exddx
	.data
# -- End  exddx
	.text
# -- Begin  exint
# mark_begin;
       .align    16,0x90
	.globl exint
exint:
# parameter 1: %rdi
..B6.1:                         # Preds ..B6.0
..___tag_value_exint.62:                                        #58.21
        pushq     %rbp                                          #58.21
..___tag_value_exint.64:                                        #
        movq      %rsp, %rbp                                    #58.21
..___tag_value_exint.65:                                        #
        andq      $-32, %rsp                                    #58.21
        pushq     %r13                                          #58.21
        subq      $24, %rsp                                     #58.21
        xorb      %dl, %dl                                      #69.3
..___tag_value_exint.67:                                        #
        movq      %rdi, %r13                                    #58.21
        xorl      %eax, %eax                                    #
        vmovsd    32(%r13), %xmm0                               #60.12
        .align    16,0x90
                                # LOE rax rbx r12 r13 r14 r15 dl xmm0
..B6.2:                         # Preds ..B6.2 ..B6.1
        movb      %dl, %cl                                      #69.20
        addb      %dl, %cl                                      #69.20
        incb      %dl                                           #69.3
        movzbl    %cl, %r8d                                     #69.20
        movq      (%r13), %rsi                                  #69.20
        vmovsd    (%rsi,%r8,8), %xmm1                           #69.20
        vmulsd    IWEIGHTS(%rax), %xmm1, %xmm2                  #69.20
        vmovsd    %xmm2, (%rsi,%r8,8)                           #69.20
        movq      (%r13), %rdi                                  #69.20
        vmovsd    8(%rdi,%r8,8), %xmm3                          #69.20
        vmulsd    8+IWEIGHTS(%rax), %xmm3, %xmm4                #69.20
        addq      $16, %rax                                     #69.3
        vmovsd    %xmm4, 8(%rdi,%r8,8)                          #69.20
        cmpb      $16, %dl                                      #69.3
        jb        ..B6.2        # Prob 93%                      #69.3
                                # LOE rax rbx r12 r13 r14 r15 dl xmm0
..B6.3:                         # Preds ..B6.2
        movq      16(%r13), %rdi                                #71.3
        vmovsd    %xmm0, (%rsp)                                 #71.3
..___tag_value_exint.68:                                        #71.3
        call      fftw_execute                                  #71.3
..___tag_value_exint.69:                                        #
                                # LOE rbx r12 r13 r14 r15
..B6.4:                         # Preds ..B6.3
        vmovsd    16+TY(%rip), %xmm2                            #75.5
        movl      $4, %eax                                      #76.5
        vmulsd    .L_2il0floatpacket.15(%rip), %xmm2, %xmm1     #75.5
        vmovsd    .L_2il0floatpacket.11(%rip), %xmm2            #76.8
        vxorpd    %xmm8, %xmm8, %xmm8                           #60.11
        vmulsd    %xmm1, %xmm2, %xmm3                           #76.10
        vmovd     %eax, %xmm7                                   #76.5
        vmovsd    (%rsp), %xmm0                                 #
        vxorps    %xmm11, %xmm11, %xmm11                        #60.11
        vmovsd    %xmm1, 16+TY(%rip)                            #75.5
        movl      $2, %eax                                      #74.3
        vpshufd   $0, %xmm7, %xmm1                              #76.5
        vsubsd    %xmm3, %xmm0, %xmm5                           #76.5
        vmovsd    24+TY(%rip), %xmm0                            #75.5
        vpcmpeqd  %xmm3, %xmm3, %xmm3                           #76.25
        vmulsd    .L_2il0floatpacket.17(%rip), %xmm0, %xmm4     #75.5
        vmulsd    %xmm4, %xmm2, %xmm6                           #76.10
        vmovsd    %xmm4, 24+TY(%rip)                            #75.5
        vaddsd    %xmm6, %xmm5, %xmm9                           #76.5
        vmovupd   .L_2il0floatpacket.18(%rip), %ymm5            #76.8
        vmovsd    %xmm9, %xmm8, %xmm10                          #60.11
        vmovdqu   .L_2il0floatpacket.13(%rip), %xmm0            #76.5
        vmovdqu   .L_2il0floatpacket.19(%rip), %xmm4            #76.22
        vinsertf128 $1, %xmm11, %ymm10, %ymm6                   #60.11
        .align    16,0x90
                                # LOE rax rbx r12 r13 r14 r15 xmm0 xmm1 xmm2 xmm3 xmm4 ymm5 ymm6
..B6.5:                         # Preds ..B6.5 ..B6.4
        vmovupd   16+TY(,%rax,8), %ymm7                         #75.5
        vpand     %xmm4, %xmm0, %xmm10                          #76.22
        vpslld    $1, %xmm10, %xmm11                            #76.22
        vcvtdq2pd %xmm0, %ymm8                                  #75.12
        vpaddd    %xmm3, %xmm11, %xmm12                         #76.25
        vcvtdq2pd %xmm12, %ymm14                                #76.25
        vpaddd    %xmm1, %xmm0, %xmm0                           #60.11
        vdivpd    %ymm8, %ymm7, %ymm9                           #75.5
        vmulpd    %ymm9, %ymm5, %ymm13                          #76.10
        vmovupd   %ymm9, 16+TY(,%rax,8)                         #75.5
        vmulpd    %ymm14, %ymm13, %ymm15                        #76.25
        addq      $4, %rax                                      #74.3
        vaddpd    %ymm15, %ymm6, %ymm6                          #76.5
        cmpq      $30, %rax                                     #74.3
        jb        ..B6.5        # Prob 82%                      #74.3
                                # LOE rax rbx r12 r13 r14 r15 xmm0 xmm1 xmm2 xmm3 xmm4 ymm5 ymm6
..B6.6:                         # Preds ..B6.5
        vmovsd    256+TY(%rip), %xmm5                           #75.5
        vmulsd    .L_2il0floatpacket.20(%rip), %xmm5, %xmm8     #75.5
        vmovsd    8+TY(%rip), %xmm7                             #78.13
        vmovsd    %xmm8, 256+TY(%rip)                           #75.5
        vsubsd    %xmm8, %xmm7, %xmm9                           #78.13
        vmulsd    %xmm2, %xmm9, %xmm2                           #78.13
        vextractf128 $1, %ymm6, %xmm0                           #60.11
        vaddpd    %xmm0, %xmm6, %xmm1                           #60.11
        vunpckhpd %xmm1, %xmm1, %xmm3                           #60.11
        vaddsd    %xmm3, %xmm1, %xmm4                           #60.11
        vaddsd    %xmm4, %xmm2, %xmm10                          #78.13
        vmovsd    %xmm10, TY(%rip)                              #78.3
        movq      24(%r13), %rdi                                #80.3
        vzeroupper                                              #80.3
        addq      $24, %rsp                                     #80.3
..___tag_value_exint.70:                                        #80.3
        popq      %r13                                          #80.3
        movq      %rbp, %rsp                                    #80.3
        popq      %rbp                                          #80.3
..___tag_value_exint.71:                                        #
        jmp       fftw_execute                                  #80.3
        .align    16,0x90
..___tag_value_exint.73:                                        #
                                # LOE
# mark_end;
	.type	exint,@function
	.size	exint,.-exint
	.data
# -- End  exint
	.text
# -- Begin  exintp
# mark_begin;
       .align    16,0x90
	.globl exintp
exintp:
# parameter 1: %rdi
..B7.1:                         # Preds ..B7.0
..___tag_value_exintp.74:                                       #83.22
        pushq     %rbp                                          #83.22
..___tag_value_exintp.76:                                       #
        movq      %rsp, %rbp                                    #83.22
..___tag_value_exintp.77:                                       #
        andq      $-32, %rsp                                    #83.22
        pushq     %r13                                          #83.22
        subq      $24, %rsp                                     #83.22
        xorb      %dl, %dl                                      #90.3
..___tag_value_exintp.79:                                       #
        movq      %rdi, %r13                                    #83.22
        xorl      %eax, %eax                                    #
        vmovsd    32(%r13), %xmm0                               #85.12
        vmovsd    %xmm0, (%rsp)                                 #85.12
        .align    16,0x90
                                # LOE rbx r12 r13 r14 r15 eax dl
..B7.2:                         # Preds ..B7.2 ..B7.1
        movzbl    %dl, %r8d                                     #91.22
        incb      %dl                                           #90.3
        movslq    %eax, %rax                                    #91.14
        shlq      $4, %r8                                       #91.5
        movq      (%r13), %rcx                                  #91.14
        negq      %r8                                           #91.5
        movq      8(%r13), %rsi                                 #91.5
        vmovsd    248(%rcx,%rax,8), %xmm0                       #91.14
        vmulsd    248+IWEIGHTS(%r8), %xmm0, %xmm1               #91.22
        vmovsd    %xmm1, 248(%rsi,%rax,8)                       #91.5
        movq      (%r13), %rdi                                  #91.14
        movq      8(%r13), %r9                                  #91.5
        vmovsd    240(%rdi,%rax,8), %xmm2                       #91.14
        vmulsd    240+IWEIGHTS(%r8), %xmm2, %xmm3               #91.22
        vmovsd    %xmm3, 240(%r9,%rax,8)                        #91.5
        addl      $-2, %eax                                     #90.3
        cmpb      $16, %dl                                      #90.3
        jb        ..B7.2        # Prob 63%                      #90.3
                                # LOE rbx r12 r13 r14 r15 eax dl
..B7.3:                         # Preds ..B7.2
        movq      16(%r13), %rdi                                #94.3
..___tag_value_exintp.80:                                       #94.3
        call      fftw_execute                                  #94.3
..___tag_value_exintp.81:                                       #
                                # LOE rbx r12 r13 r14 r15
..B7.4:                         # Preds ..B7.3
        vmovsd    16+TY(%rip), %xmm2                            #98.5
        movl      $4, %eax                                      #99.5
        vmulsd    .L_2il0floatpacket.15(%rip), %xmm2, %xmm0     #98.5
        vmovsd    .L_2il0floatpacket.11(%rip), %xmm2            #99.8
        vxorpd    %xmm9, %xmm9, %xmm9                           #85.11
        vmovsd    24+TY(%rip), %xmm4                            #98.5
        vmovd     %eax, %xmm8                                   #99.5
        vmulsd    %xmm0, %xmm2, %xmm3                           #99.10
        vxorps    %xmm12, %xmm12, %xmm12                        #85.11
        vmulsd    .L_2il0floatpacket.17(%rip), %xmm4, %xmm5     #98.5
        vmovsd    (%rsp), %xmm1                                 #99.5
        movl      $2, %eax                                      #97.3
        vmulsd    %xmm5, %xmm2, %xmm7                           #99.10
        vsubsd    %xmm3, %xmm1, %xmm6                           #99.5
        vmovsd    %xmm0, 16+TY(%rip)                            #98.5
        vpcmpeqd  %xmm3, %xmm3, %xmm3                           #99.25
        vmovsd    %xmm5, 24+TY(%rip)                            #98.5
        vaddsd    %xmm7, %xmm6, %xmm10                          #99.5
        vmovupd   .L_2il0floatpacket.18(%rip), %ymm5            #99.8
        vmovsd    %xmm10, %xmm9, %xmm11                         #85.11
        vpshufd   $0, %xmm8, %xmm1                              #99.5
        vmovdqu   .L_2il0floatpacket.13(%rip), %xmm0            #99.5
        vmovdqu   .L_2il0floatpacket.19(%rip), %xmm4            #99.22
        vinsertf128 $1, %xmm12, %ymm11, %ymm6                   #85.11
        .align    16,0x90
                                # LOE rax rbx r12 r13 r14 r15 xmm0 xmm1 xmm2 xmm3 xmm4 ymm5 ymm6
..B7.5:                         # Preds ..B7.5 ..B7.4
        vmovupd   16+TY(,%rax,8), %ymm7                         #98.5
        vpand     %xmm4, %xmm0, %xmm10                          #99.22
        vpslld    $1, %xmm10, %xmm11                            #99.22
        vcvtdq2pd %xmm0, %ymm8                                  #98.12
        vpaddd    %xmm3, %xmm11, %xmm12                         #99.25
        vcvtdq2pd %xmm12, %ymm14                                #99.25
        vpaddd    %xmm1, %xmm0, %xmm0                           #85.11
        vdivpd    %ymm8, %ymm7, %ymm9                           #98.5
        vmulpd    %ymm9, %ymm5, %ymm13                          #99.10
        vmovupd   %ymm9, 16+TY(,%rax,8)                         #98.5
        vmulpd    %ymm14, %ymm13, %ymm15                        #99.25
        addq      $4, %rax                                      #97.3
        vaddpd    %ymm15, %ymm6, %ymm6                          #99.5
        cmpq      $30, %rax                                     #97.3
        jb        ..B7.5        # Prob 82%                      #97.3
                                # LOE rax rbx r12 r13 r14 r15 xmm0 xmm1 xmm2 xmm3 xmm4 ymm5 ymm6
..B7.6:                         # Preds ..B7.5
        vmovsd    256+TY(%rip), %xmm5                           #98.5
        vmulsd    .L_2il0floatpacket.20(%rip), %xmm5, %xmm8     #98.5
        vmovsd    8+TY(%rip), %xmm7                             #101.13
        vmovsd    %xmm8, 256+TY(%rip)                           #98.5
        vsubsd    %xmm8, %xmm7, %xmm9                           #101.13
        vmulsd    %xmm2, %xmm9, %xmm2                           #101.13
        vextractf128 $1, %ymm6, %xmm0                           #85.11
        vaddpd    %xmm0, %xmm6, %xmm1                           #85.11
        vunpckhpd %xmm1, %xmm1, %xmm3                           #85.11
        vaddsd    %xmm3, %xmm1, %xmm4                           #85.11
        vaddsd    %xmm4, %xmm2, %xmm10                          #101.13
        vmovsd    %xmm10, TY(%rip)                              #101.3
        movq      24(%r13), %rdi                                #103.3
        vzeroupper                                              #103.3
        addq      $24, %rsp                                     #103.3
..___tag_value_exintp.82:                                       #103.3
        popq      %r13                                          #103.3
        movq      %rbp, %rsp                                    #103.3
        popq      %rbp                                          #103.3
..___tag_value_exintp.83:                                       #
        jmp       fftw_execute                                  #103.3
        .align    16,0x90
..___tag_value_exintp.85:                                       #
                                # LOE
# mark_end;
	.type	exintp,@function
	.size	exintp,.-exintp
	.data
# -- End  exintp
	.text
# -- Begin  plddxm
# mark_begin;
       .align    16,0x90
	.globl plddxm
plddxm:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %ecx
# parameter 5: %r8
# parameter 6: %r9
..B8.1:                         # Preds ..B8.0
..___tag_value_plddxm.86:                                       #111.84
        pushq     %r12                                          #111.84
..___tag_value_plddxm.88:                                       #
        pushq     %r13                                          #111.84
..___tag_value_plddxm.90:                                       #
        pushq     %r14                                          #111.84
..___tag_value_plddxm.92:                                       #
        pushq     %r15                                          #111.84
..___tag_value_plddxm.94:                                       #
        pushq     %rbx                                          #111.84
..___tag_value_plddxm.96:                                       #
        pushq     %rbp                                          #111.84
..___tag_value_plddxm.98:                                       #
        subq      $24, %rsp                                     #111.84
..___tag_value_plddxm.100:                                      #
        movl      $32, %ebp                                     #112.16
        movl      $8, %r10d                                     #113.26
        movl      %ecx, %ebx                                    #111.84
        movl      %ebp, 8(%rsp)                                 #112.16
        movq      %rdi, %rcx                                    #111.84
        movl      $5, (%rsp)                                    #113.26
        movl      $1, %edi                                      #114.7
        movl      %r10d, 4(%rsp)                                #113.26
        addq      $-64, %rsp                                    #114.7
..___tag_value_plddxm.101:                                      #
        movq      %rsi, %r12                                    #111.84
        movq      %r9, %r15                                     #111.84
        movq      %r8, %r14                                     #111.84
        movq      %rdx, %r13                                    #111.84
        movl      %ebx, %edx                                    #114.7
        lea       72(%rsp), %rsi                                #114.7
        movl      %ebp, (%rsp)                                  #114.7
        xorl      %r8d, %r8d                                    #114.7
        movq      %r12, 8(%rsp)                                 #114.7
        movl      %edi, %r9d                                    #114.7
        movq      $0, 16(%rsp)                                  #114.7
        lea       64(%rsp), %rax                                #114.7
        movl      $1, 24(%rsp)                                  #114.7
        movl      %ebp, 32(%rsp)                                #114.7
        movq      %rax, 40(%rsp)                                #114.7
        movl      %r10d, 48(%rsp)                               #114.7
..___tag_value_plddxm.102:                                      #114.7
        call      fftw_plan_many_r2r                            #114.7
..___tag_value_plddxm.103:                                      #
                                # LOE rax r12 r13 r14 r15 ebx ebp
..B8.2:                         # Preds ..B8.1
        addq      $8, %r12                                      #115.7
        movl      $1, %edi                                      #115.7
        lea       72(%rsp), %rsi                                #115.7
        movl      %ebx, %edx                                    #115.7
        movq      %r12, %rcx                                    #115.7
        xorl      %r8d, %r8d                                    #115.7
        movl      %edi, %r9d                                    #115.7
        movl      %ebp, (%rsp)                                  #115.7
        movq      %r13, 8(%rsp)                                 #115.7
        movq      $0, 16(%rsp)                                  #115.7
        movl      $1, 24(%rsp)                                  #115.7
        movq      %rax, (%r14)                                  #114.4
        lea       68(%rsp), %rax                                #115.7
        movl      %ebp, 32(%rsp)                                #115.7
        movq      %rax, 40(%rsp)                                #115.7
        movl      $9, 48(%rsp)                                  #115.7
..___tag_value_plddxm.104:                                      #115.7
        call      fftw_plan_many_r2r                            #115.7
..___tag_value_plddxm.105:                                      #
                                # LOE rax r15
..B8.3:                         # Preds ..B8.2
        movq      %rax, (%r15)                                  #115.4
        addq      $88, %rsp                                     #116.1
..___tag_value_plddxm.106:                                      #
        popq      %rbp                                          #116.1
..___tag_value_plddxm.108:                                      #
        popq      %rbx                                          #116.1
..___tag_value_plddxm.110:                                      #
        popq      %r15                                          #116.1
..___tag_value_plddxm.112:                                      #
        popq      %r14                                          #116.1
..___tag_value_plddxm.114:                                      #
        popq      %r13                                          #116.1
..___tag_value_plddxm.116:                                      #
        popq      %r12                                          #116.1
..___tag_value_plddxm.118:                                      #
        ret                                                     #116.1
        .align    16,0x90
..___tag_value_plddxm.119:                                      #
                                # LOE
# mark_end;
	.type	plddxm,@function
	.size	plddxm,.-plddxm
	.data
# -- End  plddxm
	.text
# -- Begin  plddxd
# mark_begin;
       .align    16,0x90
	.globl plddxd
plddxd:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %rcx
# parameter 5: %r8
..B9.1:                         # Preds ..B9.0
..___tag_value_plddxd.120:                                      #118.77
        pushq     %r13                                          #118.77
..___tag_value_plddxd.122:                                      #
        pushq     %r14                                          #118.77
..___tag_value_plddxd.124:                                      #
        pushq     %r15                                          #118.77
..___tag_value_plddxd.126:                                      #
        subq      $16, %rsp                                     #118.77
..___tag_value_plddxd.128:                                      #
        movq      %r8, %r15                                     #118.77
        movq      %rcx, %r14                                    #118.77
        movq      %rdx, %r13                                    #118.77
        movq      %rdi, %rsi                                    #118.77
        movl      $32, %edi                                     #123.7
        movl      $TY, %edx                                     #123.7
        movl      $5, %ecx                                      #123.7
        movl      $8, %r8d                                      #123.7
        movl      $5, (%rsp)                                    #120.26
        movl      $8, 4(%rsp)                                   #120.26
..___tag_value_plddxd.129:                                      #123.7
        call      fftw_plan_r2r_1d                              #123.7
..___tag_value_plddxd.130:                                      #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B9.2:                         # Preds ..B9.1
        movl      $32, %edi                                     #124.7
        movl      $TY+8, %esi                                   #124.7
        movq      %r13, %rdx                                    #124.7
        movl      $9, %r8d                                      #124.7
        movl      4(%rsp), %ecx                                 #124.7
        movq      %rax, (%r14)                                  #123.4
..___tag_value_plddxd.131:                                      #124.7
        call      fftw_plan_r2r_1d                              #124.7
..___tag_value_plddxd.132:                                      #
                                # LOE rax rbx rbp r12 r15
..B9.3:                         # Preds ..B9.2
        movq      %rax, (%r15)                                  #124.4
        addq      $16, %rsp                                     #125.1
..___tag_value_plddxd.133:                                      #
        popq      %r15                                          #125.1
..___tag_value_plddxd.135:                                      #
        popq      %r14                                          #125.1
..___tag_value_plddxd.137:                                      #
        popq      %r13                                          #125.1
..___tag_value_plddxd.139:                                      #
        ret                                                     #125.1
        .align    16,0x90
..___tag_value_plddxd.140:                                      #
                                # LOE
# mark_end;
	.type	plddxd,@function
	.size	plddxd,.-plddxd
	.data
# -- End  plddxd
	.text
# -- Begin  plintd
# mark_begin;
       .align    16,0x90
	.globl plintd
plintd:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %rcx
# parameter 5: %r8
..B10.1:                        # Preds ..B10.0
..___tag_value_plintd.141:                                      #127.76
        pushq     %r12                                          #127.76
..___tag_value_plintd.143:                                      #
        pushq     %r13                                          #127.76
..___tag_value_plintd.145:                                      #
        pushq     %r14                                          #127.76
..___tag_value_plintd.147:                                      #
        pushq     %r15                                          #127.76
..___tag_value_plintd.149:                                      #
        pushq     %rsi                                          #127.76
..___tag_value_plintd.151:                                      #
        movq      %rsi, %r13                                    #127.76
        movq      %rdx, %r12                                    #127.76
        movq      %r8, %r15                                     #127.76
        movq      %rcx, %r14                                    #127.76
        movl      $32, %edi                                     #129.7
        movq      %r12, %rsi                                    #129.7
        movl      $9, %ecx                                      #129.7
        movl      $8, %r8d                                      #129.7
        lea       8(%r13), %rdx                                 #129.7
        movl      $9, (%rsp)                                    #128.26
        movl      $4, 4(%rsp)                                   #128.26
..___tag_value_plintd.152:                                      #129.7
        call      fftw_plan_r2r_1d                              #129.7
..___tag_value_plintd.153:                                      #
                                # LOE rax rbx rbp r12 r13 r14 r15
..B10.2:                        # Preds ..B10.1
        movl      $32, %edi                                     #130.7
        movq      %r13, %rsi                                    #130.7
        movq      %r12, %rdx                                    #130.7
        movl      $9, %r8d                                      #130.7
        movl      4(%rsp), %ecx                                 #130.7
        movq      %rax, (%r14)                                  #129.4
..___tag_value_plintd.154:                                      #130.7
        call      fftw_plan_r2r_1d                              #130.7
..___tag_value_plintd.155:                                      #
                                # LOE rax rbx rbp r15
..B10.3:                        # Preds ..B10.2
        movq      %rax, (%r15)                                  #130.4
        popq      %rcx                                          #131.1
..___tag_value_plintd.156:                                      #
        popq      %r15                                          #131.1
..___tag_value_plintd.158:                                      #
        popq      %r14                                          #131.1
..___tag_value_plintd.160:                                      #
        popq      %r13                                          #131.1
..___tag_value_plintd.162:                                      #
        popq      %r12                                          #131.1
..___tag_value_plintd.164:                                      #
        ret                                                     #131.1
        .align    16,0x90
..___tag_value_plintd.165:                                      #
                                # LOE
# mark_end;
	.type	plintd,@function
	.size	plintd,.-plintd
	.data
# -- End  plintd
	.text
# -- Begin  exddxm
# mark_begin;
       .align    16,0x90
	.globl exddxm
exddxm:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %ecx
# parameter 5: %r8
# parameter 6: %r9
..B11.1:                        # Preds ..B11.0
..___tag_value_exddxm.166:                                      #134.127
        pushq     %rbp                                          #134.127
..___tag_value_exddxm.168:                                      #
        movq      %rsp, %rbp                                    #134.127
..___tag_value_exddxm.169:                                      #
        andq      $-32, %rsp                                    #134.127
        pushq     %r12                                          #134.127
        pushq     %r13                                          #134.127
        pushq     %r14                                          #134.127
        pushq     %r15                                          #134.127
        pushq     %rbx                                          #134.127
        subq      $24, %rsp                                     #134.127
..___tag_value_exddxm.171:                                      #
        movq      %rdi, %r13                                    #134.127
        movq      %r8, %rdi                                     #136.3
        movq      %r9, %r15                                     #134.127
        movq      %rdx, (%rsp)                                  #134.127
        movl      %ecx, %r14d                                   #134.127
        movq      %rsi, %r12                                    #134.127
..___tag_value_exddxm.176:                                      #136.3
        call      fftw_execute                                  #136.3
..___tag_value_exddxm.177:                                      #
                                # LOE r12 r13 r15 r14d
..B11.2:                        # Preds ..B11.1
        movl      %r14d, %ebx                                   #
        shll      $5, %ebx                                      #
        testl     %r14d, %r14d                                  #142.13
        jbe       ..B11.8       # Prob 10%                      #142.13
                                # LOE r12 r13 r15 ebx r14d
..B11.3:                        # Preds ..B11.2
        movl      $-2, %eax                                     #146.7
        movl      %ebx, %esi                                    #
        movq      $0x1e0000001f, %rdx                           #146.7
        vxorpd    %xmm3, %xmm3, %xmm3                           #147.20
        vmovsd    .L_2il0floatpacket.10(%rip), %xmm4            #144.11
        vmovupd   .L_2il0floatpacket.44(%rip), %xmm2            #147.20
        vmovd     %eax, %xmm0                                   #146.7
        xorl      %eax, %eax                                    #
        vpshufd   $0, %xmm0, %xmm5                              #146.7
        vmovd     %rdx, %xmm0                                   #146.7
        vmovsd    .L_2il0floatpacket.15(%rip), %xmm1            #149.25
        movq      (%rsp), %rcx                                  #
                                # LOE rcx r12 r13 r15 eax ebx esi r14d xmm0 xmm1 xmm2 xmm3 xmm4 xmm5
..B11.4:                        # Preds ..B11.6 ..B11.3
        decl      %eax                                          #142.3
        addl      $-32, %esi                                    #142.3
        xorb      %r10b, %r10b                                  #145.5
        movl      %esi, %r9d                                    #
        lea       (%r14,%rax), %r8d                             #144.5
        movl      %r8d, %edx                                    #144.5
        vmulsd    (%rcx,%rdx,8), %xmm4, %xmm6                   #144.5
        vmovsd    %xmm6, (%rcx,%rdx,8)                          #144.5
        vmovsd    %xmm6, %xmm3, %xmm7                           #146.7
        vmovdqa   %xmm0, %xmm6                                  #146.7
        .align    16,0x90
                                # LOE rdx rcx rsi r12 r13 r15 eax ebx r8d r9d r14d r10b xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7
..B11.5:                        # Preds ..B11.5 ..B11.4
        vcvtdq2pd %xmm6, %xmm10                                 #147.20
        vcmpltpd  %xmm3, %xmm10, %xmm9                          #147.20
        vandpd    %xmm9, %xmm2, %xmm11                          #147.20
        lea       31(%r9), %r11d                                #146.13
        addb      $2, %r10b                                     #145.5
        vaddpd    %xmm11, %xmm10, %xmm12                        #147.20
        vmovsd    (%r13,%r11,8), %xmm8                          #146.13
        addl      $-2, %r9d                                     #145.5
        vmovhpd   -8(%r13,%r11,8), %xmm8, %xmm13                #146.13
        vpaddd    %xmm5, %xmm6, %xmm6                           #147.7
        vmulpd    %xmm13, %xmm12, %xmm14                        #147.7
        vsubpd    %xmm13, %xmm7, %xmm7                          #146.7
        vmovlpd   %xmm14, (%r13,%r11,8)                         #147.7
        vmovhpd   %xmm14, -8(%r13,%r11,8)                       #147.7
        cmpb      $30, %r10b                                    #145.5
        jb        ..B11.5       # Prob 82%                      #145.5
                                # LOE rdx rcx rsi r12 r13 r15 eax ebx r8d r9d r14d r10b xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7
..B11.6:                        # Preds ..B11.5
        vunpckhpd %xmm7, %xmm7, %xmm6                           #146.7
        lea       1(%rsi), %r9d                                 #146.7
        vaddsd    %xmm6, %xmm7, %xmm7                           #146.7
        vsubsd    (%r13,%r9,8), %xmm7, %xmm8                    #146.7
        vmulsd    (%r13,%rsi,8), %xmm1, %xmm9                   #149.28
        vmovsd    %xmm8, (%rcx,%rdx,8)                          #146.7
        lea       32(%rsi), %edx                                #149.5
        vsubsd    %xmm9, %xmm8, %xmm10                          #149.28
        vmulsd    %xmm10, %xmm4, %xmm11                         #149.28
        vmovsd    %xmm11, (%r13,%rdx,8)                         #149.5
        testl     %r8d, %r8d                                    #142.13
        jne       ..B11.4       # Prob 82%                      #142.13
                                # LOE rcx r12 r13 r15 eax ebx esi r14d xmm0 xmm1 xmm2 xmm3 xmm4 xmm5
..B11.8:                        # Preds ..B11.6 ..B11.2
        movq      %r15, %rdi                                    #168.3
..___tag_value_exddxm.178:                                      #168.3
        call      fftw_execute                                  #168.3
..___tag_value_exddxm.179:                                      #
                                # LOE r12 ebx
..B11.9:                        # Preds ..B11.8
        lea       -1(%rbx), %eax                                #171.9
        testl     %ebx, %ebx                                    #171.13
        jbe       ..B11.13      # Prob 10%                      #171.13
                                # LOE rax r12
..B11.11:                       # Preds ..B11.9 ..B11.11
        movq      %rax, %rdx                                    #172.23
        andq      $31, %rdx                                     #172.23
        vmovsd    (%r12,%rax,8), %xmm0                          #172.6
        vmulsd    WEIGHTS(,%rdx,8), %xmm0, %xmm1                #172.6
        vmovsd    %xmm1, (%r12,%rax,8)                          #172.6
        decl      %eax                                          #171.9
        movl      %eax, %ecx                                    #171.3
        incl      %ecx                                          #171.3
        jne       ..B11.11      # Prob 82%                      #171.13
                                # LOE rax r12
..B11.13:                       # Preds ..B11.11 ..B11.9
        addq      $24, %rsp                                     #174.1
..___tag_value_exddxm.180:                                      #174.1
        popq      %rbx                                          #174.1
..___tag_value_exddxm.181:                                      #174.1
        popq      %r15                                          #174.1
..___tag_value_exddxm.182:                                      #174.1
        popq      %r14                                          #174.1
..___tag_value_exddxm.183:                                      #174.1
        popq      %r13                                          #174.1
..___tag_value_exddxm.184:                                      #174.1
        popq      %r12                                          #174.1
        movq      %rbp, %rsp                                    #174.1
        popq      %rbp                                          #174.1
..___tag_value_exddxm.185:                                      #
        ret                                                     #174.1
        .align    16,0x90
..___tag_value_exddxm.187:                                      #
                                # LOE
# mark_end;
	.type	exddxm,@function
	.size	exddxm,.-exddxm
	.data
# -- End  exddxm
	.text
# -- Begin  exddxd
# mark_begin;
       .align    16,0x90
	.globl exddxd
exddxd:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %xmm0
# parameter 4: %rdx
# parameter 5: %rcx
..B12.1:                        # Preds ..B12.0
..___tag_value_exddxd.188:                                      #176.104
        pushq     %rbp                                          #176.104
..___tag_value_exddxd.190:                                      #
        movq      %rsp, %rbp                                    #176.104
..___tag_value_exddxd.191:                                      #
        andq      $-32, %rsp                                    #176.104
        pushq     %r13                                          #176.104
        pushq     %r14                                          #176.104
        pushq     %r15                                          #176.104
        pushq     %rsi                                          #176.104
..___tag_value_exddxd.193:                                      #
        movq      %rdi, %r15                                    #176.104
        movq      %rdx, %rdi                                    #178.3
        movq      %rcx, %r14                                    #176.104
        vmovsd    %xmm0, (%rsp)                                 #176.104
        movq      %rsi, %r13                                    #176.104
..___tag_value_exddxd.196:                                      #178.3
        call      fftw_execute                                  #178.3
..___tag_value_exddxd.197:                                      #
                                # LOE rbx r12 r13 r14 r15
..B12.2:                        # Preds ..B12.1
        vmovsd    .L_2il0floatpacket.10(%rip), %xmm3            #182.6
        movl      $4, %eax                                      #185.5
        vmulsd    (%rsp), %xmm3, %xmm2                          #182.3
        vmovsd    16+TY(%rip), %xmm5                            #184.8
        vmovd     %eax, %xmm10                                  #185.5
        vmovsd    24+TY(%rip), %xmm8                            #184.8
        movb      $3, %al                                       #183.3
        vmulsd    .L_2il0floatpacket.11(%rip), %xmm5, %xmm6     #185.5
        vsubsd    8+TY(%rip), %xmm2, %xmm4                      #184.5
        vmulsd    .L_2il0floatpacket.12(%rip), %xmm8, %xmm9     #185.5
        vsubsd    %xmm5, %xmm4, %xmm7                           #184.5
        vmovupd   .L_2il0floatpacket.14(%rip), %ymm4            #185.12
        vxorpd    %ymm0, %ymm0, %ymm0                           #176.6
        vsubsd    %xmm8, %xmm7, %xmm2                           #184.5
        vmovapd   %ymm0, %ymm1                                  #176.6
        vmovsd    %xmm6, 16+TY(%rip)                            #185.5
        vmovsd    %xmm9, 24+TY(%rip)                            #185.5
        vpshufd   $0, %xmm10, %xmm6                             #185.5
        vmovdqu   .L_2il0floatpacket.13(%rip), %xmm5            #185.5
                                # LOE rbx r12 r13 r14 r15 al xmm2 xmm3 xmm5 xmm6 ymm0 ymm1 ymm4
..B12.3:                        # Preds ..B12.3 ..B12.2
        vcvtdq2pd %xmm5, %ymm8                                  #185.12
        movb      %al, %dl                                      #184.8
        vpaddd    %xmm6, %xmm5, %xmm5                           #185.5
        incb      %dl                                           #184.8
        addb      $4, %al                                       #183.3
        movzbl    %dl, %ecx                                     #184.8
        vcmpltpd  %ymm0, %ymm8, %ymm7                           #185.12
        vmovupd   TY(,%rcx,8), %ymm11                           #184.8
        vandpd    %ymm7, %ymm4, %ymm9                           #185.12
        vaddpd    %ymm9, %ymm8, %ymm10                          #185.12
        vsubpd    %ymm11, %ymm1, %ymm1                          #184.5
        vmulpd    %ymm11, %ymm10, %ymm12                        #185.5
        vmovupd   %ymm12, TY(,%rcx,8)                           #185.5
        cmpb      $31, %al                                      #183.3
        jb        ..B12.3       # Prob 82%                      #183.3
                                # LOE rbx r12 r13 r14 r15 al xmm2 xmm3 xmm5 xmm6 ymm0 ymm1 ymm4
..B12.4:                        # Preds ..B12.3
        movq      %r14, %rdi                                    #190.3
        vextractf128 $1, %ymm1, %xmm0                           #176.6
        vaddpd    %xmm0, %xmm1, %xmm4                           #176.6
        vunpckhpd %xmm4, %xmm4, %xmm5                           #176.6
        vaddsd    %xmm5, %xmm4, %xmm6                           #176.6
        vaddsd    %xmm2, %xmm6, %xmm7                           #176.6
        vmovsd    .L_2il0floatpacket.15(%rip), %xmm2            #187.14
        vmulsd    TY(%rip), %xmm2, %xmm8                        #187.17
        vsubsd    %xmm8, %xmm7, %xmm9                           #187.17
        vmulsd    %xmm9, %xmm3, %xmm3                           #187.17
        vmovsd    %xmm3, 256(%r15)                              #187.3
        vzeroupper                                              #190.3
..___tag_value_exddxd.198:                                      #190.3
        call      fftw_execute                                  #190.3
..___tag_value_exddxd.199:                                      #
                                # LOE rbx r12 r13
..B12.5:                        # Preds ..B12.4
        movq      %r13, %rcx                                    #193.3
        andq      $31, %rcx                                     #193.3
        movl      %ecx, %ecx                                    #193.3
        testl     %ecx, %ecx                                    #193.3
        je        ..B12.10      # Prob 50%                      #193.3
                                # LOE rcx rbx r12 r13
..B12.6:                        # Preds ..B12.5
        testb     $7, %cl                                       #193.3
        jne       ..B12.18      # Prob 10%                      #193.3
                                # LOE rcx rbx r12 r13
..B12.7:                        # Preds ..B12.6
        negl      %ecx                                          #193.3
        xorl      %edx, %edx                                    #193.3
        addl      $32, %ecx                                     #193.3
        xorl      %eax, %eax                                    #193.3
        shrl      $3, %ecx                                      #193.3
                                # LOE rdx rcx rbx r12 r13 eax
..B12.8:                        # Preds ..B12.8 ..B12.7
        vmovsd    (%r13,%rdx,8), %xmm0                          #194.6
        incl      %eax                                          #193.3
        vmulsd    WEIGHTS(,%rdx,8), %xmm0, %xmm1                #194.6
        vmovsd    %xmm1, (%r13,%rdx,8)                          #194.6
        movl      %eax, %edx                                    #193.3
        cmpl      %ecx, %eax                                    #193.3
        jb        ..B12.8       # Prob 82%                      #193.3
                                # LOE rdx rcx rbx r12 r13 eax
..B12.10:                       # Preds ..B12.8 ..B12.5
        movl      %ecx, %eax                                    #193.3
        negl      %eax                                          #193.3
        andl      $7, %eax                                      #193.3
        negl      %eax                                          #193.3
        addl      $32, %eax                                     #193.3
        .align    16,0x90
                                # LOE rcx rbx r12 r13 eax
..B12.11:                       # Preds ..B12.11 ..B12.10
        lea       4(%rcx), %edx                                 #194.6
        vmovupd   WEIGHTS(,%rcx,8), %xmm0                       #194.13
        vmovupd   WEIGHTS(,%rdx,8), %xmm3                       #194.13
        vinsertf128 $1, 16+WEIGHTS(,%rcx,8), %ymm0, %ymm1       #194.13
        vmulpd    (%r13,%rcx,8), %ymm1, %ymm2                   #194.6
        vmovupd   %ymm2, (%r13,%rcx,8)                          #194.6
        addl      $8, %ecx                                      #193.3
        vinsertf128 $1, 16+WEIGHTS(,%rdx,8), %ymm3, %ymm4       #194.13
        vmulpd    (%r13,%rdx,8), %ymm4, %ymm5                   #194.6
        vmovupd   %ymm5, (%r13,%rdx,8)                          #194.6
        cmpl      %eax, %ecx                                    #193.3
        jb        ..B12.11      # Prob 82%                      #193.3
                                # LOE rcx rbx r12 r13 eax
..B12.13:                       # Preds ..B12.11 ..B12.18
        movl      %eax, %edx                                    #193.3
        cmpl      $32, %eax                                     #193.3
        jae       ..B12.17      # Prob 0%                       #193.3
                                # LOE rdx rbx r12 r13 eax
..B12.15:                       # Preds ..B12.13 ..B12.15
        vmovsd    (%r13,%rdx,8), %xmm0                          #194.6
        incl      %eax                                          #193.3
        vmulsd    WEIGHTS(,%rdx,8), %xmm0, %xmm1                #194.6
        vmovsd    %xmm1, (%r13,%rdx,8)                          #194.6
        movl      %eax, %edx                                    #193.3
        cmpl      $32, %eax                                     #193.3
        jb        ..B12.15      # Prob 82%                      #193.3
                                # LOE rdx rbx r12 r13 eax
..B12.17:                       # Preds ..B12.15 ..B12.13
        vzeroupper                                              #196.1
        popq      %rcx                                          #196.1
..___tag_value_exddxd.200:                                      #196.1
        popq      %r15                                          #196.1
..___tag_value_exddxd.201:                                      #196.1
        popq      %r14                                          #196.1
..___tag_value_exddxd.202:                                      #196.1
        popq      %r13                                          #196.1
        movq      %rbp, %rsp                                    #196.1
        popq      %rbp                                          #196.1
..___tag_value_exddxd.203:                                      #
        ret                                                     #196.1
..___tag_value_exddxd.205:                                      #
                                # LOE
..B12.18:                       # Preds ..B12.6                 # Infreq
        xorl      %eax, %eax                                    #193.3
        jmp       ..B12.13      # Prob 100%                     #193.3
        .align    16,0x90
..___tag_value_exddxd.210:                                      #
                                # LOE rbx r12 r13 eax
# mark_end;
	.type	exddxd,@function
	.size	exddxd,.-exddxd
	.data
# -- End  exddxd
	.text
# -- Begin  exintd
# mark_begin;
       .align    16,0x90
	.globl exintd
exintd:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %xmm0
# parameter 5: %rcx
# parameter 6: %r8
..B13.1:                        # Preds ..B13.0
..___tag_value_exintd.211:                                      #198.125
        pushq     %rbp                                          #198.125
..___tag_value_exintd.213:                                      #
        movq      %rsp, %rbp                                    #198.125
..___tag_value_exintd.214:                                      #
        andq      $-32, %rsp                                    #198.125
        pushq     %r12                                          #198.125
        pushq     %rbx                                          #198.125
        subq      $16, %rsp                                     #198.125
        movq      %rdx, %r9                                     #198.125
        movq      %r9, %rax                                     #202.3
..___tag_value_exintd.216:                                      #
        movq      %r8, %r12                                     #198.125
        andq      $31, %rax                                     #202.3
        movq      %rsi, %r8                                     #198.125
        movl      %eax, %esi                                    #202.3
        movq      %rdi, %rbx                                    #198.125
        vmovsd    %xmm0, (%rsp)                                 #198.125
        testl     %esi, %esi                                    #202.3
        je        ..B13.7       # Prob 50%                      #202.3
                                # LOE rax rcx rbx r8 r9 r12 r13 r14 r15 esi
..B13.2:                        # Preds ..B13.1
        testl     $7, %esi                                      #202.3
        jne       ..B13.30      # Prob 10%                      #202.3
                                # LOE rcx rbx r8 r9 r12 r13 r14 r15 esi
..B13.3:                        # Preds ..B13.2
        negl      %esi                                          #202.3
        xorl      %edx, %edx                                    #202.3
        addl      $32, %esi                                     #202.3
        shrl      $3, %esi                                      #202.3
        movl      %esi, %eax                                    #202.3
                                # LOE rax rdx rcx rbx r8 r9 r12 r13 r14 r15 esi
..B13.4:                        # Preds ..B13.4 ..B13.3
        vmovsd    (%r8,%rdx,8), %xmm0                           #203.12
        vmulsd    IWEIGHTS(,%rdx,8), %xmm0, %xmm1               #203.17
        vmovsd    %xmm1, (%r9,%rdx,8)                           #203.6
        incq      %rdx                                          #202.3
        cmpq      %rax, %rdx                                    #202.3
        jb        ..B13.4       # Prob 82%                      #202.3
                                # LOE rax rdx rcx rbx r8 r9 r12 r13 r14 r15 esi
..B13.7:                        # Preds ..B13.1 ..B13.4
        negl      %esi                                          #202.3
        andl      $7, %esi                                      #202.3
        negl      %esi                                          #202.3
        addl      $32, %esi                                     #202.3
        .align    16,0x90
                                # LOE rax rcx rbx rsi r8 r9 r12 r13 r14 r15
..B13.8:                        # Preds ..B13.8 ..B13.7
        vmovupd   (%r8,%rax,8), %xmm0                           #203.12
        vmovupd   32(%r8,%rax,8), %xmm5                         #203.12
        vmovupd   IWEIGHTS(,%rax,8), %xmm1                      #203.17
        vmovupd   32+IWEIGHTS(,%rax,8), %xmm6                   #203.17
        vinsertf128 $1, 16+IWEIGHTS(,%rax,8), %ymm1, %ymm3      #203.17
        vinsertf128 $1, 48+IWEIGHTS(,%rax,8), %ymm6, %ymm8      #203.17
        vinsertf128 $1, 16(%r8,%rax,8), %ymm0, %ymm2            #203.12
        vinsertf128 $1, 48(%r8,%rax,8), %ymm5, %ymm7            #203.12
        vmulpd    %ymm3, %ymm2, %ymm4                           #203.17
        vmulpd    %ymm8, %ymm7, %ymm9                           #203.17
        vmovupd   %ymm4, (%r9,%rax,8)                           #203.6
        vmovupd   %ymm9, 32(%r9,%rax,8)                         #203.6
        addq      $8, %rax                                      #202.3
        cmpq      %rsi, %rax                                    #202.3
        jb        ..B13.8       # Prob 82%                      #202.3
                                # LOE rax rcx rbx rsi r8 r9 r12 r13 r14 r15
..B13.10:                       # Preds ..B13.8 ..B13.30
        cmpq      $32, %rsi                                     #202.3
        jae       ..B13.14      # Prob 0%                       #202.3
                                # LOE rcx rbx rsi r8 r9 r12 r13 r14 r15
..B13.12:                       # Preds ..B13.10 ..B13.12
        vmovsd    (%r8,%rsi,8), %xmm0                           #203.12
        vmulsd    IWEIGHTS(,%rsi,8), %xmm0, %xmm1               #203.17
        vmovsd    %xmm1, (%r9,%rsi,8)                           #203.6
        incq      %rsi                                          #202.3
        cmpq      $32, %rsi                                     #202.3
        jb        ..B13.12      # Prob 82%                      #202.3
                                # LOE rcx rbx rsi r8 r9 r12 r13 r14 r15
..B13.14:                       # Preds ..B13.12 ..B13.10
        movq      %rcx, %rdi                                    #206.3
        vzeroupper                                              #206.3
..___tag_value_exintd.218:                                      #206.3
        call      fftw_execute                                  #206.3
..___tag_value_exintd.219:                                      #
                                # LOE rbx r12 r13 r14 r15
..B13.15:                       # Preds ..B13.14
        lea       16(%rbx), %rax                                #210.5
        andq      $31, %rax                                     #209.3
        vxorpd    %ymm1, %ymm1, %ymm1                           #198.6
        testl     %eax, %eax                                    #209.3
        je        ..B13.20      # Prob 50%                      #209.3
                                # LOE rbx r12 r13 r14 r15 eax ymm1
..B13.16:                       # Preds ..B13.15
        testb     $7, %al                                       #209.3
        jne       ..B13.31      # Prob 10%                      #209.3
                                # LOE rbx r12 r13 r14 r15 eax ymm1
..B13.17:                       # Preds ..B13.16
        negl      %eax                                          #209.3
        xorl      %ecx, %ecx                                    #209.3
        addl      $32, %eax                                     #209.3
        xorl      %edx, %edx                                    #
        shrl      $3, %eax                                      #209.3
        vmovsd    .L_2il0floatpacket.11(%rip), %xmm2            #211.8
        vmovsd    (%rsp), %xmm8                                 #
        .align    16,0x90
                                # LOE rdx rbx r12 r13 r14 r15 eax ecx xmm2 xmm8 ymm1
..B13.18:                       # Preds ..B13.18 ..B13.17
        vxorpd    %xmm3, %xmm3, %xmm3                           #210.12
        lea       2(%rcx), %esi                                 #210.5
        vcvtsi2sd %esi, %xmm3, %xmm3                            #210.12
        vmovsd    16(%rbx,%rdx,8), %xmm0                        #210.5
        andl      $1, %esi                                      #211.22
        vdivsd    %xmm3, %xmm0, %xmm4                           #210.5
        vxorpd    %xmm6, %xmm6, %xmm6                           #211.25
        lea       -1(%rsi,%rsi), %r8d                           #211.25
        vcvtsi2sd %r8d, %xmm6, %xmm6                            #211.25
        vmulsd    %xmm4, %xmm2, %xmm5                           #211.10
        vmulsd    %xmm6, %xmm5, %xmm7                           #211.25
        incl      %ecx                                          #209.3
        vmovsd    %xmm4, 16(%rbx,%rdx,8)                        #210.5
        incq      %rdx                                          #209.3
        vaddsd    %xmm7, %xmm8, %xmm8                           #211.5
        cmpl      %eax, %ecx                                    #209.3
        jb        ..B13.18      # Prob 82%                      #209.3
                                # LOE rdx rbx r12 r13 r14 r15 eax ecx xmm2 xmm8 ymm1
..B13.19:                       # Preds ..B13.18
        vmovsd    %xmm8, (%rsp)                                 #
        jmp       ..B13.21      # Prob 100%                     #
                                # LOE rbx r12 r13 r14 r15 eax xmm2 ymm1
..B13.20:                       # Preds ..B13.15
        vmovsd    .L_2il0floatpacket.11(%rip), %xmm2            #211.8
                                # LOE rbx r12 r13 r14 r15 eax xmm2 ymm1
..B13.21:                       # Preds ..B13.19 ..B13.20
        movl      $4, %edx                                      #209.3
        lea       2(%rax), %ecx                                 #209.3
        lea       3(%rax), %esi                                 #209.3
        lea       4(%rax), %r8d                                 #209.3
        lea       5(%rax), %r9d                                 #209.3
        vmovd     %edx, %xmm0                                   #209.3
        vmovd     %ecx, %xmm3                                   #209.3
        movl      %eax, %edx                                    #209.3
        negl      %eax                                          #209.3
        addl      $3, %eax                                      #209.3
        vmovd     %esi, %xmm4                                   #209.3
        andl      $3, %eax                                      #209.3
        vmovd     %r8d, %xmm5                                   #209.3
        vmovd     %r9d, %xmm6                                   #209.3
        negl      %eax                                          #209.3
        vpunpcklqdq %xmm4, %xmm3, %xmm7                         #209.3
        addl      $31, %eax                                     #209.3
        vpunpcklqdq %xmm6, %xmm5, %xmm8                         #209.3
        vpshufd   $0, %xmm0, %xmm0                              #209.3
        vpcmpeqd  %xmm3, %xmm3, %xmm3                           #211.25
        vshufps   $136, %xmm8, %xmm7, %xmm6                     #209.3
        vmovupd   .L_2il0floatpacket.18(%rip), %ymm5            #211.8
        vmovdqu   .L_2il0floatpacket.19(%rip), %xmm4            #211.22
        .align    16,0x90
                                # LOE rax rdx rbx r12 r13 r14 r15 xmm0 xmm2 xmm3 xmm4 xmm6 ymm1 ymm5
..B13.22:                       # Preds ..B13.22 ..B13.21
        vmovupd   16(%rbx,%rdx,8), %ymm7                        #210.5
        vpand     %xmm4, %xmm6, %xmm10                          #211.22
        vpslld    $1, %xmm10, %xmm11                            #211.22
        vcvtdq2pd %xmm6, %ymm8                                  #210.12
        vpaddd    %xmm3, %xmm11, %xmm12                         #211.25
        vcvtdq2pd %xmm12, %ymm14                                #211.25
        vpaddd    %xmm0, %xmm6, %xmm6                           #198.6
        vdivpd    %ymm8, %ymm7, %ymm9                           #210.5
        vmulpd    %ymm9, %ymm5, %ymm13                          #211.10
        vmovupd   %ymm9, 16(%rbx,%rdx,8)                        #210.5
        vmulpd    %ymm14, %ymm13, %ymm15                        #211.25
        addq      $4, %rdx                                      #209.3
        vaddpd    %ymm15, %ymm1, %ymm1                          #211.5
        cmpq      %rax, %rdx                                    #209.3
        jb        ..B13.22      # Prob 82%                      #209.3
                                # LOE rax rdx rbx r12 r13 r14 r15 xmm0 xmm2 xmm3 xmm4 xmm6 ymm1 ymm5
..B13.24:                       # Preds ..B13.22 ..B13.31
        cmpq      $31, %rax                                     #209.3
        jae       ..B13.28      # Prob 0%                       #209.3
                                # LOE rax rbx r12 r13 r14 r15 xmm2 ymm1
..B13.25:                       # Preds ..B13.24
        vmovsd    (%rsp), %xmm8                                 #
        .align    16,0x90
                                # LOE rax rbx r12 r13 r14 r15 xmm2 xmm8 ymm1
..B13.26:                       # Preds ..B13.26 ..B13.25
        movl      %eax, %edx                                    #210.5
        vxorpd    %xmm3, %xmm3, %xmm3                           #210.12
        addl      $2, %edx                                      #210.5
        vxorpd    %xmm6, %xmm6, %xmm6                           #211.25
        vcvtsi2sd %edx, %xmm3, %xmm3                            #210.12
        vmovsd    16(%rbx,%rax,8), %xmm0                        #210.5
        andl      $1, %edx                                      #211.22
        vdivsd    %xmm3, %xmm0, %xmm4                           #210.5
        vmulsd    %xmm4, %xmm2, %xmm5                           #211.10
        lea       -1(%rdx,%rdx), %ecx                           #211.25
        vcvtsi2sd %ecx, %xmm6, %xmm6                            #211.25
        vmulsd    %xmm6, %xmm5, %xmm7                           #211.25
        vmovsd    %xmm4, 16(%rbx,%rax,8)                        #210.5
        incq      %rax                                          #209.3
        vaddsd    %xmm7, %xmm8, %xmm8                           #211.5
        cmpq      $31, %rax                                     #209.3
        jb        ..B13.26      # Prob 82%                      #209.3
                                # LOE rax rbx r12 r13 r14 r15 xmm2 xmm8 ymm1
..B13.27:                       # Preds ..B13.26
        vmovsd    %xmm8, (%rsp)                                 #
                                # LOE rbx r12 r13 r14 r15 xmm2 ymm1
..B13.28:                       # Preds ..B13.27 ..B13.24
        movq      %r12, %rdi                                    #215.3
        vextractf128 $1, %ymm1, %xmm0                           #198.6
        vmulsd    8(%rbx), %xmm2, %xmm2                         #213.13
        vaddpd    %xmm0, %xmm1, %xmm3                           #198.6
        vunpckhpd %xmm3, %xmm3, %xmm4                           #198.6
        vaddsd    %xmm4, %xmm3, %xmm5                           #198.6
        vaddsd    (%rsp), %xmm5, %xmm6                          #198.6
        vaddsd    %xmm6, %xmm2, %xmm7                           #213.13
        vmovsd    %xmm7, (%rbx)                                 #213.3
        vzeroupper                                              #215.3
        addq      $16, %rsp                                     #215.3
..___tag_value_exintd.220:                                      #215.3
        popq      %rbx                                          #215.3
..___tag_value_exintd.221:                                      #215.3
        popq      %r12                                          #215.3
        movq      %rbp, %rsp                                    #215.3
        popq      %rbp                                          #215.3
..___tag_value_exintd.222:                                      #
        jmp       fftw_execute                                  #215.3
..___tag_value_exintd.224:                                      #
                                # LOE
..B13.30:                       # Preds ..B13.2                 # Infreq
        xorl      %esi, %esi                                    #202.3
        jmp       ..B13.10      # Prob 100%                     #202.3
                                # LOE rcx rbx rsi r8 r9 r12 r13 r14 r15
..B13.31:                       # Preds ..B13.16                # Infreq
        vmovsd    .L_2il0floatpacket.11(%rip), %xmm2            #211.8
        xorl      %eax, %eax                                    #209.3
        jmp       ..B13.24      # Prob 100%                     #209.3
        .align    16,0x90
..___tag_value_exintd.228:                                      #
                                # LOE rax rbx r12 r13 r14 r15 xmm2 ymm1
# mark_end;
	.type	exintd,@function
	.size	exintd,.-exintd
	.data
# -- End  exintd
	.bss
	.align 32
	.align 32
IWEIGHTS:
	.type	IWEIGHTS,@object
	.size	IWEIGHTS,256
	.space 256	# pad
	.align 32
WEIGHTS:
	.type	WEIGHTS,@object
	.size	WEIGHTS,256
	.space 256	# pad
	.align 32
TY:
	.type	TY,@object
	.size	TY,264
	.space 264	# pad
	.section .rodata, "a"
	.align 32
	.align 32
.L_2il0floatpacket.1:
	.long	0x54442d18,0x3fb921fb,0x54442d18,0x3fb921fb,0x54442d18,0x3fb921fb,0x54442d18,0x3fb921fb
	.type	.L_2il0floatpacket.1,@object
	.size	.L_2il0floatpacket.1,32
	.align 32
.L_2il0floatpacket.2:
	.long	0x00000000,0x3fe00000,0x00000000,0x3fe00000,0x00000000,0x3fe00000,0x00000000,0x3fe00000
	.type	.L_2il0floatpacket.2,@object
	.size	.L_2il0floatpacket.2,32
	.align 32
.L_2il0floatpacket.3:
	.long	0x00000000,0xbf900000,0x00000000,0xbf900000,0x00000000,0xbf900000,0x00000000,0xbf900000
	.type	.L_2il0floatpacket.3,@object
	.size	.L_2il0floatpacket.3,32
	.align 32
.L_2il0floatpacket.4:
	.long	0x00000000,0x3ff00000,0x00000000,0x3ff00000,0x00000000,0x3ff00000,0x00000000,0x3ff00000
	.type	.L_2il0floatpacket.4,@object
	.size	.L_2il0floatpacket.4,32
	.align 32
.L_2il0floatpacket.5:
	.long	0x00000000,0xc0500000,0x00000000,0xc0500000,0x00000000,0xc0500000,0x00000000,0xc0500000
	.type	.L_2il0floatpacket.5,@object
	.size	.L_2il0floatpacket.5,32
	.align 32
.L_2il0floatpacket.14:
	.long	0x00000000,0x41f00000,0x00000000,0x41f00000,0x00000000,0x41f00000,0x00000000,0x41f00000
	.type	.L_2il0floatpacket.14,@object
	.size	.L_2il0floatpacket.14,32
	.align 32
.L_2il0floatpacket.18:
	.long	0x00000000,0x40000000,0x00000000,0x40000000,0x00000000,0x40000000,0x00000000,0x40000000
	.type	.L_2il0floatpacket.18,@object
	.size	.L_2il0floatpacket.18,32
	.align 16
.L_2il0floatpacket.0:
	.long	0x0000001f,0x0000001e,0x0000001d,0x0000001c
	.type	.L_2il0floatpacket.0,@object
	.size	.L_2il0floatpacket.0,16
	.align 16
.L_2il0floatpacket.13:
	.long	0x00000004,0x00000005,0x00000006,0x00000007
	.type	.L_2il0floatpacket.13,@object
	.size	.L_2il0floatpacket.13,16
	.align 16
.L_2il0floatpacket.19:
	.long	0x00000001,0x00000001,0x00000001,0x00000001
	.type	.L_2il0floatpacket.19,@object
	.size	.L_2il0floatpacket.19,16
	.align 16
.L_2il0floatpacket.44:
	.long	0x00000000,0x41f00000,0x00000000,0x41f00000
	.type	.L_2il0floatpacket.44,@object
	.size	.L_2il0floatpacket.44,16
	.align 8
.L_2il0floatpacket.10:
	.long	0x00000000,0x40400000
	.type	.L_2il0floatpacket.10,@object
	.size	.L_2il0floatpacket.10,8
	.align 8
.L_2il0floatpacket.11:
	.long	0x00000000,0x40000000
	.type	.L_2il0floatpacket.11,@object
	.size	.L_2il0floatpacket.11,8
	.align 8
.L_2il0floatpacket.12:
	.long	0x00000000,0x40080000
	.type	.L_2il0floatpacket.12,@object
	.size	.L_2il0floatpacket.12,8
	.align 8
.L_2il0floatpacket.15:
	.long	0x00000000,0x3fe00000
	.type	.L_2il0floatpacket.15,@object
	.size	.L_2il0floatpacket.15,8
	.align 8
.L_2il0floatpacket.17:
	.long	0x55555555,0x3fd55555
	.type	.L_2il0floatpacket.17,@object
	.size	.L_2il0floatpacket.17,8
	.align 8
.L_2il0floatpacket.20:
	.long	0x00000000,0x3fa00000
	.type	.L_2il0floatpacket.20,@object
	.size	.L_2il0floatpacket.20,8
	.align 8
.L_2il0floatpacket.56:
	.long	0x00000000,0x3ff00000
	.type	.L_2il0floatpacket.56,@object
	.size	.L_2il0floatpacket.56,8
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
	.4byte 0x00000014
	.8byte 0x7801000100000000
	.8byte 0x0000019008070c10
	.4byte 0x00000000
	.4byte 0x00000034
	.4byte 0x0000001c
	.8byte ..___tag_value_mkwi.1
	.8byte ..___tag_value_mkwi.8-..___tag_value_mkwi.1
	.byte 0x04
	.4byte ..___tag_value_mkwi.3-..___tag_value_mkwi.1
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_mkwi.4-..___tag_value_mkwi.3
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_mkwi.6-..___tag_value_mkwi.4
	.8byte 0x00000000c608070c
	.2byte 0x0000
	.4byte 0x00000034
	.4byte 0x00000054
	.8byte ..___tag_value_plddx.9
	.8byte ..___tag_value_plddx.21-..___tag_value_plddx.9
	.byte 0x04
	.4byte ..___tag_value_plddx.11-..___tag_value_plddx.9
	.4byte 0x0286100e
	.byte 0x04
	.4byte ..___tag_value_plddx.13-..___tag_value_plddx.11
	.2byte 0x200e
	.byte 0x04
	.4byte ..___tag_value_plddx.18-..___tag_value_plddx.13
	.4byte 0x04c6100e
	.4byte ..___tag_value_plddx.20-..___tag_value_plddx.18
	.2byte 0x080e
	.byte 0x00
	.4byte 0x00000034
	.4byte 0x0000008c
	.8byte ..___tag_value_plint.22
	.8byte ..___tag_value_plint.34-..___tag_value_plint.22
	.byte 0x04
	.4byte ..___tag_value_plint.24-..___tag_value_plint.22
	.4byte 0x0286100e
	.byte 0x04
	.4byte ..___tag_value_plint.26-..___tag_value_plint.24
	.2byte 0x200e
	.byte 0x04
	.4byte ..___tag_value_plint.31-..___tag_value_plint.26
	.4byte 0x04c6100e
	.4byte ..___tag_value_plint.33-..___tag_value_plint.31
	.2byte 0x080e
	.byte 0x00
	.4byte 0x00000034
	.4byte 0x000000c4
	.8byte ..___tag_value_plintp.35
	.8byte ..___tag_value_plintp.47-..___tag_value_plintp.35
	.byte 0x04
	.4byte ..___tag_value_plintp.37-..___tag_value_plintp.35
	.4byte 0x0286100e
	.byte 0x04
	.4byte ..___tag_value_plintp.39-..___tag_value_plintp.37
	.2byte 0x200e
	.byte 0x04
	.4byte ..___tag_value_plintp.44-..___tag_value_plintp.39
	.4byte 0x04c6100e
	.4byte ..___tag_value_plintp.46-..___tag_value_plintp.44
	.2byte 0x080e
	.byte 0x00
	.4byte 0x0000004c
	.4byte 0x000000fc
	.8byte ..___tag_value_exddx.48
	.8byte ..___tag_value_exddx.61-..___tag_value_exddx.48
	.byte 0x04
	.4byte ..___tag_value_exddx.50-..___tag_value_exddx.48
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_exddx.51-..___tag_value_exddx.50
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_exddx.53-..___tag_value_exddx.51
	.8byte 0xffe00d1c380e0e10
	.8byte 0xfffffff80d1affff
	.2byte 0x0422
	.4byte ..___tag_value_exddx.58-..___tag_value_exddx.53
	.2byte 0x04ce
	.4byte ..___tag_value_exddx.59-..___tag_value_exddx.58
	.4byte 0xc608070c
	.2byte 0x0000
	.4byte 0x0000004c
	.4byte 0x0000014c
	.8byte ..___tag_value_exint.62
	.8byte ..___tag_value_exint.73-..___tag_value_exint.62
	.byte 0x04
	.4byte ..___tag_value_exint.64-..___tag_value_exint.62
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_exint.65-..___tag_value_exint.64
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_exint.67-..___tag_value_exint.65
	.8byte 0xffe00d1c380e0d10
	.8byte 0xfffffff80d1affff
	.2byte 0x0422
	.4byte ..___tag_value_exint.70-..___tag_value_exint.67
	.2byte 0x04cd
	.4byte ..___tag_value_exint.71-..___tag_value_exint.70
	.4byte 0xc608070c
	.2byte 0x0000
	.4byte 0x0000004c
	.4byte 0x0000019c
	.8byte ..___tag_value_exintp.74
	.8byte ..___tag_value_exintp.85-..___tag_value_exintp.74
	.byte 0x04
	.4byte ..___tag_value_exintp.76-..___tag_value_exintp.74
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_exintp.77-..___tag_value_exintp.76
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_exintp.79-..___tag_value_exintp.77
	.8byte 0xffe00d1c380e0d10
	.8byte 0xfffffff80d1affff
	.2byte 0x0422
	.4byte ..___tag_value_exintp.82-..___tag_value_exintp.79
	.2byte 0x04cd
	.4byte ..___tag_value_exintp.83-..___tag_value_exintp.82
	.4byte 0xc608070c
	.2byte 0x0000
	.4byte 0x00000094
	.4byte 0x000001ec
	.8byte ..___tag_value_plddxm.86
	.8byte ..___tag_value_plddxm.119-..___tag_value_plddxm.86
	.byte 0x04
	.4byte ..___tag_value_plddxm.88-..___tag_value_plddxm.86
	.4byte 0x028c100e
	.byte 0x04
	.4byte ..___tag_value_plddxm.90-..___tag_value_plddxm.88
	.4byte 0x038d180e
	.byte 0x04
	.4byte ..___tag_value_plddxm.92-..___tag_value_plddxm.90
	.4byte 0x048e200e
	.byte 0x04
	.4byte ..___tag_value_plddxm.94-..___tag_value_plddxm.92
	.4byte 0x058f280e
	.byte 0x04
	.4byte ..___tag_value_plddxm.96-..___tag_value_plddxm.94
	.4byte 0x0683300e
	.byte 0x04
	.4byte ..___tag_value_plddxm.98-..___tag_value_plddxm.96
	.4byte 0x0786380e
	.byte 0x04
	.4byte ..___tag_value_plddxm.100-..___tag_value_plddxm.98
	.2byte 0x500e
	.byte 0x04
	.4byte ..___tag_value_plddxm.101-..___tag_value_plddxm.100
	.4byte 0x0401900e
	.4byte ..___tag_value_plddxm.106-..___tag_value_plddxm.101
	.4byte 0x04c6380e
	.4byte ..___tag_value_plddxm.108-..___tag_value_plddxm.106
	.4byte 0x04c3300e
	.4byte ..___tag_value_plddxm.110-..___tag_value_plddxm.108
	.4byte 0x04cf280e
	.4byte ..___tag_value_plddxm.112-..___tag_value_plddxm.110
	.4byte 0x04ce200e
	.4byte ..___tag_value_plddxm.114-..___tag_value_plddxm.112
	.4byte 0x04cd180e
	.4byte ..___tag_value_plddxm.116-..___tag_value_plddxm.114
	.4byte 0x04cc100e
	.4byte ..___tag_value_plddxm.118-..___tag_value_plddxm.116
	.4byte 0x0000080e
	.2byte 0x0000
	.4byte 0x0000005c
	.4byte 0x00000284
	.8byte ..___tag_value_plddxd.120
	.8byte ..___tag_value_plddxd.140-..___tag_value_plddxd.120
	.byte 0x04
	.4byte ..___tag_value_plddxd.122-..___tag_value_plddxd.120
	.4byte 0x028d100e
	.byte 0x04
	.4byte ..___tag_value_plddxd.124-..___tag_value_plddxd.122
	.4byte 0x038e180e
	.byte 0x04
	.4byte ..___tag_value_plddxd.126-..___tag_value_plddxd.124
	.4byte 0x048f200e
	.byte 0x04
	.4byte ..___tag_value_plddxd.128-..___tag_value_plddxd.126
	.2byte 0x300e
	.byte 0x04
	.4byte ..___tag_value_plddxd.133-..___tag_value_plddxd.128
	.4byte 0x04cf200e
	.4byte ..___tag_value_plddxd.135-..___tag_value_plddxd.133
	.4byte 0x04ce180e
	.4byte ..___tag_value_plddxd.137-..___tag_value_plddxd.135
	.4byte 0x04cd100e
	.4byte ..___tag_value_plddxd.139-..___tag_value_plddxd.137
	.8byte 0x000000000000080e
	.byte 0x00
	.4byte 0x0000006c
	.4byte 0x000002e4
	.8byte ..___tag_value_plintd.141
	.8byte ..___tag_value_plintd.165-..___tag_value_plintd.141
	.byte 0x04
	.4byte ..___tag_value_plintd.143-..___tag_value_plintd.141
	.4byte 0x028c100e
	.byte 0x04
	.4byte ..___tag_value_plintd.145-..___tag_value_plintd.143
	.4byte 0x038d180e
	.byte 0x04
	.4byte ..___tag_value_plintd.147-..___tag_value_plintd.145
	.4byte 0x048e200e
	.byte 0x04
	.4byte ..___tag_value_plintd.149-..___tag_value_plintd.147
	.4byte 0x058f280e
	.byte 0x04
	.4byte ..___tag_value_plintd.151-..___tag_value_plintd.149
	.2byte 0x300e
	.byte 0x04
	.4byte ..___tag_value_plintd.156-..___tag_value_plintd.151
	.4byte 0x04cf280e
	.4byte ..___tag_value_plintd.158-..___tag_value_plintd.156
	.4byte 0x04ce200e
	.4byte ..___tag_value_plintd.160-..___tag_value_plintd.158
	.4byte 0x04cd180e
	.4byte ..___tag_value_plintd.162-..___tag_value_plintd.160
	.4byte 0x04cc100e
	.4byte ..___tag_value_plintd.164-..___tag_value_plintd.162
	.8byte 0x000000000000080e
	.4byte 0x000000ac
	.4byte 0x00000354
	.8byte ..___tag_value_exddxm.166
	.8byte ..___tag_value_exddxm.187-..___tag_value_exddxm.166
	.byte 0x04
	.4byte ..___tag_value_exddxm.168-..___tag_value_exddxm.166
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_exddxm.169-..___tag_value_exddxm.168
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_exddxm.171-..___tag_value_exddxm.169
	.8byte 0xffe00d1c380e0310
	.8byte 0xffffffd80d1affff
	.8byte 0xe00d1c380e0c1022
	.8byte 0xfffff80d1affffff
	.8byte 0x0d1c380e0d1022ff
	.8byte 0xfff00d1affffffe0
	.8byte 0x1c380e0e1022ffff
	.8byte 0xe80d1affffffe00d
	.8byte 0x380e0f1022ffffff
	.8byte 0x0d1affffffe00d1c
	.4byte 0xffffffe0
	.2byte 0x0422
	.4byte ..___tag_value_exddxm.180-..___tag_value_exddxm.171
	.2byte 0x04c3
	.4byte ..___tag_value_exddxm.181-..___tag_value_exddxm.180
	.2byte 0x04cf
	.4byte ..___tag_value_exddxm.182-..___tag_value_exddxm.181
	.2byte 0x04ce
	.4byte ..___tag_value_exddxm.183-..___tag_value_exddxm.182
	.2byte 0x04cd
	.4byte ..___tag_value_exddxm.184-..___tag_value_exddxm.183
	.2byte 0x04cc
	.4byte ..___tag_value_exddxm.185-..___tag_value_exddxm.184
	.8byte 0x00000000c608070c
	.2byte 0x0000
	.4byte 0x000000bc
	.4byte 0x00000404
	.8byte ..___tag_value_exddxd.188
	.8byte ..___tag_value_exddxd.210-..___tag_value_exddxd.188
	.byte 0x04
	.4byte ..___tag_value_exddxd.190-..___tag_value_exddxd.188
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_exddxd.191-..___tag_value_exddxd.190
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_exddxd.193-..___tag_value_exddxd.191
	.8byte 0xffe00d1c380e0d10
	.8byte 0xfffffff80d1affff
	.8byte 0xe00d1c380e0e1022
	.8byte 0xfffff00d1affffff
	.8byte 0x0d1c380e0f1022ff
	.8byte 0xffe80d1affffffe0
	.4byte 0x0422ffff
	.4byte ..___tag_value_exddxd.200-..___tag_value_exddxd.193
	.2byte 0x04cf
	.4byte ..___tag_value_exddxd.201-..___tag_value_exddxd.200
	.2byte 0x04ce
	.4byte ..___tag_value_exddxd.202-..___tag_value_exddxd.201
	.2byte 0x04cd
	.4byte ..___tag_value_exddxd.203-..___tag_value_exddxd.202
	.4byte 0xc608070c
	.byte 0x04
	.4byte ..___tag_value_exddxd.205-..___tag_value_exddxd.203
	.8byte 0x0e0d10028610060c
	.8byte 0x1affffffe00d1c38
	.8byte 0x0e1022fffffff80d
	.8byte 0xffffffe00d1c380e
	.8byte 0x1022fffffff00d1a
	.8byte 0xffffe00d1c380e0f
	.8byte 0x22ffffffe80d1aff
	.4byte 0x00000000
	.2byte 0x0000
	.byte 0x00
	.4byte 0x00000094
	.4byte 0x000004c4
	.8byte ..___tag_value_exintd.211
	.8byte ..___tag_value_exintd.228-..___tag_value_exintd.211
	.byte 0x04
	.4byte ..___tag_value_exintd.213-..___tag_value_exintd.211
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_exintd.214-..___tag_value_exintd.213
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_exintd.216-..___tag_value_exintd.214
	.8byte 0xffe00d1c380e0310
	.8byte 0xfffffff00d1affff
	.8byte 0xe00d1c380e0c1022
	.8byte 0xfffff80d1affffff
	.2byte 0x22ff
	.byte 0x04
	.4byte ..___tag_value_exintd.220-..___tag_value_exintd.216
	.2byte 0x04c3
	.4byte ..___tag_value_exintd.221-..___tag_value_exintd.220
	.2byte 0x04cc
	.4byte ..___tag_value_exintd.222-..___tag_value_exintd.221
	.4byte 0xc608070c
	.byte 0x04
	.4byte ..___tag_value_exintd.224-..___tag_value_exintd.222
	.8byte 0x1c380e031010060c
	.8byte 0xf00d1affffffe00d
	.8byte 0x0c10028622ffffff
	.8byte 0xffffffe00d1c380e
	.8byte 0x0022fffffff80d1a
	.4byte 0x00000000
	.2byte 0x0000
# End
