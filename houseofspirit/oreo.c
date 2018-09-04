unsigned int leave_message()
{
  unsigned int v0; // ST1C_4

  v0 = __readgsdword(0x14u);
  printf("Enter any notice you'd like to submit with your order: ");
  fgets(order_message, 128, stdin);
  replace_0xA(order_message);
  return __readgsdword(0x14u) ^ v0;
}

unsigned int __cdecl replace_0xA(const char *message)
{
  size_t last; // edx
  char *c; // [esp+28h] [ebp-10h]
  unsigned int v4; // [esp+2Ch] [ebp-Ch]

  v4 = __readgsdword(0x14u);
  last = strlen(message) - 1;
  c = (char *)&message[last];
  if ( &message[last] >= message && *c == 10 )
    *c = 0;
  return __readgsdword(0x14u) ^ v4;
}

unsigned int do_business()
{
  unsigned int v1; // [esp+1Ch] [ebp-Ch]

  v1 = __readgsdword(0x14u);
  puts("What would you like to do?\n");
  printf("%u. Add new rifle\n", 1);
  printf("%u. Show added rifles\n", 2);
  printf("%u. Order selected rifles\n", 3);
  printf("%u. Leave a Message with your Order\n", 4);
  printf("%u. Show current stats\n", 5);
  printf("%u. Exit!\n", 6);
  while ( 1 )
  {
    switch ( get_option() )
    {
      case 1:
        add_rifle();
        break;
      case 2:
        show_add();
        break;
      case 3:
        order_rifle();
        break;
      case 4:
        leave_message();
        break;
      case 5:
        show_stats();
        break;
      case 6:
        return __readgsdword(0x14u) ^ v1;
      default:
        continue;
    }
  }
}

nt get_option()
{
  int option; // [esp+18h] [ebp-30h]
  char s; // [esp+1Ch] [ebp-2Ch]
  unsigned int v3; // [esp+3Ch] [ebp-Ch]

  v3 = __readgsdword(0x14u);
  do
  {
    printf("Action: ");
    fgets(&s, 32, stdin);
  }
  while ( !__isoc99_sscanf(&s, "%u", &option) );
  return option;
}
unsigned int add_rifle()
{
  Order *pre; // [esp+18h] [ebp-10h]
  unsigned int v2; // [esp+1Ch] [ebp-Ch]

  v2 = __readgsdword(0x14u);
  pre = (Order *)g_ptr;
  g_ptr = (char *)malloc(0x38u);
  if ( g_ptr )
  {
    *((_DWORD *)g_ptr + 13) = pre;
    printf("Rifle name: ");
    fgets(g_ptr + 25, 56, stdin);
    replace_0xA(g_ptr + 25);
    printf("Rifle description: ");
    fgets(g_ptr, 56, stdin);
    replace_0xA(g_ptr);
    ++add_times;
  }
  else
  {
    puts("Something terrible happened!");
  }
  return __readgsdword(0x14u) ^ v2;
}

unsigned int show_add()
{
  Order *i; // [esp+14h] [ebp-14h]
  unsigned int v2; // [esp+1Ch] [ebp-Ch]

  v2 = __readgsdword(0x14u);
  printf("Rifle to be ordered:\n%s\n", "===================================");
  for ( i = (Order *)g_ptr; i; i = *(Order **)&i->pre )
  {
    printf("Name: %s\n", i->name);
    printf("Description: %s\n", i);
    puts("===================================");
  }
  return __readgsdword(0x14u) ^ v2;
}

unsigned int order_rifle()
{
  Order *ptr; // ST18_4
  Order *v2; // [esp+14h] [ebp-14h]
  unsigned int v3; // [esp+1Ch] [ebp-Ch]

  v3 = __readgsdword(0x14u);
  v2 = (Order *)g_ptr;
  if ( add_times )
  {
    while ( v2 )
    {
      ptr = v2;
      v2 = *(Order **)&v2->pre;
      free(ptr);
    }
    g_ptr = 0;
    ++order_times;
    puts("Okay order submitted!");
  }
  else
  {
    puts("No rifles to be ordered!");
  }
  return __readgsdword(0x14u) ^ v3;
}

unsigned int show_stats()
{
  unsigned int v1; // [esp+1Ch] [ebp-Ch]

  v1 = __readgsdword(0x14u);
  puts("======= Status =======");
  printf("New:    %u times\n", add_times);
  printf("Orders: %u times\n", order_times);
  if ( *order_message )
    printf("Order Message: %s\n", order_message);
  puts("======================");
  return __readgsdword(0x14u) ^ v1;
}

int __cdecl main()
{
  add_times = 0;
  order_times = 0;
  order_message = (char *)&unk_804A2C0;
  puts("Welcome to the OREO Original Rifle Ecommerce Online System!");
  puts(
    "\n"
    "     ,______________________________________\n"
    "    |_________________,----------._ [____]  -,__  __....-----=====\n"
    "                   (_(||||||||||||)___________/                   |\n"
    "                      `----------'   OREO [ ))\"-,                   |\n"
    "                                           \"\"    `,  _,--....___    |\n"
    "                                                   `/           \"\"\"\"\n"
    "\t");
  do_business();
  return 0;
}

00000000 Order           struc ; (sizeof=0x36, mappedto_5)
00000000 description     db 25 dup(?)
00000019 name            db 27 dup(?)
00000034 pre             dw ?
00000036 Order           ends
