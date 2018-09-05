unsigned __int64 do_business()
{
  __int64 cmd; // [rsp+0h] [rbp-18h]
  unsigned __int64 v2; // [rsp+8h] [rbp-10h]

  v2 = __readfsqword(0x28u);
  puts("PROMPT: Enter command:");
  get_cmd((char *)&cmd, 8LL);
  if ( !memcmp(&cmd, "GET\n", 5uLL) )
  {
    process_get();
  }
  else if ( !memcmp(&cmd, "PUT\n", 5uLL) )
  {
    process_put();
  }
  else if ( !memcmp(&cmd, "DUMP\n", 6uLL) )
  {
    process_dump();
  }
  else if ( !memcmp(&cmd, "DEL\n", 5uLL) )
  {
    process_del();
  }
  else
  {
    if ( !memcmp(&cmd, "EXIT\n", 6uLL) )
      just_exit();
    __printf_chk(1LL, "ERROR: '%s' is not a valid command.\n", &cmd);
  }
  return __readfsqword(0x28u) ^ v2;
}

