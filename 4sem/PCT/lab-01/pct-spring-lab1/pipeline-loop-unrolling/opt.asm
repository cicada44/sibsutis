endbr64 
test   %esi,%esi
! jle    0x1218 <vec_sum+40>
lea    -0x1(%rsi),%eax
lea    0x4(%rdi,%rax,4),%rdx
xor    %eax,%eax
nopw   0x0(%rax,%rax,1)
add    (%rdi),%eax
add    $0x4,%rdi
cmp    %rdx,%rdi
! jne    0x1208 <vec_sum+24>
ret    
nopl   0x0(%rax)
xor    %eax,%eax
ret