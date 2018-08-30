__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  int num; // eax
  signed int isok; // [rsp+Ch] [rbp-74h]
  char nptr; // [rsp+10h] [rbp-70h]
  unsigned __int64 v7; // [rsp+78h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  alarm(0x78u);
  while ( fgets(&nptr, 10, stdin) )
  {
    num = atoi(&nptr);
    if ( num == 2 )
    {
      isok = write_content();
      goto echo_result;
    }
    if ( num > 2 )
    {
      if ( num == 3 )
      {
        isok = free_size();
        goto echo_result;
      }
      if ( num == 4 )
      {
        isok = check_size();
        goto echo_result;
      }
    }
    else if ( num == 1 )
    {
      isok = malloc_size();
      goto echo_result;
    }
    isok = -1;
echo_result:
    if ( isok )
      puts("FAIL");
    else
      puts("OK");
    fflush(stdout);
  }
  return 0LL;
}

signed __int64 write_content()
{
  signed __int64 result; // rax
  int i; // eax
  unsigned int idx; // [rsp+8h] [rbp-88h]
  __int64 size; // [rsp+10h] [rbp-80h]
  char *ptr; // [rsp+18h] [rbp-78h]
  char buf; // [rsp+20h] [rbp-70h]
  unsigned __int64 v6; // [rsp+88h] [rbp-8h]

  v6 = __readfsqword(0x28u);
  fgets(&buf, 16, stdin);
  idx = atol(&buf);
  if ( idx > 0x100000 )
    return 0xFFFFFFFFLL;
  if ( !chunk_ptra[idx] )
    return 0xFFFFFFFFLL;
  fgets(&buf, 16, stdin);
  size = atoll(&buf);
  ptr = chunk_ptra[idx];
  for ( i = fread(ptr, 1uLL, size, stdin); i > 0; i = fread(ptr, 1uLL, size, stdin) )
  {
    ptr += i;
    size -= i;
  }
  if ( size )
    result = 0xFFFFFFFFLL;
  else
    result = 0LL;
  return result;
}

signed __int64 free_size()
{
  unsigned int i; // [rsp+Ch] [rbp-74h]
  char buf; // [rsp+10h] [rbp-70h]
  unsigned __int64 v3; // [rsp+78h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  fgets(&buf, 16, stdin);
  i = atol(&buf);
  if ( i > 0x100000 )
    return 0xFFFFFFFFLL;
  if ( !chunk_ptra[i] )
    return 0xFFFFFFFFLL;
  free(chunk_ptra[i]);
  chunk_ptra[i] = 0LL;
  return 0LL;
}

signed __int64 check_size()
{
  unsigned int idx; // [rsp+Ch] [rbp-74h]
  char buf; // [rsp+10h] [rbp-70h]
  unsigned __int64 v3; // [rsp+78h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  fgets(&buf, 16, stdin);
  idx = atol(&buf);
  if ( idx > 0x100000 )
    return 0xFFFFFFFFLL;
  if ( !chunk_ptra[idx] )
    return 0xFFFFFFFFLL;
  if ( strlen(chunk_ptra[idx]) <= 3 )
    puts("//TODO");
  else
    puts("...");
  return 0LL;
}

signed __int64 malloc_size()
{
  __int64 size; // [rsp+0h] [rbp-80h]
  char *p; // [rsp+8h] [rbp-78h]
  char buf; // [rsp+10h] [rbp-70h]
  unsigned __int64 v4; // [rsp+78h] [rbp-8h]

  v4 = __readfsqword(0x28u);
  fgets(&buf, 16, stdin);
  size = atoll(&buf);
  p = (char *)malloc(size);
  if ( !p )
    return 0xFFFFFFFFLL;
  chunk_ptra[++idxstart1_602100] = p;
  printf("%d\n", (unsigned int)idxstart1_602100, size);
  return 0LL;
}
