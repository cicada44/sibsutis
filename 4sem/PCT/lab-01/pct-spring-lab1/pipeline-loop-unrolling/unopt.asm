endbr64 
push   %rbp
mov    %rsp,%rbp
mov    %rdi,-0x18(%rbp)
mov    %esi,-0x1c(%rbp)
movl   $0x0,-0x8(%rbp)
movl   $0x0,-0x4(%rbp)
! jmp    0x127b <vec_sum+60>
mov    -0x4(%rbp),%eax
cltq   
lea    0x0(,%rax,4),%rdx
mov    -0x18(%rbp),%rax
add    %rdx,%rax
mov    (%rax),%eax
add    %eax,-0x8(%rbp)
addl   $0x1,-0x4(%rbp)
mov    -0x4(%rbp),%eax
cmp    -0x1c(%rbp),%eax
! jl     0x125e <vec_sum+31>
mov    -0x8(%rbp),%eax
pop    %rbp
ret