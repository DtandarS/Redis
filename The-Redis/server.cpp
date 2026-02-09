/*


   - Created by Tomsa da DtandarS

   - 16.12.2025 at 20:44

   - Please hire me please.


*/

#include <master.h>


bool isTrue{true};
static size_t max_message = 4096;

static void msg(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

static void msg_errno(const char *msg)
{
  int err = errno;
  fprintf(stderr, "errno[%d] %s\n", err, msg);
}

static void die(const char *msg)
{
  int err = errno;
  printf("[%d] %c\n", err, *msg);
  abort();
}

int main(int argv, char** argc)
{


  return 0;
}





